/* -*- C++ -*- $Id: MessengerShutdownTimer.cpp 85583 2009-06-09 13:47:38Z calabrese_p $ */

#include "MessengerShutdownTimer.h"

MessengerShutdownTimer::MessengerShutdownTimer (CORBA::ORB_ptr orb)
  : orb_(CORBA::ORB::_duplicate(orb))
{
}

int MessengerShutdownTimer::handle_timeout (
  const ACE_Time_Value &,
  const void*)
{
  ACE_DEBUG((LM_DEBUG, "In MessengerShutdownTimer::handle_timeout\n"));
  orb_->shutdown (false);
  return 0;
}
