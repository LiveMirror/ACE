/* -*- C++ -*- $Id: Test_i.cpp 97583 2014-02-13 15:18:12Z mesnier_p $ */

#include "Test_i.h"

CORBA::Short
Test_i::get_server_num (void)
{
  return 1;
}

void
Test_i::terminate (void)
{
  exit (0);
}


