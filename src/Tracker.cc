//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "PeerToTrackerMsg_m.h"    // generated header from the message file
#include "Tracker.h"

#include "IPvXAddressResolver.h"     // manages both IPv4 and IPV6 address resolution
Define_Module(Tracker)
;

Tracker::Tracker(void) {
}

Tracker::~Tracker() {
}

// the initialize method. We initialize the parameter. Connection to the server is done after an event is triggered
void Tracker::initialize(int stage) {

    // Skip all but stage '3'
    cSimpleModule::initialize(stage);
    if (stage != 3) {
        return;
    }

    // obtain the values of parameters

    this->numSeedsInTorrent = 0;

    this->localAddress_ = this->par("localAddress").stringValue();
    this->localPort_ = this->par("localPort");
    this->connectPort_ = this->par("connectPort");
    this->numPeersInSim_ = this->par("numPeersInSim");

    map<string, vector<int> > mymap; // construct empty map
    this->peers_to_chunk_map_ = mymap; // assign it to peers_to_chunk_map_

    string dataTransferMode = this->par("dataTransferMode").stringValue();

    // create a new socket for the listening role
    this->socket_ = new TCPSocket();

    // decide the data transfer mode
    if (!dataTransferMode.compare("bytecount"))
        this->socket_->setDataTransferMode(TCP_TRANSFER_BYTECOUNT);
    else if (!dataTransferMode.compare("object"))
        this->socket_->setDataTransferMode(TCP_TRANSFER_OBJECT);
    else if (!dataTransferMode.compare("bytestream"))
        this->socket_->setDataTransferMode(TCP_TRANSFER_BYTESTREAM);
    else { // error
        EV<< "=== Bad data transfer mode value. Assuming object" << endl;
        this->socket_->setDataTransferMode(TCP_TRANSFER_OBJECT);
    }

        // In the server role, we bind ourselves to the well-defined port and IP address on which
        // we listen for incoming connections
    this->socket_->bind(
            this->localAddress_.length() ?
                    IPvXAddressResolver().resolve(this->localAddress_.c_str()) :
                    IPvXAddress(), this->localPort_);

    // register ourselves as the callback object
    bool *passive = new bool(true);
    this->socket_->setCallbackObject(this, passive); // send the flag

    // do not forget to set the outgoing gate
    this->socket_->setOutputGate(gate("tcpOut"));

    // now listen for incoming connections.  This version is the forking version where
    // upon every new incoming connection, a new socket is created.
    this->socket_->listen();

    // debugging
    EV<< "+++ Peer: " << this->localAddress_
    << " created a listening socket with " << "connection ID = "
    << this->socket_->getConnectionId() << " +++" << endl;

    // now save this socket in our map
    this->socketMap_.addSocket(this->socket_);

    setStatusString("waiting");

}

/** This is the all-encompassing event handling function. It is our responsibility to
 *  figure out what to do with every event, which is appln-specific */
void Tracker::handleMessage(cMessage *msg) {

    if (msg->isSelfMessage()) {
        EV<< "Error There is no self message sent" << endl;
    }
    else {

        TCPSocket *socket = this->socketMap_.findSocketFor(msg);
        if (!socket) {
            TCPCommand *cmd = dynamic_cast<TCPCommand *>(msg->getControlInfo());
            if (!cmd) {
                throw cRuntimeError(
                        "TrackerApp::handleMessage: no TCPCommand control info in message (not from TCP?)");
            } else {
                TCPSocket *new_socket = new TCPSocket(msg);

                // register ourselves as the callback object
                bool *passive = new bool(true);
                new_socket->setCallbackObject(this, passive);

                // do not forget to set the outgoing gate
                new_socket->setOutputGate(gate("tcpOut"));

                // for the sake of correctness, we make sure the socket exists
                if (!this->socket_) {  // no socket. How did we come here?
                    throw cRuntimeError("ClientApp::handleMessage: no connection yet to server");
                }

                // another thing I learned the hard way is that we must set up the data trasnfer
                // mode for this new socket
                new_socket->setDataTransferMode(
                        this->socket_->getDataTransferMode());

                // now save this socket in our map
                this->socketMap_.addSocket(new_socket);

                // process the message
                new_socket->processMessage(msg);
            }
        } else {
            // let that socket process the message
            socket->processMessage(msg);
        }

    }
}

        /** handle incoming data. Could be a request or response */
