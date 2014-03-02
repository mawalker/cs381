/*
 * ClientApp.cc
 *
 *  Created on: Feb 1, 2014
 *      Author: Aniruddha Gokhale
 *      Class:  CS381
 *      Institution: Vanderbilt University
 */

// An application logic for Client behavior. This code has been developed by
// modifying the code in TCPBasicClientApp and TCPGenericSrvApp available
// in the INET framework
#include "PeerToPeerMSG_m.h"    // generated header from the message file
#include "Peer.h"               // our header
#include "IPvXAddressResolver.h"     // manages both IPv4 and IPV6 addess resolution
// this is needed by OMNeT++ because it registers our C++ class with the underlying
// OMNeT simulator upon which all the callbacks can be made when events occur
Define_Module(Peer)
;

// constructor
Peer::Peer(void) :
        myID_(), server_(), connectPort_(0), fileSize_(1024), // 1 Kilo bytes
        numAttempts_(1), dataTransferMode_(TCP_TRANSFER_OBJECT), socket_(NULL) {
    // nothing
}

// destructor
Peer::~Peer() {
    // nothing
}

// the initialize method. We initialize the parameter. Connection to the server is done after an event is triggered
void Peer::initialize(int stage) {
    cSimpleModule::initialize(stage);
    if (stage != 3)
        return;

    // get values from the parameters from the ini file
    this->myID_ = this->par("myID").stringValue();
    this->server_ = this->par("connectAddress").stringValue();
    this->connectPort_ = this->par("connectPort");
    this->fileSize_ = this->par("fileSize");
    this->numAttempts_ = this->par("numAttempts");
    this->startAsSeed_ = this->par("startAsSeed");

    // obtain the values of parameters
    this->localAddress_ = this->par("localAddress").stringValue();
    this->localPort_ = this->par("localPort");
    this->numPeers_ = this->par("numPeers");
    this->connectPort_ = this->par("connectPort");
    this->numberOfChunksInFile_ = this->par("numberOfChunksInFile");
    this->trackerAddress_ = this->par("trackerAddress").stringValue();
    this->numPeersConnected_ = 0;

    this->numberOfchunksToDownload.setName("Remaining Chunks");

    // indicate what type of data transfer is going to be supported by our socket
    // there are three choices supported in INET. For now we choose BYTECOUNT, i.e.,
    // the underlying system will emulate the sending of that many bytes. We
    // are not concerned with the actual content. But if we really wanted to do it
    // that way, then we will do BYTESTREAM
    string dataTransferMode = this->par("dataTransferMode").stringValue();

    if (!dataTransferMode.compare("bytecount"))
        this->dataTransferMode_ = TCP_TRANSFER_BYTECOUNT;
    else if (!dataTransferMode.compare("object"))
        this->dataTransferMode_ = TCP_TRANSFER_OBJECT;
    else if (!dataTransferMode.compare("bytestream"))
        this->dataTransferMode_ = TCP_TRANSFER_BYTESTREAM;
    else { // error
        EV<< "=== Client: Bad data transfer mode value. Assuming BYTESTREAM" << endl;
        this->dataTransferMode_ = TCP_TRANSFER_BYTESTREAM;
    }

        // Debugging purposes
    EV<< "Peer " << this->myID_ << " is initialized with transfer mode = "
    << dataTransferMode << " for file size of " << this->fileSize_
    << " and server details: name = " << this->server_
    << " and port = " << this->connectPort_ << endl;

   // initialize
   vector<int> v;
   this->ownedChunks_ = v;
   this->chunksToDownload_ = v;
   map<string, vector<int> > m;
   this->peersToChunkMap_ = m;

    // setup initial file state, either seed or leech
    if (this->startAsSeed_ == true) { // seed
        for (int i = 0; i < this->numberOfChunksInFile_; i++) {
            insertChunkInOrder(i);
        }
    } else { // leech
        for (int i = 0; i < this->numberOfChunksInFile_; i++) {
            this->chunksToDownload_.push_back(i);
        }
    }
    this->initialCountOfOwnedChunks_ = this->ownedChunks_.size();

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

    // Create a connection to TRACKER and send REGISTRATION Message
    // make connection with TRACKER

    // debugging
    EV<< "+++ Peer: " << this->localAddress_
    << " creating a new socket with Tracker" << endl;

    TCPSocket *tracker_socket = new TCPSocket();

    // register ourselves as the callback object - we are active here
    bool *passive2 = new bool(false);
    tracker_socket->setCallbackObject(this, passive2);

    // do not forget to set the outgoing gate
    tracker_socket->setOutputGate(gate("tcpOut"));

    // another thing I learned the hard way is that we must set up the data transfer
    // mode for this new socket
    tracker_socket->setDataTransferMode(this->socket_->getDataTransferMode());

    // now save this socket in our map
    this->socketMap_.addSocket(tracker_socket);

    // issue a connect request to TRACKER
    tracker_socket->connect(
            IPvXAddressResolver().resolve(this->trackerAddress_.c_str()),
            this->connectPort_);

    // save this socket
    this->trackerSocket_ = tracker_socket;

    // now we start a timer so that when it kicks in, we make a connection to the server.
    // this event serves as a way to kickstart things.
    cMessage *timer_msg = new cMessage("connect_timer");
    this->scheduleAt(simTime() + exponential(0.001), timer_msg);

    setStatusString("waiting");

}

