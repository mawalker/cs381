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

}

void Tracker::finish() {
}

void Tracker::connect(int i) {
}

void Tracker::close(void) {
}

void Tracker::socketClosed(int connId, void *yourPtr) {
}

void Tracker::socketFailure(int connId, void *yourPtr, int code) {
}

/** This is the all-encompassing event handling function. It is our responsibility to
 *  figure out what to do with every event, which is appln-specific */
void Tracker::handleMessage(cMessage *msg) {

}

// when the client sends a connection established msg, this callback will be invoked.
void Tracker::socketEstablished(int connID, void *role) {

}

/** handle incoming data. Could be a request or response */
void Tracker::socketDataArrived(int connID, void *, cPacket *msg, bool) {

}

void Tracker::sendRequest(int connId) {

}

// send a request to the other side
//void Tracker::sendRequest(int connId) { //, const char *id, const char *fname) {

//}

// send a response
void Tracker::sendResponse(int connId) { // const char *id, unsigned long size) {

}

// this method is used to flash messages during animation where we can see bubbles on the screen.
void Tracker::setStatusString(const char *s) {
    if (ev.isGUI ()) {
        getDisplayString ().setTagArg ("t", 0, s);
        bubble (s);
    }
}

void Tracker::socketPeerClosed(int connID, void *) {

}

