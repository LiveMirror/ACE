/**
 * @file Echo_Caller.cpp
 *
 * $Id: Echo_Caller.cpp 91649 2010-09-08 13:44:26Z johnnyw $
 *
 * @author Carlos O'Ryan <coryan@atdesk.com>
 *
 */
#include "Echo_Caller.h"
#include "Server_Timer.h"
#include "tao/ORB_Core.h"

Echo_Caller::Echo_Caller(CORBA::ORB_ptr orb)
  : orb_(CORBA::ORB::_duplicate(orb))
{
}

void
Echo_Caller::start_task(Test::Echo_ptr client)
{
  Server_Timer * task =
    new Server_Timer(client, orb_->orb_core()->reactor());
  task->activate();
  task->remove_reference ();

  task =
    new Server_Timer(client, orb_->orb_core()->reactor());
  task->activate();
  task->remove_reference ();
}

void
Echo_Caller::shutdown(void)
{
  ACE_DEBUG ((LM_DEBUG, "Server received shutdown message\n"));
  orb_->shutdown(0);
}
