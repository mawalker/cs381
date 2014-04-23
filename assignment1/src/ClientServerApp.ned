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


package CS381_ClientServer;

// we want our application to support the TCPApp interface
import inet.applications.ITCPApp;

// our module behaves like the TCPApp. At simulation time, we provide the appropriate value.
simple ClientApp like ITCPApp
{
	parameters:
	    string myID = default ("client");              // some name assigned to me (for debugging purposes)
        string connectAddress = default ("server");    // server address (may be symbolic)
        int connectPort = default (1000);        	   // port number of the server to connect to
        int fileSize @unit(byte) = default (1KiB);	   // size of file to be transferred
        int numAttempts = default (1);				   // number of times the file should be requested
        // different modes of transferring. I think bytecount is not realistic. But bytestream and object probably are.
        string dataTransferMode @enum ("bytecount","object","bytestream") = default ("bytestream");
        @display ("i=block/app");
 		@statistic[eed](title="end-to-end delay of received packets";unit=s);
   		@statistic[jitter](title="jitter of received packets");
    gates:
        // since we are at the application layer, the only things we are interested in are how we
        // connect to the transport layer below us and how the transport layer talks to us.
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}

// our module behaves like the TCPApp. At simulation time, we provide the appropriate value.
simple ServerApp like ITCPApp
{
	parameters:
        string localAddress = default ("server"); // decides what is our addr. May be left empty ("") -- I assume
                                                  // this will mean "any interface"
        int localPort = default (1000);           // port number to listen on
        // different modes of transferring. I think bytecount is not realistic. But bytestream and object probably are.
        string dataTransferMode @enum ("bytecount","object","bytestream") = default ("bytestream");
        
        @display ("i=block/app");
 
    gates:
        // since we are at the application layer, the only things we are interested in are how we
        // connect to the transport layer below us and how the transport layer talks to us.
        input tcpIn @labels(TCPCommand/up);
        output tcpOut @labels(TCPCommand/down);
}

