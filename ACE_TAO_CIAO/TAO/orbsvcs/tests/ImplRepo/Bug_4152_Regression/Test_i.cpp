/* -*- C++ -*- $Id: Test_i.cpp 97526 2014-01-10 22:25:40Z mesnier_p $ */

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