void Peer::sendP2TRequest(int connId, enum P2T_MSG_TYPE prt_msg_type) {
    EV << "=== Peer: " << this->localAddress_ << " sendRequest. " << endl;

        cMessage *temp_msg = new cMessage("temp");
        TCPCommand *temp_cmd = new TCPCommand();
        temp_cmd->setConnId(connId);
        temp_msg->setControlInfo(temp_cmd);

        TCPSocket *socket = this->socketMap_.findSocketFor(temp_msg);
        if (!socket) {
            EV << ">>> Cannot find socket to send request <<< " << endl;
        } else {

            switch (prt_msg_type) {
            case P2T_REGISTRATION_REQUEST: {
                Ownership_Message *req = new Ownership_Message();
                req->setType((int) P2T_REGISTRATION_REQUEST);
                req->setId(this->localAddress_.c_str());
                int size = this->ownedChunks_.size();
                req->setOwned_chunksArraySize(size);
                for (int i = 0; i < size; i++) {
                    req->setOwned_chunks(i, this->ownedChunks_[i]);
                }
                req->setByteLength(256); // I think we can set any length we want :-)
                socket->send(req);
                break;
            }
            case P2T_REFRESH_MESSAGE: {
                Ownership_Message *refresh_req = new Ownership_Message();
                refresh_req->setType((int) P2T_REFRESH_MESSAGE);
                refresh_req->setId(this->localAddress_.c_str());
                int size = this->ownedChunks_.size();
                refresh_req->setOwned_chunksArraySize(size);
                for (int i = 0; i < size; i++) {
                    refresh_req->setOwned_chunks(i, this->ownedChunks_[i]);
                }
                refresh_req->setByteLength(256); // I think we can set any length we want :-)
                socket->send(refresh_req);
                break;
            }
            case P2T_DOWNLOAD_COMPLETE: {
                P2T_DOWNLOAD_COMPLETE_Msg *complete_req = new P2T_DOWNLOAD_COMPLETE_Msg();
                complete_req->setType((int) P2T_DOWNLOAD_COMPLETE);
                complete_req->setId(this->localAddress_.c_str());
                complete_req->setByteLength(32); // I think we can set any length we want :-)
                socket->send(complete_req);
                break;
            }
            default:
                EV << ">>> unknown incoming request type <<< " << endl;
                break;

            }
        }
        // cleanup
        delete temp_msg;

}

