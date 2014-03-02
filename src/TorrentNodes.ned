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

// Author: Aniruddha Gokhale
// Vanderbilt University EECS
// Created: Fall 2012 for CS381
// Modified: Jan 2014 for CS381
//
// An application logic for P2P behavior. This code has been developed by 
// modifying the code in TCPBasicClientApp and TCPGenericSrvApp available 
// in the INET framework


package CS381_Torrent_HW2;

// we want our application to support the TCPApp interface
import inet.applications.ITCPApp;

simple Tracker like ITCPApp
{
    parameters:
        string localAddress = default(""); // may be left empty ("")
        int localPort = default(1000); // port number to listen on
        //int numPeers = default (7);	// one peer to connect to
        string connectAddresses = default("");  // server addresses (may be symbolic)
        int connectPort = default(1000); // port number of the peer to connect to
        string dataTransferMode @enum("bytecount","object","bytestream") = default("object");
        string peers_to_chunk = default("");
        string myID = default("");
        int numPeersInSim = default(2);
        int fileSize = default(100);
        @display("i=block/app");

    gates:
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}

simple Peer like ITCPApp
{
    parameters:
        string localAddress = default(""); // may be left empty ("")
        int localPort = default(1000); // port number to listen on
        int numPeers = default(2);	// peers to connect to
        string connectAddresses = default("");  // server addresses (may be symbolic)
        int connectPort = default(1000); // port number of the peer to connect to
        string dataTransferMode @enum("bytecount","object","bytestream") = default("object");
        string trackerAddress = default("");
        int numPeersInSim = default(2);
        int numberOfChunksInFile = default(50);
        string myID = default("");
        int fileSize = default(100);
        bool startAsSeed = default(false);
        @display("i=block/app");

    gates:
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}
