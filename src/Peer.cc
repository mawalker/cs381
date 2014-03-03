/*
 * P2PApp.cc
 *
 *  Modified Class from CS381 P2PApp.cc
 */

#include "Peer.h"         // our header
#include "IPvXAddressResolver.h"

#include "PeerToPeerMSG_m.h"
#include "PeerToTrackerMsg_m.h"

Define_Module(Peer)
;

Peer::Peer(void) {
    // nothing
}

Peer::~Peer() {
    // nothing
}

// the initialize method
void Peer::initialize(int stage) {
    cSimpleModule::initialize(stage);
    if (stage != 3)
        return;

    // obtain the values of parameters
    this->localAddress_ = this->par("localAddress").stringValue();
    this->localPort_ = this->par("localPort");
    this->numPeers_ = this->par("numPeers");
    this->connectPort_ = this->par("connectPort");
    this->numChunksInFile_ = this->par("numChunksInFile");
    this->trackerAddress_ = this->par("trackerAddress").stringValue();
    this->numPeersConnected_ = 0;

    this->numChunksToGet_.setName("Chunks to Get");

    this->newChunkRecieved.setName("Chunk Received" + this->localPort_);

    // initialization
    vector<int> v;
    this->ownedChunks_ = v;
    this->chunksToGet_ = v;
    map<string, vector<int> > m;
    this->peersToChunkMap_ = m;

    this->startAsSeed_ = this->par("startAsSeed");

    // setup initial file state, either seed or leech
    if (this->startAsSeed_ == true) { // seed
        EV<< "+++ Peer: " << this->localAddress_ << "Started as Seed +++" << endl;
        for (int i = 0; i < (int)this->numChunksInFile_; i++) {
            insertChunk(i);
        }

    } else { // leech
        EV<< "+++ Peer: " << this->localAddress_ << "Started as Leech +++" << endl;
        for (int i = 0; i < (int)this->numChunksInFile_; i++) {
            this->chunksToGet_.push_back(i);
        }
    }

    this->initNumOwnedChunks_ = this->ownedChunks_.size();

    for (int i = 0; i < this->numChunksInFile_; i++) {
        // check if we already have this chunk
        bool found = false;
        for (size_t j = 0; j < this->ownedChunks_.size(); j++) {
            int chunk = this->ownedChunks_[j];
            // already have the chunk
            if (i == chunk) {
                found = true;
                break;
            }
        }
        if (!found)
            this->chunksToGet_.push_back(i);
    }

    // indicate what type of data transfer is going to be supported by our socket
    // there are three choices supported in INET. For now we choose BYTECOUNT, i.e.,
    // the underlying system will emulate the sending of that many bytes. We
    // are not concerned with the actual content. But if we really wanted to do it
    // that way, then we will do BYTESTREAM
    string dataTransferMode = this->par("dataTransferMode").stringValue();

    // create a new socket for the LISTENING role
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

    // tracker is active
    bool *passive1 = new bool(false);
    tracker_socket->setCallbackObject(this, passive1);

    // do not forget to set the outgoing gate
    tracker_socket->setOutputGate(gate("tcpOut"));

    // another thing I learned the hard way is that we must set up the data trasnfer
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

    if (this->startAsSeed_ == true) {
        this->sendP2TRequest(this->trackerSocket_->getConnectionId(),
                P2T_DOWNLOAD_COMPLETE);
    }

    cMessage *timer_msg = new cMessage("timer");
    this->scheduleAt(simTime() + exponential(0.01), timer_msg);

    setStatusString("waiting");

    EV<< "+++ Peer: " << this->localAddress_
    << " has these chunks:" << initNumOwnedChunks_<<endl;

}

    /** the all serving handle message method */
void Peer::handleMessage(cMessage *msg) {
    EV<< "=== Peer: " << this->localAddress_
    << " received handleMessage message" << endl;

    // check if this was a self generated message, such as a timeout to wake us up to
    // connect to a peer
    if (msg->isSelfMessage())
    this->handleTimer(msg);
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
                        "Peer::handleMessage: no TCPCommand control info in message (not from TCP?)");
            } else {
                EV << "=== Peer: " << this->localAddress_
                << " **No socket yet ** ===" << endl;

                int connId = cmd->getConnId();
                // debugging
                EV << "+++ Peer: " << this->localAddress_
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
            socket->processMessage(msg);}
    }
}

    /** this method is provided to clean things up when the simulation stops */
void Peer::finish() {
    EV<< "=== finish called" << endl;

    // cleanup all the sockets
    this->socketMap_.deleteSockets();

    std::string modulePath = getFullPath();
}

    /** handle the timeout method */