void Peer::sendResponse(int connId, int chunk) {

    EV << "=== Peer: " << this->localAddress_ << " sendResponse. " << endl;

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

            P2P_Resp *resp = new P2P_Resp();
            resp->setType((int) P2P_RESPONSE);
            resp->setId(this->localAddress_.c_str());
            resp->setRequestedChunk(chunk);
            // need to set the byte length else nothing gets sent as I found the hard way
            resp->setByteLength(1024); // I think we can set any length we want :-)

            // return the response chunk
            socket->send(resp);
        }

    // cleanup
        delete temp_msg;

}

void Peer::connectAndDownloadChunks() {

    EV << "PACKETS YET TO BE DOWNLOADED BY  " << this->localAddress_ << " : ";

       for (size_t i = 0; i < this->chunksToDownload_.size(); i++)
           EV << this->chunksToDownload_[i] << " ";

       if (this->chunksToDownload_.size() == 0)
           EV << endl << "FILE DOWNLOAD COMPLETED FOR " << this->localAddress_ << endl;
       // need to connect to peers having chunk which we dont have

       // loop through each peer and check which of them have to the chunk to download
       // iterator for peer and chunk map
       map<string, vector<int> >::iterator it;

       // should also handle the case foe refresh message
       set<int> chunksAlreadyEnqueued;

       for (it = this->peersToChunkMap_.begin(); it != this->peersToChunkMap_.end();
               ++it) {

           if (this->numPeersConnected_ >= this->numPeers_)
               // already have sufficient connections, return
               return;

           string peer = (*it).first.c_str();

           // need to make sure we are ourselves not this peer
           if (peer.compare(this->localAddress_) == 0)
               continue;

           // make sure we are not already connected to this peer
           bool peerFound = false;
           for (size_t j = 0; j < this->peersConnected_.size(); j++) {
               if (peer.compare(this->peersConnected_[j]) == 0) {
                   peerFound = true;
                   break;
               }
           }

           // already connected to this peer, lets move to next
           if (peerFound)
               continue;

           int chunkVectorSize = it->second.size();
           vector<int> chunks = it->second;
           for (int k = 0; k < chunkVectorSize; k++) {

               // need to find if this peer has this chunk
               bool chunkFound = false;

               for (size_t i = 0; i < this->chunksToDownload_.size(); i++) {

                   // this means we have to download this chunk from peer
                   if (chunks[k] == chunksToDownload_[i]) {
                       set<int>::iterator setiter;
                       setiter = chunksAlreadyEnqueued.find(chunks[k]);

                       // this chunk is already enqueued for download, we should look at next chunk in the peer
                       if (setiter != chunksAlreadyEnqueued.end())
                           break;

                       // connect to this peer
                       chunksAlreadyEnqueued.insert(chunks[k]);
                       this->connToChunkMap_.insert(
                               pair<int, int>(connect(peer), chunks[k]));
                       this->peersConnected_.push_back(peer);
                       this->numPeersConnected_++;
                       chunkFound = true;
                       break;
                   }
               }
               if (chunkFound)
                   break;
           }
       }
}

/** This is the all-encompassing event handling function. It is our responsibility to
 *  figure out what to do with every event, which is appln-specific */
