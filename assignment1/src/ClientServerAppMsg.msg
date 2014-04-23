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
// Created: Spring 2014 for CS381
//
// Message types

// In this file we define the messages we are interested in sending over the network.
// In this example, we will have two types of messages: Request and Response.
enum CS_MSG_TYPE {
    CS_REQUEST = 0;
    CS_RESPONSE = 1;
};

// I am describing a base class for the packet so that it can be extended by subclasses. The 
// power we derive from this is at implementation time where we rely on polymorphism
packet CS_Packet
{
   int     type @enum(CS_MSG_TYPE);  // our message type
};

// a client sends the server this packet indicating to it its id, and the name of the file it
// is requesting
packet CS_Req extends CS_Packet
{
    string	id;		        // announce the requestor's ID
    int filesize;	        // request for a file of the specified size
    string fname;
};

// this is the response from the server
packet CS_Resp extends CS_Packet
{
    string  id;			// ID of the responder
	unsigned long size;	// size of the data	
    char data [];	    // contents of the file (for now we have commented this out)
};

