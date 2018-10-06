// -*- C++ -*-
// $Id: GetComp_Receiver_exec.cpp 92620 2010-11-17 11:11:36Z mhengstmengel $

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v1.8.3
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

#include "GetComp_Receiver_exec.h"

namespace CIAO_GetComp_Receiver_Impl
{

  /**
   * Facet Executor Implementation Class: do_my_foo_exec_i
   */

  do_my_foo_exec_i::do_my_foo_exec_i (
        ::GetComp::CCM_Receiver_Context_ptr ctx)
    : ciao_context_ (
        ::GetComp::CCM_Receiver_Context::_duplicate (ctx))
  {
  }

  do_my_foo_exec_i::~do_my_foo_exec_i (void)
  {
  }

  // Operations from ::GetComp::MyFoo

  ::CORBA::Long
  do_my_foo_exec_i::foo (const char * /*in_str*/,
      ::CORBA::String_out answer)
  {
    answer = CORBA::string_dup ("This is my answer : Hi");
    return 1;
  }

  /**
   * Component Executor Implementation Class: Receiver_exec_i
   */

  Receiver_exec_i::Receiver_exec_i (void){
  }

  Receiver_exec_i::~Receiver_exec_i (void)
  {
  }

  // Supported operations and attributes.

  // Component attributes and port operations.

  ::GetComp::CCM_MyFoo_ptr
  Receiver_exec_i::get_do_my_foo (void)
  {
    if ( ::CORBA::is_nil (this->ciao_do_my_foo_.in ()))
      {
        do_my_foo_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          do_my_foo_exec_i (
            this->ciao_context_.in ()),
            ::GetComp::CCM_MyFoo::_nil ());

          this->ciao_do_my_foo_ = tmp;
      }

    return
      ::GetComp::CCM_MyFoo::_duplicate (
        this->ciao_do_my_foo_.in ());
  }

  // Operations from Components::SessionComponent.

  void
  Receiver_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::GetComp::CCM_Receiver_Context::_narrow (ctx);

    if ( ::CORBA::is_nil (this->ciao_context_.in ()))
      {
        throw ::CORBA::INTERNAL ();
      }
  }

  void
  Receiver_exec_i::configuration_complete (void)
  {
    /* Your code here. */
  }

  void
  Receiver_exec_i::ccm_activate (void)
  {
    /* Your code here. */
  }

  void
  Receiver_exec_i::ccm_passivate (void)
  {
    /* Your code here. */
  }

  void
  Receiver_exec_i::ccm_remove (void)
  {
    /* Your code here. */
  }

  extern "C" GETCOMP_T_RECEIVER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_GetComp_Receiver_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      Receiver_exec_i);

    return retval;
  }
}
