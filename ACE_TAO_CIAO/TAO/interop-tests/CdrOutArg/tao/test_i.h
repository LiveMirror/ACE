// -*- C++ -*-

//=============================================================================
/**
 *  @file   test_i.h
 *
 *  $Id: test_i.h 97394 2013-10-28 21:54:55Z mesnier_p $
 *
 *  @author Phil Mesnier
 */
//=============================================================================


#ifndef CDR_OUT_ARG_TEST_I_H
#define CDR_OUT_ARG_TEST_I_H

#include "testS.h"

/**
 * @class CDR_Out_Arg_i
 *
 * Implements the CDR_Out_Arg interface
 */
class CDR_Out_Arg_i : public POA_Interop::CDR_Out_Arg
{

public:

  CDR_Out_Arg_i (CORBA::ORB_ptr orb);

  void get_out (CORBA::Long_out arg);

  void shutdown (void);

private:

  /// The ORB pseudo-reference (for shutdown).
  CORBA::ORB_var orb_;

};

#endif /* TAO_INTERCEPTOR_TEST_I_H */