void Peer::handleTimer(cMessage *msg) {

    EV<< "=== Peer: " << this->localAddress_
    << " received handleTimer message. "
    << "Send refresh request to Tracker" << endl;

    // perform cleanup
    delete msg;

    // find latest info about peers
    this->sendP2TRequest(this->trackerSocket_->getConnectionId(), P2T_REFRESH_REQUEST);

    // schedule next timer
    cMessage *timer_msg = new cMessage("timer");
    this ->scheduleAt(simTime() + exponential(0.01), timer_msg);

}

    /*************************************************/
    /** implement all the callback interface methods */
    /*************************************************/

void Peer::socketEstablished(int connID, void *role) {
    EV<< "=== Peer: " << this->localAddress_
    << " received socketEstablished message on connID " << connID
    << " ===" << endl;

    setStatusString("ConnectionEstablished");

    // now that the connection is established, if we are the active entity that opens a
    // connection, then we initiate the next data transfer with the peer
    bool *passive = static_cast<bool *>(role);
    if (*passive) {
        EV << "=== We are in passive role and hence just wait for an incoming req ===" << endl;
    } else {
        EV << "=== We are in active role and hence initiate a req ===" << endl;

        // if connection with the tracker is established
        if (connID == this->trackerSocket_->getConnectionId()) {

            this->sendP2TRequest(connID, P2T_REG_REQUEST);
        } else { // else this is a connection with peer

            map<int, int>::iterator mapIt;
            mapIt = this->connToChunkMap_.find(connID);
            if (mapIt != this->connToChunkMap_.end()) {
                this->sendRequest(connID, mapIt->second);
            }

        }

    }
}

    /** handle incoming data. Could be a request or response */
void Peer::socketDataArrived(int connID, void *, cPacket *msg, bool) {

    EV<< "=== Peer: " << this->localAddress_
    << " received socketDataArrived message. ===" << endl;

    // incoming request may be of different types

    P2T_Packet *packet = dynamic_cast<P2T_Packet *>(msg);
    if (packet) {

        switch ((P2T_MSG_TYPE) packet->getType()) {
            case T2P_MEMBER_RESPONSE: {
                T2P_MEMBER_Res *res = dynamic_cast<T2P_MEMBER_Res *>(msg);
                if (!res) {
                    EV << "Arriving packet is not of type T2P_MEMBER_Res"
                    << endl;
                } else {
                    setStatusString("Tracker Response");
                    EV << "Received response from tracker" << endl;

                    for (int i = 0; i < (int)res->getChunksOwnedArraySize(); i++) {
                        CHUNKS_OWNED_Msg chunksOwnedMsg =
                        res->getChunksOwned(i);
                        string id = chunksOwnedMsg.getId();

                        // get the chunks downloaded
                        vector<int> chunksD;
                        for (int i = 0; i < (int)chunksOwnedMsg.getDownloadedChunksArraySize(); i++) {
                            chunksD.push_back(
                                    chunksOwnedMsg.getDownloadedChunks(i));
                        }

                        // add info about the peer owning given chunks
                        this->peersToChunkMap_.insert(
                                pair<string, vector<int> >(id, chunksD));

                    }

                    // add peer to the list of all peers
                    for (int i = 0; i < (int)res->getIdsArraySize(); i++) {
                        this->peers_.push_back(res->getIds(i));
                    }

                    downloadChunks();
                }
            }
            break;
            default:
            EV << ">>> unknown response type <<< " << endl;
            break;
        }

    } else {
        P2P_Packet *packet1 = dynamic_cast<P2P_Packet *>(msg);
        if (!packet1) {
            return;
        }
        switch ((P2P_MSG_TYPE) packet1->getType()) {

            case P2P_REQUEST: {
                P2P_Req *req = dynamic_cast<P2P_Req *>(msg);
                if (!req) {
                    EV << "Arriving packet is not of type P2P_Req" << endl;
                } else {
                    setStatusString("Peer Request");
                    EV << "Arriving packet: Requestor ID = " << req->getId()
                    << ", Requested chunk = " << req->getChunkNo() << endl;

                    this->sendResponse(connID, req->getChunkNo());
                }
            }
            break;

            case P2P_RESPONSE: {
                P2P_Resp *resp = dynamic_cast<P2P_Resp *>(msg);
                if (!resp) {
                    EV << "Arriving packet is not of type P2P_Resp" << endl;
                } else {
                    setStatusString("Response");
                    EV << "Arriving packet: Responder ID = " << resp->getId()
                    << ", requested chunk = " << resp->getChunkNo()
                    << endl;

                    int chunk = resp->getChunkNo();

                    insertChunk(chunk); // insert chunk for download
                    deleteChunk(chunk);// delete chunk from the list of chunks to download

                    if ((int)this->ownedChunks_.size() >= this->numChunksInFile_) {
                        this->sendP2TRequest(this->trackerSocket_->getConnectionId(),
                                P2T_DOWNLOAD_COMPLETE);
                    }

                    int numChunksRemaining = this->ownedChunks_.size() - this->numChunksInFile_;
                    this->numChunksToGet_.record(numChunksRemaining);

                    this->sendP2TRequest(this->trackerSocket_->getConnectionId(),
                            P2T_REFRESH_REQUEST);

                    // get next chunk if such exists
                    vector<int> chunksForPeer = this->peersToChunkMap_.find(
                            resp->getId())->second;

                    int index = 0;
                    for (int i = 0; i < (int)chunksForPeer.size(); i++) {
                        if (chunk == chunksForPeer[i]) {
                            // this is the downloaded chunk
                            index = i;
                            break;
                        }
                    }

                    // see if we have next chunk to get
                    int nextChunk = -1;
                    for (int i = index + 1; i < (int)chunksForPeer.size(); i++) {
                        int ch = chunksForPeer[i];
                        bool found = false;
                        for (size_t j = 0; j < this->chunksToGet_.size(); j++) {
                            if (ch == this->chunksToGet_[j]) {
                                found = true;
                                break;
                            }
                        }

                        if (found) {
                            nextChunk = ch;
                            break;
                        }
                    }

                    // if next chunk is not found, diconnect
                    if (nextChunk == -1) {
                        cMessage *temp_msg = new cMessage("temp");
                        TCPCommand *temp_cmd = new TCPCommand();
                        temp_cmd->setConnId(connID);
                        temp_msg->setControlInfo(temp_cmd);
                        TCPSocket *socket = this->socketMap_.findSocketFor(
                                temp_msg);

                        socket->close();
                    } else { // else get next chunk
                        this->sendRequest(connID, nextChunk);
                    }

                }

            }
            break;
            default:
            EV << ">>> unknown incoming request type <<< " << endl;
            break;
        }

    }

    // cleanup
    delete msg;
}

