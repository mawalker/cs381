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

//
// TODO generated message class
//
enum P2P_MSG_TYPE {
    P2P_REQUEST = 0;
    P2P_RESPONSE = 1;
};

packet P2P_Packet{
   int     type @enum(P2P_MSG_TYPE);  // our message type
};

packet P2P_Req extends P2P_Packet{
    string	id;		        // Id of requestor
    int chunkNo;	        // chunk number
};

packet P2P_Resp extends P2P_Packet{
    string  id;				// Id of responder
    int chunkNo;			// chunk number
    char contents[];	    // file contents
};
