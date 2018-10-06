// -*- C++ -*-
// $Id: UsesSM_Receiver_exec.cpp 92723 2010-11-26 10:52:35Z mhengstmengel $

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

#include "UsesSM_Receiver_exec.h"
#include "ace/OS_NS_unistd.h"

namespace CIAO_UsesSM_Receiver_Impl
{

  /**
   * Facet Executor Implementation Class: do_my_one_exec_i
   */

  do_my_one_exec_i::do_my_one_exec_i (
        ::UsesSM::CCM_Receiver_Context_ptr ctx,
         Atomic_UShort &nr_of_one_received)
    : ciao_context_ (
        ::UsesSM::CCM_Receiver_Context::_duplicate (ctx)),
         nr_of_one_received_(nr_of_one_received)
  {
  }

  do_my_one_exec_i::~do_my_one_exec_i (void)
  {
  }

  // Operations from ::UsesSM::One

  ::CORBA::Long
  do_my_one_exec_i::foo (const char * in_str,
  ::CORBA::Long cmd,
  ::CORBA::String_out answer)
  {
    // sleep to make it possible to test asynchronous behavior.
    ACE_OS::sleep(2);
    ++this->nr_of_one_received_;
    answer = CORBA::string_dup (in_str);
    return cmd;
  }

  /**
   * Facet Executor Implementation Class: do_my_two_exec_i
   */

  do_my_two_exec_i::do_my_two_exec_i (
        ::UsesSM::CCM_Receiver_Context_ptr ctx,
         Atomic_UShort &nr_of_two_received)
    : ciao_context_ (
        ::UsesSM::CCM_Receiver_Context::_duplicate (ctx)),
         nr_of_two_received_(nr_of_two_received)
  {
  }

  do_my_two_exec_i::~do_my_two_exec_i (void)
  {
  }

  // Operations from ::UsesSM::Two

  void
  do_my_two_exec_i::bar (::CORBA::Long /* cmd */,
  ::CORBA::String_out answer)
  {
    ++this->nr_of_two_received_;
    answer = CORBA::string_dup ("answer TWO::bar");
  }

  /**
   * Component Executor Implementation Class: Receiver_exec_i
   */

  Receiver_exec_i::Receiver_exec_i (void)
  : nr_of_one_received_(0),
    nr_of_two_received_(0)
  {
  }

  Receiver_exec_i::~Receiver_exec_i (void)
  {
  }

  // Supported operations and attributes.

  // Component attributes and port operations.

  ::UsesSM::CCM_One_ptr
  Receiver_exec_i::get_do_my_one (void)
  {
    if ( ::CORBA::is_nil (this->ciao_do_my_one_.in ()))
      {
        do_my_one_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          do_my_one_exec_i (
            this->ciao_context_.in (),
            this->nr_of_one_received_),
            ::UsesSM::CCM_One::_nil ());

          this->ciao_do_my_one_ = tmp;
      }

    return
      ::UsesSM::CCM_One::_duplicate (
        this->ciao_do_my_one_.in ());
  }

  ::UsesSM::CCM_Two_ptr
  Receiver_exec_i::get_do_my_two (void)
  {
    if ( ::CORBA::is_nil (this->ciao_do_my_two_.in ()))
      {
        do_my_two_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          do_my_two_exec_i (
            this->ciao_context_.in (),
            this->nr_of_two_received_),
           ::UsesSM::CCM_Two::_nil ());

          this->ciao_do_my_two_ = tmp;
      }

    return
      ::UsesSM::CCM_Two::_duplicate (
        this->ciao_do_my_two_.in ());
  }

  // Operations from Components::SessionComponent.

  void
  Receiver_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::UsesSM::CCM_Receiver_Context::_narrow (ctx);

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
    //this receiver instance received my_one foo, or this is a receiver instance
    //that received my_two bar .
    if (((this->nr_of_one_received_.value() == 2) &&
          (this->nr_of_two_received_.value() == 0)) ||
         ((this->nr_of_two_received_.value() == 3) &&
          (this->nr_of_one_received_.value() == 0)))
       {
         if (this->nr_of_one_received_.value() == 2)
           {
             ACE_DEBUG ((LM_DEBUG, "OK: Receiver received the expected "
                                   "number of correct calls for foo (%u/2).\n",
                                   this->nr_of_one_received_.value()));
           }
         else
           {
             ACE_DEBUG ((LM_DEBUG, "OK: Receiver received the expected "
                                   "number of correct calls for bar (%u/3).\n",
                                   this->nr_of_two_received_.value()));
           }
       }
     else
       {
         ACE_ERROR ((LM_ERROR, "ERROR: Receiver didn't receive the expected "
                               "number of correct calls.\n"
                               "Expected 2 calls for foo but received %u or \n"
                               "Expected 3 calls for bar but received %u.\n",
                               this->nr_of_one_received_.value(),
                               this->nr_of_two_received_.value()));

       }
  }

  extern "C" USESSM_RECEIVER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_UsesSM_Receiver_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      Receiver_exec_i);

    return retval;
  }
}
