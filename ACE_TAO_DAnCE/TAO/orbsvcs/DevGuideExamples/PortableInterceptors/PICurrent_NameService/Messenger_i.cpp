/* -*- C++ -*- $Id: Messenger_i.cpp 83398 2008-10-22 15:45:34Z sowayaa $ */

// ******  Code generated by the The ACE ORB (TAO) IDL Compiler *******
// TAO and the TAO IDL Compiler have been developed by the Center for
// Distributed Object Computing at Washington University, St. Louis.
//
// Information about TAO is available at:
//                 http://www.cs.wustl.edu/~schmidt/TAO.html

#include "Messenger_i.h"
#include "ace/OS_NS_time.h"
#if defined (ACE_HAS_STANDARD_CPP_LIBRARY) && (ACE_HAS_STANDARD_CPP_LIBRARY == 1)
#include <iostream>
#else
#include <iostream.h>
#endif

// Implementation skeleton constructor
Messenger_i::Messenger_i (void)
  {
  }

// Implementation skeleton destructor
Messenger_i::~Messenger_i (void)
  {
  }

CORBA::Boolean Messenger_i::send_message (
    const char * user_name,
    const char * subject,
    char *& message
  )

  {
    //Add your implementation here
    std::cerr << "Message from: " << user_name << std::endl;
    std::cerr << "Subject:      " << subject << std::endl;
    std::cerr << "Message:      " << message << std::endl;
    return 1;
  }

char * Messenger_i::get_time (

  )

{
  time_t thetime;
  struct tm * timeinfo;

  ACE_OS::time(&thetime);
  timeinfo = ACE_OS::localtime(&thetime);
  char *timestring = CORBA::string_dup(ACE_OS::asctime(timeinfo));

  return timestring;
}