void Peer::socketPeerClosed(int connID, void *) {
    EV<< "=== Peer: " << this->localAddress_
    << " received socketPeerClosed message" << endl;
    EV << "peer closed for connID = " << connID << endl;

    cMessage *temp_msg = new cMessage("temp");
    TCPCommand *temp_cmd = new TCPCommand();
    temp_cmd->setConnId(connID);
    temp_msg->setControlInfo(temp_cmd);
    TCPSocket *socket = this->socketMap_.findSocketFor(temp_msg);
    this->socketMap_.removeSocket(socket);
    setStatusString("peer closed");

}

void Peer::socketClosed(int connID, void *) {
    EV<< "=== Peer: " << this->localAddress_
    << " received socketClosed message" << endl;
    // *redefine* to start another session etc.
    EV << "connection closed\n";

    cMessage *temp_msg = new cMessage("temp");
    TCPCommand *temp_cmd = new TCPCommand();
    temp_cmd->setConnId(connID);
    temp_msg->setControlInfo(temp_cmd);
    TCPSocket *socket = this->socketMap_.findSocketFor(temp_msg);
    this->socketMap_.removeSocket(socket);
    setStatusString("closed");
}

void Peer::socketFailure(int, void *, int code) {
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
int Peer::connect(string peer) {
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

// close the peer side
void Peer::close() {
    EV<< "=== Peer: " << this->localAddress_ << " received close () message"
    << endl;
    EV << "issuing CLOSE command\n";

    setStatusString("closing");

    this->socket_->close();
}

// send a request to the other side
void Peer::sendP2TRequest(int connId, enum P2T_MSG_TYPE prt_msg_type) {

    EV<< "=== Peer: " << this->localAddress_ << " sendRequest. " << endl;

    cMessage *temp_msg = new cMessage("temp");
    TCPCommand *temp_cmd = new TCPCommand();
    temp_cmd->setConnId(connId);
    temp_msg->setControlInfo(temp_cmd);

    TCPSocket *socket = this->socketMap_.findSocketFor(temp_msg);
    if (!socket) {
        EV << ">>> Cannot find socket to send request <<< " << endl;
    } else {

        switch (prt_msg_type) {
            case P2T_REG_REQUEST: {
                CHUNKS_OWNED_Msg *req = new CHUNKS_OWNED_Msg();
                req->setType((int) P2T_REG_REQUEST);
                req->setId(this->localAddress_.c_str());
                req->setDownloadedChunksArraySize((int)this->ownedChunks_.size());
                for (int i = 0; i < (int)this->ownedChunks_.size(); i++) {
                    req->setDownloadedChunks(i, this->ownedChunks_[i]);
                }
                req->setByteLength(256); // I think we can set any length we want :-)
                socket->send(req);
                break;
            }
            case P2T_REFRESH_REQUEST: {
                CHUNKS_OWNED_Msg *refresh_req = new CHUNKS_OWNED_Msg();
                refresh_req->setType((int) P2T_REFRESH_REQUEST);
                refresh_req->setId(this->localAddress_.c_str());
                refresh_req->setDownloadedChunksArraySize((int)this->ownedChunks_.size());
                for (int i = 0; i < (int)this->ownedChunks_.size(); i++) {
                    refresh_req->setDownloadedChunks(i, this->ownedChunks_[i]);
                }
                refresh_req->setByteLength(256); // I think we can set any length we want :-)
                socket->send(refresh_req);
                break;
            }
            case P2T_DOWNLOAD_COMPLETE : {
                P2T_DOWNLOAD_COMPLETE_Msg *complete_req = new P2T_DOWNLOAD_COMPLETE_Msg();
                complete_req->setType((int) P2T_DOWNLOAD_COMPLETE);
                complete_req->setId(this->localAddress_.c_str());
                complete_req->setByteLength(32); // I think we can set any length we want :-)
                socket->send(complete_req);
            }
            default:
            EV << ">>> unknown incoming request type <<< " << endl;
            break;

        }
    }
    // cleanup
    delete temp_msg;
}

void Peer::downloadChunks() {

    EV<< this->localAddress_ << " is about to download chunks: ";

    for (size_t i = 0; i < this->chunksToGet_.size(); i++)
    EV << this->chunksToGet_[i] << " ";

    if (this->chunksToGet_.size() == 0) {
        EV << endl << this->localAddress_ << " completed download " << endl;
    }

    map<string, vector<int> >::iterator it;
    set<int> chunksChosen;

    for (it = this->peersToChunkMap_.begin(); it != this->peersToChunkMap_.end();
            ++it) {

        if (this->numPeersConnected_ >= this->numPeers_) {
            return;
        }

        string peer = (*it).first.c_str();

        if (peer.compare(this->localAddress_) != 0) { // make sure we are not talking to ourselves

            vector<int> chunks = it->second;
            for (int k = 0; k < it->second.size(); k++) {

                // if peer already has this chunk
                bool found = false;

                for (size_t i = 0; i < this->chunksToGet_.size(); i++) {

                    // need to download the chunk
                    if (chunks[k] == chunksToGet_[i]) {
                        set<int>::iterator iter;
                        iter = chunksChosen.find(chunks[k]);

                        // chunk has already been chosen, find next
                        if (iter != chunksChosen.end()){
                            break;
                        }

                        // connect to this peer
                        chunksChosen.insert(chunks[k]);
                        this->connToChunkMap_.insert(
                                pair<int, int>(connect(peer), chunks[k]));
                        this->peersConnected_.push_back(peer);
                        this->numPeersConnected_++;
                        found = true;
                        break;
                    }
                }
                if (found)
                break;
            }
        }
    }
}

// Peer to Peer request
void Peer::sendRequest(int connId, int chunkNo) {
    EV<< "=== Peer: " << this->localAddress_ << " sendRequest. " << endl;

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
        req->setChunkNo(chunkNo);
        // need to set the byte length else nothing gets sent as I found the hard way
        req->setByteLength(32);// I think we can set any length we want :-)

        socket->send(req);
    }

// cleanup
    delete temp_msg;
}

// send a response
void Peer::sendResponse(int connId, int chunkNo) {
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

        P2P_Resp *resp = new P2P_Resp();
        resp->setType((int) P2P_RESPONSE);
        resp->setId(this->localAddress_.c_str());
        resp->setChunkNo(chunkNo);
        // need to set the byte length else nothing gets sent as I found the hard way
        resp->setByteLength(1024);// I think we can set any length we want :-)

        // return the response chunk
        socket->send(resp);
    }

// cleanup
    delete temp_msg;
}

void Peer::insertChunk(int chunkNo) {

    if (this->ownedChunks_.empty()) {
        this->ownedChunks_.push_back(chunkNo);
        this->newChunkRecieved.record(chunkNo);
        return;
    }

    int index = 0;
    bool found = false;
    for (size_t i = 0; i < this->ownedChunks_.size(); i++) {
        if (this->ownedChunks_[i] > chunkNo) {
            index = i;
            found = true;
            break;
        } else if (this->ownedChunks_[i] == chunkNo){
            return;
        }

    }

    if (!found){
        index = this->ownedChunks_.size();
    }

    this->ownedChunks_.insert(this->ownedChunks_.begin() + index,
            chunkNo);

    this->newChunkRecieved.record(chunkNo);
}

void Peer::deleteChunk(int chunkValue) {
    for (size_t i = 0; i < this->chunksToGet_.size(); i++) {
        if (this->chunksToGet_[i] == chunkValue) {
            this->chunksToGet_.erase(this->chunksToGet_.begin() + i);
            return;
        }
    }

}

void Peer::setStatusString(const char *s) {
    if (ev.isGUI()) {
        getDisplayString().setTagArg("t", 0, s);
        bubble(s);
    }
}

