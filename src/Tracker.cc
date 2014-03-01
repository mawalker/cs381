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

#include "IPvXAddressResolver.h"     // manages both IPv4 and IPV6 addess resolution

Define_Module(Tracker);

Tracker::Tracker(void) :
        myID_(), localPort_(0), socket_(NULL) {
}

Tracker::~Tracker() {
}

// the initialize method. We initialize the parameter. Connection to the server is done after an event is triggered
void Tracker::initialize(int stage) {

    cSimpleModule::initialize(stage);
    if (stage != 3)
        return;

    // obtain the values of parameters
    this->localAddress_ = this->par("localAddress").stringValue();
    this->localPort_ = this->par("localPort");

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
        this->socket_->setDataTransferMode (TCP_TRANSFER_OBJECT);
    }

        // In the server role, we bind ourselves to the well-defined port and IP address on which
        // we listen for incoming connections
    this->socket_->bind(
            this->localAddress_.length() ?
                    IPvXAddressResolver().resolve(this->localAddress_.c_str()) :
                    IPvXAddress(), this->localPort_);

    // register ourselves as the callback object and indicate our role as a passive listener because
    // of our role as a server.
    bool *passive = new bool(true);
    // send the flag as the second param. This is a void * and so only the appln logic knows
    // how to use this flag. We make use of this flag to tell us if we are a client or server.
    // Thus, when a client receives a callback, it is an indication for it to send the next
    // packet to the server.
    this->socket_->setCallbackObject(this, passive);

    // do not forget to set the outgoing gate
    this->socket_->setOutputGate(gate("tcpOut"));

    // now listen for incoming connections.  This version is the forking version where
    // upon every new incoming connection, a new socket is created so that listening happens
    // on one socket while data transmission happens on another.
    this->socket_->listen();

    // debugging
    EV<< "+++ Server: " << this->localAddress_ << " created a listening socket with "
    << "connection ID = " << this->socket_->getConnectionId () << " +++" << endl;

    // now save this socket in our map
    this->socketMap_.addSocket(this->socket_);

    setStatusString("waiting");

}

/** This is the all-encompassing event handling function. It is our responsibility to
 *  figure out what to do with every event, which is appln-specific */
void Tracker::handleMessage(cMessage *msg) {

    EV<< "=== Server: " << this->localAddress_ << " received handleMessage message" << endl;

    // find a socket corresponding to "msg"
    TCPSocket *socket = this->socketMap_.findSocketFor (msg);
    if (!socket) {  // no such socket in our socket map
        // we are going to be here if we are a passive listener of incoming connection
        // at which point a connection will be established. But there will not be a
        // socket created yet for the data transfer. We create such a socket.

        // make sure first that we are dealing with a TCP command (and not something else)
        TCPCommand *cmd = dynamic_cast<TCPCommand *>(msg->getControlInfo());
        if (!cmd) {
            throw cRuntimeError("P2PApp::handleMessage: no TCPCommand control info in message (not from TCP?)");
        } else {
            EV << "=== Server: " << this->localAddress_ << " **No socket yet ** ===" << endl;

            int connId = cmd->getConnId();
            // debugging
            EV << "+++ Server: " << this->localAddress_ << " creating a new socket with "
            << "connection ID = " << connId << " ===" << endl;

            // since we are creating a new socket to handle an incoming connection request
            // with a client so that future data comm can happen over that socket, we use a
            // specific constructor of the TCPSocket class which takes the msg as a param.
            // Internally, that constructor uses the connection ID.
            TCPSocket *new_socket = new TCPSocket (msg);

            // register ourselves as the callback object
            bool *passive = new bool (true);// since we are on the server side
            new_socket->setCallbackObject (this, passive);

            // do not forget to set the outgoing gate. Same gate is used to talk to the TCP layer.
            new_socket->setOutputGate (gate ("tcpOut"));

            // another thing I learned the hard way is that we must set up the data trasnfer
            // mode for this new socket otherwise things do not work. We acquire this mode
            // from our parent socket.
            new_socket->setDataTransferMode (this->socket_->getDataTransferMode ());

            // now save this socket in our map
            this->socketMap_.addSocket (new_socket);

            // process the message on this new socket
            new_socket->processMessage (msg);
        }
    } else {
        // let that socket that already exists, process the message
        socket->processMessage (msg);
    }
}

// when the client sends a connection established msg, this callback will be invoked.
void Tracker::socketEstablished(int connID, void *role) {
    EV<< "=== Server: " << this->localAddress_
    << " received socketEstablished message on connID " << connID << " ===" << endl;

    setStatusString("ConnectionEstablished");
}

    /** handle incoming data. Could be a request or response */