void Tracker::socketDataArrived(int connID, void *, cPacket *msg, bool) {

    EV<< "=== Peer: " << this->localAddress_
    << " received socketDataArrived message. ===" << endl;

    // incoming request may be of different types
    P2T_Packet *packet = dynamic_cast<P2T_Packet *>(msg);
    if (!packet) {
        return;
    }

    switch ((P2T_MSG_TYPE) packet->getType()) {
        case P2T_REFRESH_MESSAGE:
        // TODO do anything here or just pass through? to re-register
        case P2T_REGISTRATION_REQUEST: {
            Ownership_Message *req = dynamic_cast<Ownership_Message *>(msg);
            if (!req) {
                EV << "Arriving packet is not of type Ownership_Message" << endl;
            } else {
                setStatusString("Registration or Refresh Request");
                string requestorId = req->getId();

                int chunkSize = req->getOwned_chunksArraySize();
                // create vector from chunklist array
                vector<int> chunkList;

                for (int i = 0; i < chunkSize; i++) {
                    chunkList.push_back(req->getOwned_chunks(i));
                }
                EV << "Arriving packet: Requestor ID = " << requestorId
                << ", Owned Chunks size= " << chunkSize << endl;

                // remove the element if existing
                map<string, vector<int> >::iterator it;
                it = this->peers_to_chunk_map_.find(requestorId);
                if (it != this->peers_to_chunk_map_.end())
                this->peers_to_chunk_map_.erase(it);

                // add this key-value pair to the map
                this->peers_to_chunk_map_.insert(
                        pair<string, vector<int> >(requestorId, chunkList));

                // add peer to peer list
                this->peers_.insert(req->getId());

                // now send a response
                this->sendResponse(connID);
            }

        }
        /*
         * Catch when the download is complete, to end the simulation when they all have
         */
        case P2T_DOWNLOAD_COMPLETE: {

            P2T_DOWNLOAD_COMPLETE_Msg *req = dynamic_cast<P2T_DOWNLOAD_COMPLETE_Msg *>(msg);
            if (!req) {
                EV << "Arriving packet is not of type P2T_DOWNLOAD_COMPLETE_Msg" << endl;
            } else {

                this->numSeedsInTorrent++;

                if (this->numSeedsInTorrent >= this->numPeersInSim_) {
                    endSimulation();
                }

            }
        }
        default:
        EV << ">>> unknown incoming request type <<< " << endl;
        break;
    }

    // cleanup
    delete msg;
}

// send a response
void Tracker::sendResponse(int connId) { // const char *id, unsigned long size) {

}

void Tracker::close(void) {
    EV<< "=== Peer: " << this->localAddress_ << " received close () message"
    << endl;
    this->socket_->close();
}

void Tracker::finish() {
    // cleanup all the sockets
    this->socketMap_.deleteSockets();
}

// this method is used to flash messages during animation where we can see bubbles on the screen.
void Tracker::setStatusString(const char *s) {
    if (ev.isGUI ()) {
        getDisplayString ().setTagArg ("t", 0, s);
        bubble (s);
    }
}

void Tracker::socketFailure(int connId, void *yourPtr, int code) {
    EV<< "*** Tracker: " << this->localAddress_
    << " received socketFailure message" << " from " << connId << endl;
}

    /** Called when the peer sends a connection established msg */
void Tracker::socketEstablished(int connID, void *role) {
    // is passive, shouldn't have to do anything
    EV<< "*** Tracker: " << this->localAddress_
    << " received socketEstablished message" << " from " << connID << endl;
}

    /** Called when the peer sends a connection closed msg */
void Tracker::socketClosed(int connId, void *yourPtr) {
    // this shouldn't happen in our simulation
    EV<< "*** Tracker: " << this->localAddress_
    << " received socketPeerClosed message" << " from " << connId << endl;
}

    /** Called when the peer sends a connection closed msg */
void Tracker::socketPeerClosed(int connID, void *) {
    // this shouldn't happen in our simulation
    EV<< "*** Tracker: " << this->localAddress_
    << " received socketPeerClosed message" << " from " << connID << endl;
}

