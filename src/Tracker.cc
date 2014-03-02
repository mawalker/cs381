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
    this->localAddress_ = this->par("localAddress").stringValue();
    this->localPort_ = this->par("localPort");
    this->connectPort_ = this->par("connectPort");

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

void Tracker::close(void) {
}

/** This is the all-encompassing event handling function. It is our responsibility to
 *  figure out what to do with every event, which is appln-specific */
void Tracker::handleMessage(cMessage *msg) {

}

/** handle incoming data. Could be a request or response */
void Tracker::socketDataArrived(int connID, void *, cPacket *msg, bool) {

}

// send a response
void Tracker::sendResponse(int connId) { // const char *id, unsigned long size) {

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

