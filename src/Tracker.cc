/*
 * P2PApp.cc
 *
 *  Created on: Sep 22, 2012
 *      Author: Aniruddha Gokhale
 *      Class:  CS381
 *      Institution: Vanderbilt University
 */

#include "Tracker.h"         // our header
#include "PeerToPeerMSG_m.h"
#include "PeerToTrackerMsg_m.h"

#include "IPvXAddressResolver.h"

Define_Module(Tracker)
;

Tracker::Tracker(void) {
    // nothing
}

Tracker::~Tracker() {
    // nothing
}

// the initialize method
void Tracker::initialize(int stage) {
    cSimpleModule::initialize(stage);
    if (stage != 3)
        return;

    // obtain the values of parameters
    this->localAddress_ = this->par("localAddress").stringValue();
    this->localPort_ = this->par("localPort");
    this->connectPort_ = this->par("connectPort");
    this->numPeersInSim_ = this->par("numPeersInSim_");

    map<string, vector<int> > mymap;
    this->peers_to_chunk_ = mymap;
    /// chunknumber2 chunknumber5 chunknumber8 peer4 ; chunknumber22  chunk9 chunknumber5 chunknumber8 peer8;

    const char *str = this->par("peers_to_chunk").stringValue();
    cStringTokenizer tokenizer = cStringTokenizer(str);
    tokenizer.setDelimiter(";");
    vector<string> tokenisedVector = tokenizer.asVector();

    this->numberOfSeeders.setName("number of seeders");

    for (size_t i = 0; i < tokenisedVector.size(); i++) {
        const char *str4 = tokenisedVector[i].c_str();
        vector<string> tokenisedChunkVector = cStringTokenizer(str4).asVector();
        string peername = tokenisedChunkVector.back();
        tokenisedChunkVector.pop_back();
        vector<int> chunkList;
        for (size_t i = 0; i < tokenisedChunkVector.size(); i++) {
            const char *str4 = tokenisedChunkVector[i].c_str();
            std::stringstream s_str(str4);
            int j;
            s_str >> j;
            insertChunkInOrder(chunkList, j);
        }

        this->peers_to_chunk_.insert(
                pair<string, vector<int> >(peername, chunkList));
    }

    /*
     // here is a way to read a parameter array (see user manual section 4.5.4)
     const char *str2 = this->par ("connectAddresses").stringValue ();
     this->connectAddresses_ = cStringTokenizer (str2).asVector();*/

    // indicate what type of data transfer is going to be supported by our socket
    // there are three choices supported in INET. For now we choose BYTECOUNT, i.e.,
    // the underlying system will emulate the sending of that many bytes. We
    // are not concerned with the actual content. But if we really wanted to do it
    // that way, then we will do BYTESTREAM
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

/** the all serving handle message method */
void Tracker::handleMessage(cMessage *msg) {
    EV<< "=== Tracker: " << this->localAddress_
    << " received handleMessage message" << endl;

    // check if this was a self generated message, such as a timeout to wake us up to
    // connect to a peer
    // no need for this one in tracker
    if (msg->isSelfMessage())
    EV << "Error There is no self message sent" << endl;
    else {
        // let the socket class process the message and make a call back on the
        // appropriate method. But note that we need to determine which socket must
        // handle this message: it could be connection establishment in our passive role
        // or it could be ack to our active conn establishment or it could be a data packet
        TCPSocket *socket = this->socketMap_.findSocketFor(msg);
        if (!socket) {
            // we are going to be here if we are a passive listener of incoming connection
            // at which point a connection will be established. But there will not be a
            // socket created yet for the data transfer. We create such a socket.

            // make sure first that we are dealing with a TCP command
            TCPCommand *cmd = dynamic_cast<TCPCommand *>(msg->getControlInfo());
            if (!cmd) {
                throw cRuntimeError(
                        "Tracker::handleMessage: no TCPCommand control info in message (not from TCP?)");
            } else {
                EV << "=== Tracker: " << this->localAddress_
                << " **No socket yet ** ===" << endl;

                int connId = cmd->getConnId();
                // debugging
                EV << "+++ Tracker: " << this->localAddress_
                << " creating a new socket with " << "connection ID = "
                << connId << " ===" << endl;

                // notice that we must use the other constructor of TCPSocket so that it
                // will use the underlying connID that was created after an incoming
                // connection establishment message
                TCPSocket *new_socket = new TCPSocket(msg);

                // register ourselves as the callback object
                bool *passive = new bool(true);
                new_socket->setCallbackObject(this, passive);

                // do not forget to set the outgoing gate
                new_socket->setOutputGate(gate("tcpOut"));

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

    /** this method is provided to clean things up when the simulation stops */
void Tracker::finish() {
    EV<< "=== finish called" << endl;

    // cleanup all the sockets
    this->socketMap_.deleteSockets();

    std::string modulePath = getFullPath();
}

    /*************************************************/
    /** implement all the callback interface methods */
    /*************************************************/

void Tracker::socketEstablished(int connID, void *role) {
    EV<< "=== Tracker: " << this->localAddress_
    << " received socketEstablished message on connID " << connID
    << " ===" << endl;

    setStatusString("ConnectionEstablished");

    // tracker is passive, dont need to do anything

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
                it = this->peers_to_chunk_.find(requestorId);
                if (it != this->peers_to_chunk_.end())
                this->peers_to_chunk_.erase(it);

                // add this key-value pair to the map
                this->peers_to_chunk_.insert(
                        pair<string, vector<int> >(requestorId, chunkList));

                // add peer to peer list
                this->peers_.insert(req->getId());

                // now send a response
                this->sendResponse(connID);
            }
        }
        break;
        case P2T_DOWNLOAD_COMPLETE: {

            P2T_DOWNLOAD_COMPLETE_Msg *req = dynamic_cast<P2T_DOWNLOAD_COMPLETE_Msg *>(msg);
            if (!req) {
                EV << "Arriving packet is not of type P2T_DOWNLOAD_COMPLETE_Msg" << endl;
            } else {

                this->numSeedsInTorrent_++;
                this->numberOfSeeders.record(numSeedsInTorrent_);

                if (this->numSeedsInTorrent_ >= this->numPeersInSim_) {
                    endSimulation();
                }

            }
        }
        break;
        default:
        EV << ">>> unknown incoming request type <<< " << endl;
        break;
    }

    // cleanup
    delete msg;
}

void Tracker::socketPeerClosed(int connID, void *) {
    EV<< "=== Peer: " << this->localAddress_
    << " received socketPeerClosed message" << endl;
    EV << "peer closed for connID = " << connID << endl;

}

void Tracker::socketClosed(int, void *) {
    EV<< "=== Peer: " << this->localAddress_
    << " received socketClosed message" << endl;
    // *redefine* to start another session etc.
    EV << "connection closed\n";
    setStatusString("closed");
}

void Tracker::socketFailure(int, void *, int code) {
    EV<< "=== Peer: " << this->localAddress_
    << " received socketFailure message" << endl;
    // subclasses may override this function, and add code try to reconnect after a delay.
    EV << "connection broken\n";
    setStatusString("broken");

}

    /**********************************************************************/
    /**           helper methods                                          */
    /**********************************************************************/

// connect to peer i
void Tracker::connect(int i) {
    EV<< "=== Peer: " << this->localAddress_ << " received connect message"
    << endl;
    EV << "issuing connect command\n";
    setStatusString("connecting");

    // we allocate a socket to be used for actively connecting to the peer and
    // transferring data over it.
    TCPSocket *new_socket = new TCPSocket();

    // don't forget to set the output gate for this socket. I learned it the
    // hard way :-(
    new_socket->setOutputGate(gate("tcpOut"));

    // another thing I learned the hard way is that we must set up the data transfer
    // mode for this new socket
    new_socket->setDataTransferMode(this->socket_->getDataTransferMode());

    // issue a connect request
    new_socket->connect(
            IPvXAddressResolver().resolve(this->connectAddresses_[i].c_str()),
            this->connectPort_);

    // do not forget to set ourselves as the callback on this new socket
    bool *passive = new bool(false);
    new_socket->setCallbackObject(this, passive);

    // debugging
    EV << "+++ Peer: " << this->localAddress_ << " created a new socket with "
    << "connection ID = " << new_socket->getConnectionId() << " ==="
    << endl;

    // save this socket in our outgoing connection map
    this->socketMap_.addSocket(new_socket);
}

// close the peer side
void Tracker::close() {
    EV<< "=== Peer: " << this->localAddress_ << " received close () message"
    << endl;
    EV << "issuing CLOSE command\n";

    setStatusString("closing");

    this->socket_->close();
}

// send a response
void Tracker::sendResponse(int connId) {
    EV<< "=== Peer: " << this->localAddress_ << " sendResponse. " << endl;

    // this is a hack because the TCPSocketMap does not allow us to search based on
    // connection ID. So we have to take a circuitous route to get to the socket
    cMessage *temp_msg = new cMessage("temp");
    TCPCommand *temp_cmd = new TCPCommand();
    temp_cmd->setConnId(connId);
    temp_msg->setControlInfo(temp_cmd);

    TCPSocket *socket = this->socketMap_.findSocketFor(temp_msg);
    if (!socket) {
        EV << ">>> Cannot find socket to send request <<< " << endl;
    } else {
        T2P_MEMBERSHIP_Res *resp = new T2P_MEMBERSHIP_Res();

        // response type enum
        resp->setType((int) T2P_MEMBERSHIP_RESPONSE);

        // set peer list
        resp->setIdsArraySize(this->peers_.size());

        set<string>::iterator iter;
        int i = 0;
        for (iter = this->peers_.begin(); iter != this->peers_.end(); iter++) {
            resp->setIds(i++, (*iter).c_str());
        }

        // number of peer info whic tracker has
        resp->setPeer_to_chunk_ownershipArraySize(this->peers_to_chunk_.size());

        // iterator for peer and chunk map
        map<string, vector<int> >::iterator it;

        int k = 0;
        for (it = this->peers_to_chunk_.begin();
                it != this->peers_to_chunk_.end(); ++it) {
            Ownership_Message *respOwnership = new Ownership_Message();
            // set id for ownership message
            respOwnership->setId((*it).first.c_str());
            int chunkVectorSize = (*it).second.size();
            respOwnership->setOwned_chunksArraySize(chunkVectorSize);

            for (int i = 0; i < chunkVectorSize; i++) {
                respOwnership->setOwned_chunks(i, (*it).second[i]);
            }

            resp->setPeer_to_chunk_ownership(k++, *respOwnership);

        }
        // need to set the byte length else nothing gets sent as I found the hard way
        resp->setByteLength(1024);// I think we can set any length we want :-)

        socket->send(resp);
    }

    // cleanup
    delete temp_msg;
}

void Tracker::insertChunkInOrder(vector<int> &chunkList, int chunkValue) {

    if (chunkList.empty()) {
        chunkList.push_back(chunkValue);
        return;
    }

    int chunkInsertionNumber = 0;
    bool found = false;
    for (size_t i = 0; i < chunkList.size(); i++) {
        if (chunkList[i] > chunkValue) {
            chunkInsertionNumber = i;
            found = true;
            break;
        } else if (chunkList[i] == chunkValue)
            // already have this chunk, ignore
            return;
    }

    if (!found)
        chunkInsertionNumber = chunkList.size();

    chunkList.insert(chunkList.begin() + chunkInsertionNumber, chunkValue);
}

void Tracker::setStatusString(const char *s) {
    if (ev.isGUI()) {
        getDisplayString().setTagArg("t", 0, s);
        bubble(s);
    }
}

