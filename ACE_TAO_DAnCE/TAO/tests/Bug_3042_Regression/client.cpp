// -*- C++ -*-
// $Id: client.cpp 91648 2010-09-08 13:25:56Z johnnyw $

#include "testC.h"
#include "ace/Log_Msg.h"

int
ACE_TMAIN(int, ACE_TCHAR *[])
{
  try
    {
       // creation
       Foo::Node node;
       node.nodes.length (2);
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("Bug_3042_Test test:");
      return -1;
    }
  catch (...)
    {
      return -1;
    }
  return 0;
}
