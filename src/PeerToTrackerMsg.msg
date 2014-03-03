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
    P2T_REG_REQUEST = 0; // registration request
    P2T_REFRESH_REQUEST = 1; // refresh request to get the latest info about peers
    T2P_MEMBER_RESPONSE = 2; // respond as a member
    P2T_DOWNLOAD_COMPLETE = 3; // tell the tracker the download is complete
};


packet P2T_Packet
{
   int     type @enum(P2T_MSG_TYPE);  // our message type
};

packet CHUNKS_OWNED_Msg extends P2T_Packet
{
    string	id;		        	// Id of requestor
    int downloadedChunks[];		// chunks that are already downloaded 
};

packet T2P_MEMBER_Res extends P2T_Packet{
    string ids[];   
    CHUNKS_OWNED_Msg chunksOwned[];
};

// called when peer downloads everything
packet P2T_DOWNLOAD_COMPLETE_Msg extends P2T_Packet
{
    string	id;		        // Id of requestor
};
