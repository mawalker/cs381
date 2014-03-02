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

package CS381_Torrent_HW2.simulations;

// import our ned defn
import CS381_Torrent_HW2.Tracker;			// our P2PApp
import CS381_Torrent_HW2.Peer;

// import all the inet defns as needed for our experiment
import ned.DatarateChannel;
import inet.nodes.inet.StandardHost;
import inet.nodes.inet.Router;
import inet.networklayer.autorouting.ipv4.IPv4NetworkConfigurator;

// this is a modified flat network taken from inet examples
network P2PTorrentFlatNet
{
    parameters:
        int numPeersInSim = default(2);

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
                config = xml("<config><interface hosts='*' address='192.168.x.x' netmask='255.255.x.x'/></config>");
        }

        // a whole bunch of routers
        rte[numPeersInSim]: Router {
            parameters:
                @display("is=vs");
        }

        peer[numPeersInSim]: StandardHost {
            parameters:
                @display("i=device/laptop_s;p=181,133");
                numTcpApps = 1;
        }

        tracker: StandardHost {
            parameters:
                @display("i=device/server2;p=66,42");
                numTcpApps = 1;
        }

    connections:

        for i=0..(numPeersInSim-1) {
            peer[i].pppg++ <--> ethernetline <--> rte[i].pppg++;
        }

        //        peer[0].pppg++ <--> ethernetline <--> rte[0].pppg++;
        //        peer[1].pppg++ <--> ethernetline <--> rte[0].pppg++;
        //        peer[2].pppg++ <--> ethernetline <--> rte[0].pppg++;
        //        peer[3].pppg++ <--> ethernetline <--> rte[0].pppg++;
        //        peer[4].pppg++ <--> ethernetline <--> rte[0].pppg++;
        //        peer[5].pppg++ <--> ethernetline <--> rte[0].pppg++;
        //        peer[6].pppg++ <--> ethernetline <--> rte[0].pppg++;
        tracker.pppg++ <--> ethernetline <--> rte[0].pppg++;

        for i=1..(numPeersInSim-1) {
            rte[i].pppg++ <--> fiberline <--> rte[0].pppg++;
        }

  //      rte[0].pppg++ <--> fiberline <--> rte[1].pppg++;
  //      rte[1].pppg++ <--> fiberline <--> rte[2].pppg++;
  //      rte[2].pppg++ <--> fiberline <--> rte[3].pppg++;
  //      rte[2].pppg++ <--> fiberline <--> rte[5].pppg++;
  //      rte[3].pppg++ <--> fiberline <--> rte[4].pppg++;
  //      rte[5].pppg++ <--> fiberline <--> rte[6].pppg++;

}
