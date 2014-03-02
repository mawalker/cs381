#ifndef _PEER_H_
#define _PEER_H_

#include <string>
#include <vector>
using namespace std;

#include "INETDefs.h"       // this contains imp definitions from the INET
#include "TCPSocket.h"      // this is needed for sockets
#include "TCPSocketMap.h"   // this is needed to maintain multiple connected
// sockets from other peers
#include "PeerToPeerMSG_m.h"
#include "PeerToTrackerMsg_m.h"
/**
 * This is our application class that demonstrates a P2P capability.
 *
 * Each peer must have both the client and server capabilities.  Since we may be
 * connected to a number of peers while many peers may connect to us, we are going
 * to maintain a socket map for outgoing and incoming connections
 */
class Peer: public cSimpleModule, public TCPSocket::CallbackInterface {

public:
    /**
     *  constructor
     */
    Peer(void);

    /**
     * destructor
     */
    virtual ~Peer(void);

private:

    TCPSocket *socket_;   // our main listening socket
    TCPSocketMap socketMap_; // maps of sockets we maintain

    string localAddress_;    // our local address
    int localPort_;          // our local port we will listen on

    int numPeers_;           // indicates how many peers we are to connect to
    vector<string> connectAddresses_;  // address of our peers
    int connectPort_;        // ports of the peer we connect to
    int numberOfChunksInFile_;
    string trackerAddress_;

    int numberOfConnectedPeers_;

    int initialCountOfOwnedChunks_;

    cOutVector numberOfchunksToDownload;

    vector<int> ownedChunks_;
    vector<int> chunksToDownloadVector_;

    set<string> peers_; // set of all peers
    map<string, vector<int> > peers_to_chunk_;

    // need a map to decide which chunk to download when peer to peer conn is established
    map<int, int> conn_to_chunk_;

    vector<string> connectedPeers_;

    TCPSocket *trackerSocket_;

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
     * will get dispatched to the socketXXX() functions.
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
    virtual int connect(string peer);

    /** Issues CLOSE command */
    virtual void close(void);

    /** Sends a request and response */
    virtual void sendP2TRequest(int connId, enum P2T_MSG_TYPE prt_msg_type);
    virtual void sendRequest(int connId, int chunk);
    virtual void sendResponse(int connId, int chunk);
    virtual void connectAndDownloadChunks();

    /** When running under GUI, it displays the given string next to the icon */
    virtual void setStatusString(const char *s);
    //@}

    /** @name TCPSocket::CallbackInterface callback methods */

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

#endif /* Peer_H_ */
