/* -*- C++ -*- */
//=============================================================================
/**
 *  @file    FTAPP_FaultConsumer_Main.cpp
 *
 *  $Id: FTAPP_FaultConsumer_Main.cpp 68471 2005-10-04 11:38:20Z jwillemsen $
 *
 *  This file is part of Fault Tolerant CORBA.
 *  This file provides the main routine for a stub FaultConsumer.
 *
 *  @author Steve Totten <totten_s@ociweb.com>
 */
//=============================================================================

#include "tao/Utils/Server_Main.h"
#include "ReplicationManagerFaultConsumerAdapter.h"

int ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
  TAO::Utils::Server_Main<ReplicationManagerFaultConsumerAdapter>
    server_main("FaultConsumer");
  return server_main.run(argc, argv);
}