void Tracker::socketDataArrived(int connID, void *, cPacket *msg, bool) {

    EV<< "=== Socket: " << this->localAddress_
    << " received socketDataArrived message. ===" << endl;

    // incoming request may be of different types
    CS_Packet *packet = dynamic_cast<CS_Packet *> (msg);
    if (!packet) {
        return;
    }

    // check what kind of packet is it
    switch ((CS_MSG_TYPE)packet->getType ()) {
        case CS_REQUEST:
        {
            CS_Req *req = dynamic_cast<CS_Req *> (msg);
            if (!req) {
                EV << "Arriving packet is not of type CS_Req" << endl;
            } else {
                setStatusString ("Request");
                EV << "Arriving packet: Requestor ID = " << req->getId ()
                << ", Requested filename = " << req->getFname () << endl;

                // now send a response
                this->sendResponse (connID, this->localAddress_.c_str (), 128);
            }
        }
        break;
        case CS_RESPONSE:
        {
            CS_Resp *resp = dynamic_cast<CS_Resp *> (msg);
            if (!resp) {
                EV << "Arriving packet is not of type CS_Resp" << endl;
            } else {
                setStatusString ("Response");
                EV << "Arriving packet: Responder ID = " << resp->getId ()
                << ", size = " << resp->getSize () << endl;

                // send the next request to the peer from whom we got a response
                this->sendRequest (connID, this->localAddress_.c_str (), "dummy.txt");
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

// send a request to the other side
void Tracker::sendRequest (int connId, const char *id, const char *fname)
{
    EV << "=== Server: " << this->localAddress_ << " sendRequest. "
       << "Sending ID: " << id << ", file name " << fname << " ===" << endl;

    // this is a hack because the TCPSocketMap does not allow us to search based on
    // connection ID. So we have to take a circuitous route to get to the socket
    cMessage *temp_msg = new cMessage ("temp");
    TCPCommand *temp_cmd = new TCPCommand ();
    temp_cmd->setConnId (connId);
    temp_msg->setControlInfo (temp_cmd);

    TCPSocket *socket = this->socketMap_.findSocketFor (temp_msg);
    if (!socket) {
        EV << ">>> Cannot find socket to send request <<< " << endl;
    } else {

        // create a Request message
        CS_Req *req = new CS_Req ();
        req->setType ((int)CS_REQUEST);
        req->setId (id);
        req->setFname (fname);
        // need to set the byte length else nothing gets sent as I found the hard way
        req->setByteLength (32);  // I think we can set any length we want :-)

        socket->send (req);
    }

    // cleanup
    delete temp_msg;
}

// send a response
void Tracker::sendResponse (int connId, const char *id, unsigned long size)
{
    EV << "=== Server: " << this->localAddress_ << " sendResponse. "
       << "Sending ID: " << id << ", size: " << size << " ===" << endl;

    // this is a hack because the TCPSocketMap does not allow us to search based on
    // connection ID. So we have to take a circuitous route to get to the socket
    cMessage *temp_msg = new cMessage ("temp");
    TCPCommand *temp_cmd = new TCPCommand ();
    temp_cmd->setConnId (connId);
    temp_msg->setControlInfo (temp_cmd);

    TCPSocket *socket = this->socketMap_.findSocketFor (temp_msg);
    if (!socket) {
        EV << ">>> Cannot find socket to send request <<< " << endl;
    } else {
        CS_Resp *resp = new CS_Resp ();
        resp->setType ((int)CS_RESPONSE);
        resp->setId (id);
        resp->setSize (size);
        // need to set the byte length else nothing gets sent as I found the hard way
        resp->setByteLength (1024);  // I think we can set any length we want :-)

        socket->send (resp);
    }

    // cleanup
    delete temp_msg;
}

// this method is used to flash messages during animation where we can see bubbles on the screen.
void Tracker::setStatusString(const char *s)
{
    if (ev.isGUI ()) {
        getDisplayString ().setTagArg ("t", 0, s);
        bubble (s);
    }
}

void Tracker::socketPeerClosed (int connID, void *){

    // delete socket from the map
    cMessage *temp_msg = new cMessage ("temp");
    TCPCommand *temp_cmd = new TCPCommand ();
    temp_cmd->setConnId (connID);
    temp_msg->setControlInfo (temp_cmd);

    TCPSocket *socket = this->socketMap_.findSocketFor (temp_msg);

    if (!socket) {
        EV << ">>> Cannot find socket to send request <<< " << endl;
    } else {

        this->socketMap_.removeSocket(socket);
    }

    EV << "=== Server: " << this->localAddress_ << " received socketPeerClosed message" << endl;
    EV << "socket closed for connID = " << connID << endl;

    delete socket; // cleanup
    delete temp_msg;
}

