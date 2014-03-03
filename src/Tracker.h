/*
 * P2PApp.h
 *
 *  Created on: Sep 22, 2012
 *      Author: Aniruddha Gokhale
 *      Class:  CS381
 *      Institution: Vanderbilt University
 */

#ifndef _BITTORENT_TRACKER_APP_H_
#define _BITTORENT_TRACKER_APP_H_

#include <string>
#include <vector>
using namespace std;

#include "INETDefs.h"       // this contains imp definitions from the INET
#include "TCPSocket.h"      // this is needed for sockets
#include "TCPSocketMap.h"   // this is needed to maintain multiple connected
                            // sockets from other peers


/**
 * This is our application class that demonstrates a Tracker capability.
 *
 * Since we may be connected to a number of peers while many peers may connect
 * to us, we are going to maintain a socket map for outgoing and incoming connections.
 * And one open socket to listen to requests.
 */
class Tracker : public cSimpleModule, public TCPSocket::CallbackInterface
{

  public:
    /**
     *  constructor
     */
    Tracker (void);

    /**
     * destructor
     */
    virtual ~Tracker (void);

  private:

    TCPSocket    *socket_;   // our main listening socket
    TCPSocketMap socketMap_; // maps of sockets we maintain

    string localAddress_;    // our local address
    int localPort_;          // our local port we will listen on

    int numPeers_;           // indicates how many peers we are to connect to
    vector<string> connectAddresses_;  // address of our peers
    int connectPort_;        // ports of the peer we connect to

    int numSeedsInTorrent_; // number of seeds in the torrent group
    int numPeersInSim_;     // number of peers in the simulation

    cOutVector numberOfSeeders;

    set<string> peers_;     // set of peer Ids
    map<string, vector<int> > peers_to_chunk_;

    void insertChunkInOrder(vector<int> &, int);

  protected:
    /**
     * Initialization. Should be redefined to perform or schedule a connect().
     */
    virtual void initialize (int stage);

    /**
     * define how many initialization stages are we going to need.
     */
    virtual int numInitStages (void) const { return 4; }

    /**
     * For self-messages it invokes handleTimer(); messages arriving from TCP
     * will get dispatched to the socketXXX() functions.
     */
    virtual void handleMessage (cMessage *msg);

    /**
     * Records basic statistics: numSessions, packetsSent, packetsRcvd,
     * bytesSent, bytesRcvd. Redefine to record different or more statistics
     * at the end of the simulation.
     */
    virtual void finish();

    /** @name Utility functions */

    //@{
    /** Issues an active OPEN to the address/port given as module parameters */
    virtual void connect (int i);

    /** Issues CLOSE command */
    virtual void close (void);

    /** Sends a response */
    virtual void sendResponse (int connId);

    /** When running under GUI, it displays the given string next to the icon */
    virtual void setStatusString (const char *s);
    //@}


    /** @name TCPSocket::CallbackInterface callback methods */

    //@{
    /** Does nothing but update statistics/status. Redefine to perform or schedule first sending. */
    virtual void socketEstablished(int connId, void *yourPtr);

    /**
     * Does nothing but update statistics/status. Redefine to perform or schedule next sending.
     * Beware: this function deletes the incoming message, which might not be what you want.
     */
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent);

    /** Since remote TCP closed, invokes close(). Redefine if you want to do something else. */
    virtual void socketPeerClosed(int connId, void *yourPtr);

    /** Does nothing but update statistics/status. Redefine if you want to do something else, such as opening a new connection. */
    virtual void socketClosed(int connId, void *yourPtr);

    /** Does nothing but update statistics/status. Redefine if you want to try reconnecting after a delay. */
    virtual void socketFailure(int connId, void *yourPtr, int code);

    /** Redefine to handle incoming TCPStatusInfo. */
    virtual void socketStatusArrived(int connId, void *yourPtr, TCPStatusInfo *status) {delete status;}
    //@}

};



#endif /* _BITTORENT_TRACKER_APP_H_ */
