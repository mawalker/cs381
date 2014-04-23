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
// This file is Peer.cpp, which implements the Peer class and also serves as
// the main program for the executable.

#include <string>
using namespace std;

#include "ace/Thread_Manager.h"   // for the thread manager
#include "ace/OS_NS_unistd.h"     // for sleep, etc
//#include "ace/OS_NS_sys_time.h"

#include "Peer.h"

// you can change these if you so desire
const int NUM_CLIENT_THREADS = 1;
const int NUM_SERVER_THREADS = 1;

// implementation of the Peer class
Peer::Peer (int argc, ACE_TCHAR *argv [])
  : argc_ (argc),
    argv_ (argv),
    id_ ("Peer"),
    corbaloc_ ("corbaloc:iiop:localhost:9999/Peer")
{
}

// destructor
Peer::~Peer (void)
{
}

int &Peer::argc (void)
{
  return this->argc_;
}

char **Peer::argv (void)
{
  return this->argv_;
}

// get the id
const char * Peer::id (void) const
{
  return this->id_.c_str ();
}

// get the tracker description
const char * Peer::trackerloc (void) const
{
	return this->trackerloc_.c_str ();
}

// get the server description
const char * Peer::serverloc (void) const
{
	return this->serverloc_.c_str ();
}

long Peer::num_chunks (void) const
{
	return this->num_chunks_;
}

map<string, vector<long> > * Peer::peer_to_chunks(void)
{
	return &this->peer_to_chunks_;
}

int Peer::connections_num(void)
{
	return this->connections_num_;
}

// command line parsing
int
Peer::parse_args (void)
{
  // in the server role, we need to specify what our ID is going to be with the
  // -i flag. In the client role we need to specify the corbaloc URL that is
  // passed to the string_to_object. corbaloc is of the form
  // "corbaloc:iiop:<hostname>:<port num>/<id>"
  //
  // I am taking this approach because when students do the assignments on the
  // VMs of the cloud, they may be be able to use URLs and not always will they
  // be able to use the file approach

  int c;

  ACE_Get_Opt get_opt (this->argc_, this->argv_, "i:c:n:f:r:");
  while ((c = get_opt ()) != -1)
    switch (c)
      {
      case 'c':
        this->corbaloc_ = get_opt.opt_arg ();
        break;

      case 'i':
        this->id_ = get_opt.opt_arg ();
        break;

	  case 'f':
		Peer_Job_i::file_name_ = get_opt.opt_arg ();
		break;

	  case 'n':
		this->connections_num_ = atoi(get_opt.opt_arg ());
		break;

	  case 'r':
		this->refresh_freq_ = atoi(get_opt.opt_arg ());
		break;

      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s "
                           "-i <our id> "
                           "-c <corbaloc url of peer> "
						   "-n <number of p2p connections that happen at the same time> "
						   "-f <file name> "
						   "-r <message refresh frequency> "
                           "\n",
                           this->argv_[0]),
                          -1);
      }

	  ACE_DEBUG ((LM_DEBUG,
			"parse_args: ID = %s, trackerloc = %s, connections_num_ = %d\n",
			this->id_.c_str (), this->trackerloc_.c_str (),
			this->connections_num_));

  // Indicates successful parsing of the command line
  return 0;
}

// main function for the program
int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{ 
  // declare the Peer class
  Peer peer (argc, argv);

  // grab a thread manager (we get the global singleton instance)
  ACE_Thread_Manager *thr_mgr = ACE_Thread_Manager::instance ();

  // declare a variable to hold the thread ids. I am showing you that you can
  // have a group of threads but for this sample we are going to have only one
  // each. 
  ACE_thread_t  server_tid[NUM_SERVER_THREADS];
  ACE_thread_t  client_tid[NUM_CLIENT_THREADS];

  // now spawn off NUM_SERVER_THREADS passing it the thread entry function
  // and the argument we want to pass it. 
  int server_group_id = 
    thr_mgr->spawn_n (server_tid,          // all the threads created
                      NUM_SERVER_THREADS,  // 1 thread in our case
                      (ACE_THR_FUNC) Peer::server_role,  // entry point to the thread
                      &peer,
                      THR_NEW_LWP | THR_JOINABLE
                      // we want threads whose return status can be
                      // monitored. Moreover, we want a lightweight
                      // process.
                      );

  if (server_group_id == -1) {
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), 
                  ACE_TEXT ("spawn_n server")));
      return -1;
  }

  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) started server group %d\n"), 
              server_group_id));

  // sleep for 10 sec so that the server roles of all peers are initialized
  ACE_OS::sleep (10);

  // now start the client thread(s)
  // now spawn off NUM_CLIENT_THREADS passing it the thread entry function
  // and the argument we want to pass it. 
  int client_group_id = 
    thr_mgr->spawn_n (client_tid,          // all the threads created
                      NUM_CLIENT_THREADS,                    // 1 thread
                      (ACE_THR_FUNC) Peer::client_role,  // entry point to the thread
                      &peer,
                      THR_NEW_LWP | THR_JOINABLE
                      // we want threads whose return status can be
                      // monitored. Moreover, we want a lightweight
                      // process.
                      );

  if (client_group_id == -1) {
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), 
                  ACE_TEXT ("spawn_n client")));
      return -1;
  }

  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) started client group %d\n"), 
              server_group_id));


  // now wait for all threads to exit and their status is reaped
  if (thr_mgr->wait () == -1) {
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), 
                  ACE_TEXT ("wait")));
      return -1;
  }

  // done
  return 0;
}
                      