void Peer::handleMessage(cMessage *msg) {
    EV<< "Client received handleMessage message" << endl;

    // check if this was a self generated message, such as a timeout to wake us up to
    // connect to the server
    if (msg->isSelfMessage ())
    this->handleTimer (msg);
    else {  // not a timer; must be a packet.

        // Because we are a client and we should have already called "connect" to the server as part of the
        // handleTimer, the possibilities are that this is an incoming ack for the connection establishment,
        // or a response to our request, or a connection close message. Unlike the server, we do not have
        // any socket map with us. We just have one socket: the one to talk to the server, which should have
        // been created as a result of the timer above.

        // make sure first that we are dealing with a TCP command (and not something else) because otherwise
        // we do not know how to handle that kind of message
        TCPCommand *cmd = dynamic_cast<TCPCommand *>(msg->getControlInfo());
        if (!cmd) {
            throw cRuntimeError("Peer::handleMessage: no TCPCommand control info in message (not from TCP?)");
        }

        // for the sake of correctness, we make sure the socket exists
        if (!this->socket_) {  // no socket. How did we come here?
            throw cRuntimeError("Peer::handleMessage: no connection yet to server");
        }

        // Everything seems fine. So process the message. Note that the processMessage is a method defined on the
        // TCPSocket class. Internally it will make the appropriate callback on the overridden methods of the
        // TCPSocketCallbackInterface object
        this->socket_->processMessage (msg);
    }
}

    /** this method is provided to clean things up when the simulation stops and all statistics collection should be finalized here */
void Peer::finish() {
    EV<< "=== finish called" << endl;

    std::string modulePath = getFullPath();
    EV << "=== Client: Before cleaning up socket, it remains in "
    << this->socket_->stateName (this->socket_->getState ()) << " state ====" << endl;

    // our socket is closed. Clean it.
    delete this->socket_;
}

    /** handle the timeout method. We are using this as the initial method to kick start the process */
void Peer::handleTimer(cMessage *msg) {
    EV << "=== Peer: " << this->localAddress_
            << " received handleTimer message. "
            << "Send refresh request to Tracker" << endl;

    // perform cleanup
    delete (msg);

    // We need to send the status to Tracker and find the latest list of peers
    this->sendP2TRequest(this->trackerSocket_->getConnectionId(),
            P2T_REFRESH_MESSAGE);

    // schedule the next timer
    cMessage *timer_msg = new cMessage("timer");
    this ->scheduleAt(simTime() + exponential(0.01), timer_msg);
}

    /*************************************************/
    /** implement all the callback interface methods */
    /*************************************************/

// when the client actively establishes a connection to the server, and if it is successful,
// this callback will be invoked so that we can do the next set of things. In our case it is as
// simple as telling the server that we are interested in a file of a certain size.
//
// Note that the second parameter is going to be NULL because we did not
// provide any param when registering ourself with the callback.
void Peer::socketEstablished(int connID, void *role) {
    EV<< "=== Client: " << this->myID_
    << " received socketEstablished message on connID " << connID << " ===" << endl;

    // just to make sure some random stuff did not show up for our second param
    if (role != NULL) {
        throw cRuntimeError("Peer::socketEstablished -- unrecognized param in callback");
    }

    // bubble during animation
    setStatusString("ConnectionEstablished");

    // send requests to the server to whom we just got connected
    //this->sendRequest (connID);
}

    /** handle incoming data. Could be a request or response */
void Peer::socketDataArrived(int connID, void *, cPacket *msg, bool) {
//    EV << "=== Client: " << this->myID_
//       << " received socketDataArrived message. ===" << endl;
//
//    // incoming request may be of different types. The only thing we can handle as a client
//    // is a response from the server and nothing else.
//    CS_Resp *response = dynamic_cast<CS_Resp *> (msg);
//    if (!response) {
//      EV << "Arriving packet is not of type CS_Resp" << endl;
//    } else {
//       setStatusString ("Response Arrived");
//
//       EV << "Arriving packet: Responder ID = " << response->getId ()
//          << ", packet size = " << response->getDataArraySize () << endl;
//
//       this->handleResponse (response);
//    }
//
//    // cleanup the incoming message after it is handled.
//    delete response;
//
//    // now that the response to our file request is received, our job is done
//    // and so we close the connection
//    this->close ();

}

void Peer::socketPeerClosed(int connID, void *) {
    EV<< "=== Client: " << this->myID_ << " received socketPeerClosed message" << endl;
    EV << "server closed for connID = " << connID << endl;

    // in our case, we are not asking our server to initiate closing the socket. Instead the client
    // will do so once it gets the response.
}

