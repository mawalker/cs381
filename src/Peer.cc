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
    this->numChunksInFile_ = this->par("numberOfChunksInFile");
    this->trackerAddress_ = this->par("trackerAddress").stringValue();
    this->numPeersConnected_ = 0;

    this->numChunksToGet_.setName("Remaining Chunks");

    this->newChunkRecieved.setName("New Chunk Received" + this->localPort_);

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
            insertChunkInOrder(i);
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

    // register ourselves as the callback object - we are active here
    bool *passive2 = new bool(false);
    tracker_socket->setCallbackObject(this, passive2);

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

    // now we start a timer so that when it kicks in, we send refresh request to Tracker

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
    delete (msg);

    // We need to send the status to Tracker and find the latest list of peers
    this->sendP2TRequest(this->trackerSocket_->getConnectionId(),
            P2T_REFRESH_REQUEST);

    // schedule the next timer
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
        EV
        << "=== We are in passive role and hence just wait for an incoming req ==="
        << endl;
    } else {
        EV << "=== We are in active role and hence initiate a req ===" << endl;

        // Connection established with Tracker
        if (connID == this->trackerSocket_->getConnectionId()) {
            // send the request to the tracker from whom we need a response
            this->sendP2TRequest(connID, P2T_REG_REQUEST);
        } else {
            // send requests to the peer to whom we just got connected
            map<int, int>::iterator connIter;
            connIter = this->connToChunkMap_.find(connID);
            if (connIter != this->connToChunkMap_.end()) {
                this->sendRequest(connID, connIter->second);
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
        // handle P2T message
        switch ((P2T_MSG_TYPE) packet->getType()) {
            case T2P_MEMBER_RESPONSE: {
                T2P_MEMBER_Res *res = dynamic_cast<T2P_MEMBER_Res *>(msg);
                if (!res) {
                    EV << "Arriving packet is not of type T2P_MEMBERSHIP_Res"
                    << endl;
                } else {
                    setStatusString("Tracker Response");
                    EV << "Response arrived from tracker" << endl;

                    int sizeOfMessages = res->getPeer_to_chunk_ownershipArraySize();
                    for (int i = 0; i < sizeOfMessages; i++) {
                        CHUNKS_OWNED_Msg chunksOwnedMsg =
                        res->getPeer_to_chunk_ownership(i);
                        string requestorId = chunksOwnedMsg.getId();

                        // create vector from chunklist array
                        vector<int> chunkList;
                        for (int i = 0; i < (int)chunksOwnedMsg.getDownloadedChunksArraySize(); i++) {
                            chunkList.push_back(
                                    chunksOwnedMsg.getDownloadedChunks(i));
                        }

                        // add this key-value pair to the map
                        this->peersToChunkMap_.insert(
                                pair<string, vector<int> >(requestorId, chunkList));

                    }

                    int numberOfPeers = res->getIdsArraySize();
                    // add peer to peer list
                    for (int i = 0; i < numberOfPeers; i++){
                        this->peers_.push_back(res->getIds(i));
                    }

                    // Now we have the list of peers and their ownership of chunks
                    // we should find which ones to connect and download chunks
                    downloadChunks();
                }
            }
            break;
            default:
            EV << ">>> unknown response type <<< " << endl;
            break;
        }

    } else {
        P2P_Packet *packet2 = dynamic_cast<P2P_Packet *>(msg);
        if (!packet2) {
            // message is not of handleable type
            return;
        }
        switch ((P2P_MSG_TYPE) packet2->getType()) {
            // Received a request from peer for a chunk
            case P2P_REQUEST: {
                P2P_Req *req = dynamic_cast<P2P_Req *>(msg);
                if (!req) {
                    EV << "Arriving packet is not of type P2P_Req" << endl;
                } else {
                    setStatusString("Peer Request");
                    EV << "Arriving packet: Requestor ID = " << req->getId()
                    << ", Requested chunk = " << req->getChunkNo() << endl;

                    // now send the desired response
                    this->sendResponse(connID, req->getChunkNo());
                }
            }
            break;
            // Received the chunk from peer
            case P2P_RESPONSE: {
                P2P_Resp *resp = dynamic_cast<P2P_Resp *>(msg);
                if (!resp) {
                    EV << "Arriving packet is not of type P2P_Resp" << endl;
                } else {
                    setStatusString("Response");
                    EV << "Arriving packet: Responder ID = " << resp->getId()
                    << ", requested chunk = " << resp->getChunkNo()
                    << endl;

                    // add the chunk in the list of download chunks
                    int chunk = resp->getChunkNo();

                    insertChunkInOrder(chunk);
                    deleteChunkFromToDownloadList(chunk);

                    // record the number of chunks remaining
                    int remainingChunkCount = this->ownedChunks_.size() - this->numChunksInFile_;

                    if ((int)this->ownedChunks_.size() >= this->numChunksInFile_) {
                        this->sendP2TRequest(this->trackerSocket_->getConnectionId(),
                                P2T_DOWNLOAD_COMPLETE);
                    }

                    this->numChunksToGet_.record(remainingChunkCount);

                    this->sendP2TRequest(this->trackerSocket_->getConnectionId(),
                            P2T_REFRESH_REQUEST);

                    EV << "Chunks remaining to be downloaded for peer " << this->localAddress_ << " : ";
                    for(size_t i = 0; i < this->chunksToGet_.size(); i++)
                    EV << this->chunksToGet_[i] << " ";

                    // request for next chunk if all the chunks are not downloaded yet from the peer
                    vector<int> peerChunklist = this->peersToChunkMap_.find(
                            resp->getId())->second;
                    int peerChunklistSize = peerChunklist.size();
                    int chunkIndex = 0;
                    for (int i = 0; i < peerChunklistSize; i++) {
                        if (chunk == peerChunklist[i]) {
                            // we found the just download chunk, need to see if next is available
                            chunkIndex = i;
                            break;
                        }
                    }

                    // we have the index of downloaded chunk, from the next elements check if they are still to be downloaded
                    int chunkTobeDownloaded = -1;
                    for (int i = chunkIndex + 1; i < peerChunklistSize; i++) {
                        int peerChunk = peerChunklist[i];
                        // need to find if we have to download this chunk
                        bool found = false;
                        for (size_t j = 0; j < this->chunksToGet_.size();
                                j++) {
                            if (peerChunk == this->chunksToGet_[j]) {
                                found = true;
                                break;
                            }
                        }
                        // have to download
                        if (found) {
                            // save the index
                            chunkTobeDownloaded = peerChunk;
                            break;
                        }
                    }

                    // no chunk to download, close the connection
                    if (chunkTobeDownloaded == -1) {
                        cMessage *temp_msg = new cMessage("temp");
                        TCPCommand *temp_cmd = new TCPCommand();
                        temp_cmd->setConnId(connID);
                        temp_msg->setControlInfo(temp_cmd);
                        TCPSocket *socket = this->socketMap_.findSocketFor(
                                temp_msg);

                        EV << "Download completed with peer - " << resp->getId() << endl;
                        EV << "PRESENTLY OWNED PACKETS BY -" << this->localAddress_ << " : ";
                        for (size_t i = 0; i < this->ownedChunks_.size(); i++)
                        EV << this->ownedChunks_[i] << " ";

                        socket->close();
                    } else {
                        this->sendRequest(connID, chunkTobeDownloaded);
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
    // close the socket corr. to peer
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
    // socket is closed, remove from the map
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
                int size = this->ownedChunks_.size();
                req->setDownloadedChunksArraySize(size);
                for (int i = 0; i < size; i++) {
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
                int size = this->ownedChunks_.size();
                refresh_req->setDownloadedChunksArraySize(size);
                for (int i = 0; i < size; i++) {
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

    EV<< "PACKETS YET TO BE DOWNLOADED BY  " << this->localAddress_ << " : ";

    for (size_t i = 0; i < this->chunksToGet_.size(); i++)
    EV << this->chunksToGet_[i] << " ";

    if (this->chunksToGet_.size() == 0)
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

            for (size_t i = 0; i < this->chunksToGet_.size(); i++) {

                // this means we have to download this chunk from peer
                if (chunks[k] == chunksToGet_[i]) {
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

void Peer::insertChunkInOrder(int chunkValue) {

    EV<< "===== INsert chunk called with "<< chunkValue << endl;

    if (this->ownedChunks_.empty()) {
        this->ownedChunks_.push_back(chunkValue);
        this->newChunkRecieved.record(chunkValue);
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

    this->newChunkRecieved.record(chunkValue);

//    for (int i = 0; i < this->ownedChunks_.size(); i++)
//        EV << this->ownedChunks_[i] << " ";
}

void Peer::deleteChunkFromToDownloadList(int chunkValue) {
    for (size_t i = 0; i < this->chunksToGet_.size(); i++) {
        if (this->chunksToGet_[i] == chunkValue) {
            this->chunksToGet_.erase(
                    this->chunksToGet_.begin() + i);
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

