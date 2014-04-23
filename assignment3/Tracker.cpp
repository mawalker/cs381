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
// This file is Tracker.cpp, which implements the Tracker class and also serves as
// the main program for the executable.

#include <string>
using namespace std;

#include "ace/Thread_Manager.h"   // for the thread manager
#include "ace/OS_NS_unistd.h"     // for sleep, etc
//#include "ace/OS_NS_sys_time.h"

#include "Tracker.h"

// you can change these if you so desire
const int NUM_CLIENT_THREADS = 1;
const int NUM_SERVER_THREADS = 1;

// implementation of the Tracker class
Tracker::Tracker (int argc, ACE_TCHAR *argv [])
  : argc_ (argc),
    argv_ (argv),
    id_ ("Tracker"),
    corbaloc_ ("corbaloc:iiop:localhost:9999/Tracker")
{
}

// destructor
Tracker::~Tracker (void)
{
}

int &Tracker::argc (void)
{
  return this->argc_;
}

char **Tracker::argv (void)
{
  return this->argv_;
}

// get the id
const char * Tracker::id (void) const
{
  return this->id_.c_str ();
}

// get the corbaloc description
const char * Tracker::corbaloc (void) const
{
  return this->corbaloc_.c_str ();
}

// command line parsing
int
Tracker::parse_args (void)
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

  ACE_Get_Opt get_opt (this->argc_, this->argv_, "c:i:");
  while ((c = get_opt ()) != -1)
    switch (c)
      {
      case 'c':
        this->corbaloc_ = get_opt.opt_arg ();
        break;

      case 'i':
        this->id_ = get_opt.opt_arg ();
        break;

      case '?':
      default:
        ACE_ERROR_RETURN ((LM_ERROR,
                           "usage:  %s "
                           "-i <our id> "
                           "-c <corbaloc url of peer> "
                           "\n",
                           this->argv_[0]),
                          -1);
      }

  ACE_DEBUG ((LM_DEBUG,
              "parse_args: ID = %s, corbaloc = %s\n",
              this->id_.c_str (), this->corbaloc_.c_str ()));

  // Indicates successful parsing of the command line
  return 0;
}

// main function for the program
int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{ 
  // declare the Tracker class
  Tracker tracker (argc, argv);

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
                      (ACE_THR_FUNC) Tracker::server_role,  // entry point to the thread
                      &tracker,
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

  // now wait for all threads to exit and their status is reaped
  if (thr_mgr->wait () == -1) {
      ACE_ERROR ((LM_ERROR, ACE_TEXT ("(%P|%t) %p\n"), 
                  ACE_TEXT ("wait")));
      return -1;
  }

  // done
  return 0;
}
                      
