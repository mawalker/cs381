// $Id$

//
// Sample code developed for CS381, Fall 2012
// 
// Author: Aniruddha Gokhale
// Date:   Oct 21, 2012
//
// The purpose of this sample code is to demonstrate a P2P example in
// CORBA. Thus we have two threads. One thread that serves in the client role
// and the other thread that serves in the server role. 
//
// In this sample, we extend our HelloWorld example such that the same set of
// operations are invoked as we did in the HelloWorld example except that in
// this case we let both trackers invoke these requests on each other.
//
// We add one more capability wherein we ask the tracker to send its obj ref to
// us. We then compare if the obj ref obtained from corbaloc and the one from
// the operation are equivalent. The motivation is that you can do something
// similar when getting obj ref to the trackers from the tracker node.
//
//
// This file is server_role.cpp, which implements the server-side thread for
// the tracker.

#include <string>
using namespace std;

#include "ace/Get_Opt.h"
#include "ace/OS_NS_stdio.h"

#include "tao/IORTable/IORTable.h"    // maintains the binding

#include "Torrent_i.h"         // impl header
#include "Tracker.h"                     // helper class

// main thread function
void *Tracker::server_role (void *arg)
{
  try
    {
      // let us convert the incoming argument
      Tracker *tracker = static_cast<Tracker *>(arg);

      // the first step should be to acquire the underlying object request
      // broker (ORB). Note that the _var type is a smart pointer that manages
      // memory.  
      ACE_DEBUG ((LM_DEBUG,
                  "server role: acquire the orb (argc = %d)\n", tracker->argc ()));
      CORBA::ORB_var orb = CORBA::ORB_init (tracker->argc (), 
                                            tracker->argv (),
                                            "server_role");
      ACE_DEBUG ((LM_DEBUG,
                  "server role: after org init (argc = %d)\n", tracker->argc ()));

      // parse the arguments
      ACE_DEBUG ((LM_DEBUG,
                  "Tracker main: parse the args\n"));
      if (tracker->parse_args () == -1) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), 
                    ACE_TEXT ("parse failed")));
        return 0;
      }

      if (CORBA::is_nil (orb.in ())) {
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), 
                  ACE_TEXT ("cannot acquire orb")));
        return 0;
      }

      // the next step is to obtain a handle to the RootPOA from our
      // ORB. Recall that the ORB is the resource manager. It is bootstrapped
      // with some default capabilities like the RootPOA
      ACE_DEBUG ((LM_DEBUG,
                  "server role: acquire the RootPOA\n"));
      CORBA::Object_var poa_object =
        orb->resolve_initial_references("RootPOA");

      // Narrow the object reference to the exact type we desire.
      PortableServer::POA_var root_poa =
        PortableServer::POA::_narrow (poa_object.in ());

      // check if it is non-nil
      if (CORBA::is_nil (root_poa.in ()))
        ACE_ERROR_RETURN ((LM_ERROR,
                           " (%P|%t) Panic: nil RootPOA\n"),
                          0);

      // obtain a handle to the POA manager which drives the lifecycle of the
      // POAs it manages.
      ACE_DEBUG ((LM_DEBUG,
                  "server role: acquire the POA Manager\n"));
      PortableServer::POAManager_var poa_manager = root_poa->the_POAManager ();

      // instantiate an instance of the implementation class. Note that after
      // this step it is just a C++ object and not a CORBA object yet.
      ACE_DEBUG ((LM_DEBUG,
                  "server role: instantiate our impl\n"));
      P2P_HelloWorld_i *hello_impl = 0;
      ACE_NEW_RETURN (hello_impl,
                      P2P_HelloWorld_i (orb.in ()),
                      0);

      // let the POA's capability own the implementation
      PortableServer::ServantBase_var owner_transfer (hello_impl);

      // activate the object with the root poa
      ACE_DEBUG ((LM_DEBUG,
                  "server role: activate our impl with the root POA\n"));
      PortableServer::ObjectId_var oid =
        root_poa->activate_object (hello_impl);

      // obtain an object reference from the ID that was assigned to our
      // implementation by the RootPOA
      ACE_DEBUG ((LM_DEBUG,
                  "server role: obtain our obj ref\n"));
      CORBA::Object_var object = root_poa->id_to_reference (oid.in ());

      // check if it is non-nil
      if (CORBA::is_nil (object.in ()))
        ACE_ERROR_RETURN ((LM_ERROR,
                           " (%P|%t) Panic: nil ref obtained from id_to_ref\n"),
                          0);

      // narrow it to the exact type we want to
      HelloWorld::Hello_var hello_obj 
        = HelloWorld::Hello::_narrow (object.in ());

      // check if it is non-nil
      if (CORBA::is_nil (hello_obj.in ()))
        ACE_ERROR_RETURN ((LM_ERROR,
                           " (%P|%t) Panic: nil Hello obj ref\n"),
                          0);


      // now obtain a stringified representation of the object reference so
      // that it can be externalized
      CORBA::String_var ior = orb->object_to_string (hello_obj.in ());
      ACE_DEBUG ((LM_DEBUG,
                  "server role: acquire the orb\n"));

      // now bind this into an IORTable so that clients can use the corbaloc
      // method and do not have to use the naming service
      ACE_DEBUG ((LM_DEBUG,
                  "server role: acquire the IORTable\n"));
      CORBA::Object_var tbl_obj 
        = orb->resolve_initial_references ("IORTable");

      // narrow it
      IORTable::Table_var table = IORTable::Table::_narrow (tbl_obj.in ());

      // bind our ID we sent on the command line to the IOR so that outside
      // world can use a URL to talk to us. This binding is maintained in the
      // IORTable. 
      ACE_DEBUG ((LM_DEBUG, 
                  "server role: binding to %s\n", tracker->id ()));
      table->bind (tracker->id (), ior.in ());

      // now kickstart the POAs so they can do their duties. In our case we
      // have just one POA, the RootPOA
      ACE_DEBUG ((LM_DEBUG,
                  "server role: activate the POA manager\n"));
      poa_manager->activate ();

      // let the ORB take over at this point and handled incoming events
      ACE_DEBUG ((LM_DEBUG,
                  "server role: run the orb\n"));
      orb->run ();

      ACE_DEBUG ((LM_DEBUG, 
                  "(%P|%t) server role - event loop finished\n"));

      // if we are done, clean up the resources, e.g., the RootPOA and the
      // ORB. 
      ACE_DEBUG ((LM_DEBUG,
                  "server role: destroy root POA and ORB\n"));
      root_poa->destroy (1, 1);
      orb->destroy ();
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Exception caught:");
      return 0;
    }

  return 0;
}
