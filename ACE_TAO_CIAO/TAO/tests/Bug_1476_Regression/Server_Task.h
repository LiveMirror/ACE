//
// $Id: Server_Task.h 59413 2004-08-10 08:12:49Z jwillemsen $
//

#ifndef ONEWAYS_INVOKING_TWOWAYS_SERVER_TASK_H
#define ONEWAYS_INVOKING_TWOWAYS_SERVER_TASK_H
#include /**/ "ace/pre.h"

#include "tao/ORB.h"
#include "ace/Task.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

/// Implement a Task to run the experiments using multiple threads.
class Server_Task : public ACE_Task_Base
{
public:
  /// Constructor
  Server_Task (CORBA::ORB_ptr orb,
               ACE_Thread_Manager *thr_mgr);

  /// Thread entry point
  int svc (void);

private:
  /// Reference to the ORB
  CORBA::ORB_var orb_;
};

#include /**/ "ace/post.h"
#endif /* ONEWAYS_INVOKING_TWOWAYS_SERVER_TASK_H*/
