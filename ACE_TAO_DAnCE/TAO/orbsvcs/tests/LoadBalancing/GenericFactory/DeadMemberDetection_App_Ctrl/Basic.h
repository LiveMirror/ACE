// -*- C++ -*-
//
// $Id: Basic.h 87872 2009-12-02 18:25:48Z dai_y $

#ifndef BASIC_H
#define BASIC_H

#include "TestS.h"
#include "orbsvcs/CosLoadBalancingC.h"
#include "orbsvcs/PortableGroupC.h"

#if defined (_MSC_VER)
# pragma warning(push)
# pragma warning (disable:4250)
#endif /* _MSC_VER */

class LB_Basic_Test;

/// Implement the Test::Basic interface
class Basic
  : public virtual POA_Test::Basic
{
public:
  Basic (int server_id);
  /// Constructor
  Basic (CORBA::Object_ptr object_group,
         CosLoadBalancing::LoadManager_ptr lm,
         CORBA::ORB_ptr orb,
         const char *loc,
         int server_id);

  /// Default _non_existent: always returns false.
  virtual CORBA::Boolean _non_existent (void);

  virtual char * get_string (void);

  virtual void shutdown (void);

  virtual void remove_member (void);

  virtual void exit (void);

private:
  /// Use an ORB reference to convert strings to objects and shutdown
  /// the application.
  CORBA::ORB_var orb_;

  /// Load Manager Reference used to delete the servant reference from the
  /// object group.
  CosLoadBalancing::LoadManager_var lm_;

  /// location of the servant
  CORBA::String_var location_;

  /// Object Group reference.
  CORBA::Object_var object_group_;

  int server_id_;
};

#if defined(_MSC_VER)
# pragma warning(pop)
#endif /* _MSC_VER */

#endif /* BASIC_H */
