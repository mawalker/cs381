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
// this case we let both peers invoke these requests on each other.
//
// We add one more capability wherein we ask the peer to send its obj ref to
// us. We then compare if the obj ref obtained from corbaloc and the one from
// the operation are equivalent. The motivation is that you can do something
// similar when getting obj ref to the peers from the tracker node.
//
//
// This file is Peer.h, which defines our C++ Peer class that we use as a
// helper.  This class has nothing to do with the implementation of the
// interface. 

#ifndef _CS381_Peer_H_
#define _CS381_Peer_H_

#include <string>
using namespace std;

#include "ace/Get_Opt.h"    // this is an ACE header for command line parsing
                            // library. 

class Peer
{
public:
  // constructor
  Peer (int argc, char *argv []);

  // destructor
  ~Peer (void);

  // parse command line
  int parse_args (void);

  // get handle to underlying command line arguments
  int & argc ();
  char ** argv ();

  // access the ID and corbaloc
  const char * id (void) const;
  const char * corbaloc (void) const;

  // signature of our thread entry points defined in the respective files
  static void *client_role (void *arg);
  static void *server_role (void *arg);

private:

  int argc_;

  char **argv_;

  string id_;

  string corbaloc_;
};

#endif /* _CS381_Peer_H_ */
