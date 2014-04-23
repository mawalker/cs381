// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.2.5
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.dre.vanderbilt.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// be/be_codegen.cpp:1616

#ifndef TORRENTI_UCLSSQ_H_
#define TORRENTI_UCLSSQ_H_

#include "TorrentS.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class  Torrent_P2T_i
  : public virtual POA_Torrent::P2T
{
public:
  // Constructor
  Torrent_P2T_i (void);

  // Destructor
  virtual ~Torrent_P2T_i (void);

  virtual
  ::RegReply * _cxx_register (
    const char * client_id,
    const char * peer_ior_val,
    const char * file_name);

  virtual
  void leave (
    const char * client_id,
    ::CORBA::ULongLong time_in_miliseconds);

  virtual
  ::OwnershipList * refresh (
    const char * client_id,
    const char * file_name,
    const ::ChunkNumbers & chunks_owned);

  virtual
  void sendNumChunks (
    const char * file_name,
    const char * server_ior_val,
    ::CORBA::Long number_of_chunks);

  virtual
  void shutdown (
    void);

private:
    COBRA::ORB_var orb_;
    string fileName_;
    OwnershipList ownershipList_;
    long numberOfChunks_;
    string ownIOR_;
};

class  Torrent_P2P_i
  : public virtual POA_Torrent::P2P
{
public:
  // Constructor
  Torrent_P2P_i (void);

  // Destructor
  virtual ~Torrent_P2P_i (void);

  virtual
  ::Chunk * getChunk (
    const char * file_name,
    ::CORBA::Long chunckNumber);

  virtual
  void shutdown (
    void);

private:
    COBRA::ORB_var orb_;
};


#endif /* TORRENTI_H_  */