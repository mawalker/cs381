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

#ifndef SERVERAPP_H_
#define SERVERAPP_H_

#include <string>
#include <vector>
using namespace std;

#include "INETDefs.h"       // this contains imp definitions from the INET
#include "TCPSocket.h"      // this is needed for sockets
#include "TCPSocketMap.h"   // this is needed to maintain multiple connected
                            // sockets from other peers

class ServerApp : public cSimpleModule, public TCPSocket::CallbackInterface{
public:
    ServerApp();
    virtual ~ServerApp();

private:

    // organizing the data members according to the parameters defined in the NED file and then
    // any C++ data members
    string myID_;            // my ID (used in debugging)
    //string  server_;         // name of server
    int localPort_;        // server's local port
    string localAddress_;    // our local address
    //int fileSize_;           // size of file to be transferred.
    //int numAttempts_;        // number of times to request the same file
    //TCPDataTransferMode dataTransferMode_;  // indicates the approach used to transfer data
    TCPSocket    *socket_;   // our socket that talks to the server
    TCPSocketMap socketMap_; // map of sockets we maintain

protected:

    /**
     * Initialization. Should be redefined to perform or schedule a connect().
     */
    virtual void initialize (int stage);
    /**
     * For self-messages it invokes handleTimer(); messages arriving from TCP
     * will get dispatched to the appropriate socketXXX() functions.
     */
    virtual void handleMessage (cMessage *msg);
    //@{
    /** Does nothing but update statistics/status. Redefine to perform or schedule first sending. */
    virtual void socketEstablished(int connId, void *yourPtr);
    /**
     * Does nothing but update statistics/status. Redefine to perform or schedule next sending.
     * Beware: this funcion deletes the incoming message, which might not be what you want.
     */
    virtual void socketDataArrived(int connId, void *yourPtr, cPacket *msg, bool urgent);

    /** When running under GUI, it displays the given string next to the icon */
    virtual void setStatusString (const char *s);

    /** Sends a request and response */
    virtual void sendRequest (int connId, const char *id, const char *fname);
    virtual void sendResponse (int connId, const char *id, unsigned long size);

    /** Since remote TCP closed, invokes close(). Redefine if you want to do something else. */
    virtual void socketPeerClosed(int connId, void *yourPtr);
};

#endif /* SERVERAPP_H_ */
