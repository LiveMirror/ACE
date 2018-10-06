
//=============================================================================
/**
 *  @file   test_i.h
 *
 *  $Id: test_i.h 93650 2011-03-28 08:44:53Z johnnyw $
 *
 *  @author Carlos O'Ryan
 */
//=============================================================================


#ifndef TAO_NATIVE_EXCEPTIONS_TEST_I_H
#define TAO_NATIVE_EXCEPTIONS_TEST_I_H

#include "testS.h"

/**
 * @class Simple_Server_i
 *
 * @brief Simpler Server implementation
 *
 * Implements the Simple_Server interface in test.idl
 */
class Simple_Server_i : public POA_Simple_Server
{
public:
  /// ctor
  Simple_Server_i (CORBA::ORB_ptr orb);

  // = The Simple_Server methods.
  CORBA::Long test_method (CORBA::Long x);

  CORBA::Long test_raise (CORBA::Long x);

  void shutdown (void);

private:
  CORBA::ORB_var orb_;
};

#if defined(__ACE_INLINE__)
#include "test_i.inl"
#endif /* __ACE_INLINE__ */

#endif /* TAO_NATIVE_EXCEPTIONS_TEST_I_H */
