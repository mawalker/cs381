/*
 * Peer.h
 *
 *  Created on: Feb 1, 2014
 *      Author: Aniruddha Gokhale
 *      Class:  CS381
 *      Institution: Vanderbilt University
 */

// An application logic for Client behavior. This code has been developed by
// modifying the P2P sample
#ifndef _CS381_PEER_H_
#define _CS381_PEER_H_

#include <string>
#include <vector>
using namespace std;

#include "INETDefs.h"       // this contains imp definitions from the INET
#include "TCPSocket.h"      // this is needed for sockets
#include "TCPSocketMap.h"   // this is needed to maintain multiple connected
// sockets from other peers

/**
 * This is our application class that demonstrates a CS capability.
 *
 * Each peer must have both the client and server capabilities.  Since we may be
 * connected to a number of peers while many peers may connect to us, we are going
 * to maintain a socket map for outgoing and incoming connections
 */
class Peer: public cSimpleModule, public TCPSocket::CallbackInterface {
    // note that the inheritance from the TCPSocket::CallbackInterface is needed to handle all socket-level events
public:
    Peer(void);
    virtual ~Peer(void);

private:
    // organizing the data members according to the parameters defined in the NED file and then
    // any C++ data members
    string myID_;            // my ID (used in debugging)
    string server_;         // name of server

    string localAddress_;    // our local address
    int localPort_;          // our local port we will listen on

    int connectPort_;        // port of the server to connect to
    int fileSize_;           // size of file to be transferred.
    int numAttempts_;        // number of times to request the same file
    TCPDataTransferMode dataTransferMode_; // indicates the approach used to transfer data
    TCPSocket *socket_;      // our socket that talks to the server

    bool startAsSeed_;

    int numPeers_;                       // # of peers total
    vector<string> connectAddresses_;    // address of our peers
    int numberOfChunksInFile_;           // # of chunks in file
    string trackerAddress_;              // tracker address

    int numberOfConnectedPeers_;         // # of peers connected

    int initialCountOfOwnedChunks_;      // how many chunks did I start with.

    cOutVector numberOfchunksToDownload; // chunks left to download.

    vector<int> ownedChunks_;            // chunks that I have
    vector<int> chunksToDownloadVector_; // chunks left to get

    set<string> peers_;                  // set of all peers
    map<string, vector<int> > peers_to_chunk_; // map of what peers have what chunks

    // need a map to decide which chunk to download when peer to peer conn is established
    map<int, int> conn_to_chunk_;

    vector<string> connectedPeers_;   // list of peers connected to

    TCPSocket *trackerSocket_;        // socket to tracker

    void insertChunkInOrder(int);
    void deleteChunkFromToDownloadList(int);

protected:
    /**
     * Initialization. Should be redefined to perform or schedule a connect().
     */
    virtual void initialize(int stage);

    /**
     * define how many initialization stages are we going to need.
     */
    virtual int numInitStages(void) const {
        return 4;
    }

    /**
     * For self-messages it invokes handleTimer(); messages arriving from TCP
     * will get dispatched to the appropriate socketXXX() functions.
     */
    virtual void handleMessage(cMessage *msg);

    /**
     * Records basic statistics: numSessions, packetsSent, packetsRcvd,
     * bytesSent, bytesRcvd. Redefine to record different or more statistics
     * at the end of the simulation.
     */
    virtual void finish();

    /** Invoked from handleMessage(). Should be defined to handle self-messages. */
    virtual void handleTimer(cMessage *msg);



    /** @name Utility functions */

    //@{
    /** Issues an active OPEN to the address/port given as module parameters */
    virtual void connect();

    /** Issues CLOSE command */
    virtual void close(void);

    /** Sends a request and response */
    virtual void sendP2TRequest(int connId, enum P2T_MSG_TYPE prt_msg_type);
    virtual void sendRequest(int connId, int chunk);
    virtual void sendResponse(int connId, int chunk);
    virtual void connectAndDownloadChunks();

    /** Handle the incoming response packet */
    //   virtual void handleResponse(CS_Resp *response);
    /** When running under GUI, it displays the given string next to the icon */
    virtual void setStatusString(const char *s);
    //@}





    /** @name overridden TCPSocket::CallbackInterface callback methods */

    //@{
    /** Does nothing but update statistics/status. Redefine to perform or schedule first sending. */
    virtual void socketEstablished(int connId, void *yourPtr);

    /**
     * Does nothing but update statistics/status. Redefine to perform or schedule next sending.
     * Beware: this funcion deletes the incoming message, which might not be what you want.
     */
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg,
            bool urgent);

    /** Since remote TCP closed, invokes close(). Redefine if you want to do something else. */
    virtual void socketPeerClosed(int connId, void *yourPtr);

    /** Does nothing but update statistics/status. Redefine if you want to do something else, such as opening a new connection. */
    virtual void socketClosed(int connId, void *yourPtr);

    /** Does nothing but update statistics/status. Redefine if you want to try reconnecting after a delay. */
    virtual void socketFailure(int connId, void *yourPtr, int code);

    /** Redefine to handle incoming TCPStatusInfo. */
    virtual void socketStatusArrived(int connId, void *yourPtr,
            TCPStatusInfo *status) {
        delete status;
    }
    //@}

};

#endif /* _CS381_PEER_H_ */

