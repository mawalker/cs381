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

package CS381_ClientServer.simulations;



// import all the inet defns as needed for our experiment
import ned.DatarateChannel;
//import inet.nodes.inet.WirelessHost;
import inet.nodes.inet.StandardHost;
import inet.nodes.inet.Router;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;
import inet.world.radio.ChannelControl;	 // for the management of the wireless channel

// import our ned defn
import CS381_ClientServer.ClientApp;			// our ClientApp
import CS381_ClientServer.ServerApp;			// our ServerApp

// this is a modified flat network taken from inet examples
network CSFlatNet
{
    parameters:
        int numClients = default (1);
        
    types:
        channel fiberline extends DatarateChannel
        {
            delay = 1us;
            datarate = 512Mbps;
        }
        
        channel ethernetline extends DatarateChannel
        {
            delay = 0.1us;
            datarate = 10Mbps;
        }
        
    submodules:
        // this one configures the IPv4 network
        configurator: IPv4NetworkConfigurator {
            parameters:
                config=xml("<config><interface hosts='*' address='192.168.x.x' netmask='255.255.x.x'/></config>");
        }
        
        // a whole bunch of routers
        rte[7]: Router {
            parameters:
                @display("is=vs");
        }
        
        client[numClients]: StandardHost {
            parameters:
                @display("i=device/laptop_s");
                numTcpApps = 1;
        }
        
        server : StandardHost {
            parameters:
                @display("i=device/laptop_s");
                numTcpApps = 1;
        }
        
        // the channel that controls all the wireless stuff. It needs to know what
        // the size of the region it is controlling.
        channelControl: ChannelControl {
            @display("p=48,28");
        }
        
    connections:
        // demonstrates how the end hosts are connected to the edge routers
        client[0].pppg++ <--> ethernetline <--> rte[0].pppg++;
        server.pppg++ <--> ethernetline <--> rte[0].pppg++;
 
 //       client[1].pppg++ <--> ethernetline <--> rte[4].pppg++;
 //       server.pppg++ <--> ethernetline <--> rte[6].pppg++;
        
        // topology of the routers. Notice how the core routers are connected with high speed n/w
//        rte[0].pppg++ <--> fiberline <--> rte[1].pppg++;
//        rte[1].pppg++ <--> fiberline <--> rte[2].pppg++;
//        rte[2].pppg++ <--> fiberline <--> rte[3].pppg++;
//        rte[2].pppg++ <--> fiberline <--> rte[5].pppg++;
//        rte[3].pppg++ <--> fiberline <--> rte[4].pppg++;
//        rte[5].pppg++ <--> fiberline <--> rte[6].pppg++;
}