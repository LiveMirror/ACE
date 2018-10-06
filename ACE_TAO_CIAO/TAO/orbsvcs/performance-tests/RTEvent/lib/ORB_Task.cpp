/**
 * @file ORB_Task.cpp
 *
 * $Id: ORB_Task.cpp 91675 2010-09-08 19:09:19Z johnnyw $
 *
 * @author Carlos O'Ryan <coryan@uci.edu>
 */

#include "ORB_Task.h"

#if !defined(__ACE_INLINE__)
#include "ORB_Task.inl"
#endif /* __ACE_INLINE__ */

ORB_Task::ORB_Task (CORBA::ORB_ptr orb)
  : orb_ (CORBA::ORB::_duplicate (orb))
{
}

int
ORB_Task::svc (void)
{
  try
    {
      this->orb_->run ();
    }
  catch (const CORBA::Exception&)
    {
      return -1;
    }
  return 0;
}
