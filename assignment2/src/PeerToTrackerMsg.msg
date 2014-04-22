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

enum P2T_MSG_TYPE {
    P2T_REGISTRATION_REQUEST = 0;
    P2T_REFRESH_MESSAGE = 1;    
    T2P_MEMBERSHIP_RESPONSE = 2;
    P2T_DOWNLOAD_COMPLETE = 3;
};


packet P2T_Packet
{
   int     type @enum(P2T_MSG_TYPE);  // our message type
};

// will be used by Peer to Tracker Registration and Refresh
// Tracker to Peer - list of membership and chunk ownership
packet Ownership_Message extends P2T_Packet
{
    string	id;		        // announce the requestor's ID
    int owned_chunks[];		// list of downloaded chunks 
};

// response containing multiple message of the format same as owned chunk
packet T2P_MEMBERSHIP_Res extends P2T_Packet{
    string ids[];   
    Ownership_Message peer_to_chunk_ownership[];
};

// called when peer downloads everything
packet P2T_DOWNLOAD_COMPLETE_Msg extends P2T_Packet
{
    string	id;		        // Id of requestor
};
