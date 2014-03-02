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

#ifndef Tracker_H_
#define Tracker_H_

#include <string>
#include <vector>
using namespace std;

#include "INETDefs.h"       // this contains imp definitions from the INET
#include "TCPSocket.h"      // this is needed for sockets
#include "TCPSocketMap.h"   // this is needed to maintain multiple connected
// sockets from other peers

class Tracker: public cSimpleModule, public TCPSocket::CallbackInterface {
public:
    Tracker();
    virtual ~Tracker();

private:

    // organizing the data members according to the parameters defined in the NED file and then
    // any C++ data members

    /**
     * These values are obtained from INI file
     */
    string myID_;            // my ID (used in debugging)

    TCPSocket *socket_;   // our main listening socket
    TCPSocketMap socketMap_; // maps of sockets we maintain

    int localPort_;        // server's local port
    string localAddress_;    // our local address

    TCPDataTransferMode dataTransferMode_; // indicates the approach used to transfer data

    int numPeers_;           // indicates how many peers we are to connected to
    int numPeersInSim_;     // indicates the number of peers in the whole sim.
    int numSeedsInTorrent;

    vector<string> connectAddresses_;  // address of our peers
    int connectPort_;        // ports of the peer we connect to

    set<string> peers_;
    map<string, vector<int> > peers_to_chunk_map_;

    void insertChunkInOrder(vector<int> &, int);

protected:

    /** @name cComponent initialization and member methods */

    //@{
    /**
     * Initialization. Should be redefined to perform or schedule a connect().
     */
    virtual void initialize(int stage); // impl. as other examples and return on !=3

    /**
     * define how many initialization stages are we going to need.
     */
    virtual int numInitStages(void) const {
        return 4; // just leave as is, 'just works'
    }

    /**
     * Records basic statistics: numSessions, packetsSent, packetsRcvd,
     * bytesSent, bytesRcvd. Redefine to record different or more statistics
     * at the end of the simulation.
     */
    virtual void finish();

    /**
     * For self-messages it invokes handleTimer(); messages arriving from TCP
     * will get dispatched to the appropriate socketXXX() functions.
     */
    virtual void handleMessage(cMessage *msg);
    //@}

    /** @name Utility functions */

    //@{
    /** Issues CLOSE command */
    virtual void close(void);

    /** Sends a response */
    virtual void sendResponse(int connId);

    /** When running under GUI, it displays the given string next to the icon */
    virtual void setStatusString(const char *s);
    //@}

    /** @name TCPSocket::CallbackInterface callback methods */

    //@{
    /** Does nothing but update statistics/status. Redefine to perform or schedule first sending. */
    virtual void socketEstablished(int connId, void *yourPtr);

    /**
     * Does nothing but update statistics/status. Redefine to perform or schedule next sending.
     * Beware: this function deletes the incoming message, which might not be what you want.
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

#endif /* Tracker_H_ */