void Peer::socketClosed(int, void *) {
    // for some odd reason, we are never getting invoked here. My understanding was that
    // after we explicitly call close, we should be getting here thru a callback.

    EV<< "=== Client: " << this->myID_ << " received socketClosed message" << endl;
    setStatusString("connection closed");

    EV << "=== Client: Before cleaning up socket, it remains in "
    << this->socket_->stateName (this->socket_->getState ()) << " state ====" << endl;

    // our socket is closed. Clean it.
    delete this->socket_;

}

void Peer::socketFailure(int, void *, int code) {
    EV<< "=== Client: " << this->myID_ << " received socketFailure message" << endl;
    // subclasses may override this function, and add code try to reconnect after a delay.
    EV << "connection broken\n";
    setStatusString("broken");

    // so we end the simulation
    endSimulation ();
}

    /**********************************************************************/
    /**           helper methods                                          */
    /**********************************************************************/

// connect to server in the active role
int Peer::connect(string peer) {
    EV << "=== Peer: " << this->localAddress_ << " received connect message"
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
    new_socket->connect(IPvXAddressResolver().resolve(peer.c_str()),
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

    return new_socket->getConnectionId();

}

// close the client
void Peer::close() {
    EV<< "=== Client: " << this->myID_ << " received close () message" << endl;
    EV << "issuing CLOSE command\n";

    setStatusString("closing");

    this->socket_->close ();

    // now this is a hack (particularly for wireless mode) because we would like to stop the simulation after
    // the client has received the file. But because the nodes keep moving, they will keep generating
    // events and our simulation will never end unless we force it by limiting the time the
    // simulation runs. So we use the timer trick.

    // now we start a timer so that when it kicks in we shut down the simulation
    cMessage *timer_msg = new cMessage ("end_sim");
    this->scheduleAt (simTime () + 0.05, timer_msg);
}

// send a request to the other side
void Peer::sendRequest(int connId, int chunk) {
    EV << "=== Peer: " << this->localAddress_ << " sendRequest. " << endl;

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
        P2P_Req *req = new P2P_Req();
        req->setType((int) P2P_REQUEST);
        req->setId(this->localAddress_.c_str());
        req->setChunk(chunk);
        // need to set the byte length else nothing gets sent as I found the hard way
        req->setByteLength(32); // I think we can set any length we want :-)

        socket->send(req);
    }

// cleanup
    delete temp_msg;

}


void Peer::insertChunkInOrder(int chunkValue) {

    if (this->ownedChunks_.empty()) {
        this->ownedChunks_.push_back(chunkValue);
        return;
    }

    int chunkInsertionNumber = 0;
    bool found = false;
    for (size_t i = 0; i < this->ownedChunks_.size(); i++) {
        if (this->ownedChunks_[i] > chunkValue) {
            chunkInsertionNumber = i;
            found = true;
            break;
        } else if (this->ownedChunks_[i] == chunkValue)
            // already have this chunk, ignore
            return;

    }

    if (!found)
        chunkInsertionNumber = this->ownedChunks_.size();

    this->ownedChunks_.insert(this->ownedChunks_.begin() + chunkInsertionNumber,
            chunkValue);
}

void Peer::deleteChunkFromToDownloadList(int chunkValue) {
    for (size_t i = 0; i < this->chunksToDownload_.size(); i++) {
        if (this->chunksToDownload_[i] == chunkValue) {
            this->chunksToDownload_.erase(
                    this->chunksToDownload_.begin() + i);
            return;
        }
    }

}

// this method is used to flash messages during animation where we can see bubbles on the screen.
void Peer::setStatusString(const char *s) {
    if (ev.isGUI ()) {
        getDisplayString ().setTagArg ("t", 0, s);
        bubble (s);
    }
}

