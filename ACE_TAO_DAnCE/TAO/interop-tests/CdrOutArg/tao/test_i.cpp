// $Id: test_i.cpp 97394 2013-10-28 21:54:55Z mesnier_p $

#include "test_i.h"

CDR_Out_Arg_i::CDR_Out_Arg_i (CORBA::ORB_ptr orb)
  : orb_ (CORBA::ORB::_duplicate (orb))
{
}

void
CDR_Out_Arg_i::get_out (CORBA::Long_out arg)
{
  arg = 100;
}

void
CDR_Out_Arg_i::shutdown (void)
{
  this->orb_->shutdown (0);
}
