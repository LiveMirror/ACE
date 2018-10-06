// -*- C++ -*-
// $Id: InterOutArgsT_Receiver_exec.cpp 92678 2010-11-23 14:10:59Z mhengstmengel $

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

#include "InterOutArgsT_Receiver_exec.h"

namespace CIAO_InterOutArgsT_Receiver_Impl
{

  /**
   * Facet Executor Implementation Class: do_my_foo_exec_i
   */

  do_my_foo_exec_i::do_my_foo_exec_i (
        ::InterOutArgsT::CCM_Receiver_Context_ptr ctx)
    : ciao_context_ (
        ::InterOutArgsT::CCM_Receiver_Context::_duplicate (ctx))
  {
  }

  do_my_foo_exec_i::~do_my_foo_exec_i (void)
  {
  }

  // Operations from ::InterOutArgsT::MyFoo

  void
  do_my_foo_exec_i::var_outs (const char * /* in_str */,
      ::CORBA::String_out answer,
        ::CORBA::Double_out d_cmd,
        ::CORBA::Long_out l_cmd)
  {
    answer = CORBA::string_dup ("This is my answer from var_outs");
    d_cmd = 3.14;
    l_cmd = 100;
  }

  void
  do_my_foo_exec_i::var_div_outs (::InterOutArgsT::TestTopic_out test_topic,
      ::InterOutArgsT::TopicString_out topic_str,
      ::InterOutArgsT::TopicArray_out topic_arr)
  {
    InterOutArgsT::TestTopic *new_topic = new InterOutArgsT::TestTopic();
    test_topic = new_topic;
    test_topic->key = CORBA::string_dup("aaa");
    test_topic->x = 10;

    topic_str = new InterOutArgsT::TopicString();
    topic_str->key = CORBA::string_dup("bbb");
    topic_str->x_str = CORBA::string_dup("ccc");

    topic_arr = new InterOutArgsT::TopicArray();
    topic_arr->key = CORBA::string_dup("ddd");
    for (CORBA::UShort i = 0; i < 5; i ++)
      {
        topic_arr->x_array[i] = i * 100;
      }
  }

  void
  do_my_foo_exec_i::var_div2_outs (::InterOutArgsT::X_Union_out x_uni,
      ::InterOutArgsT::test_seq_out seq)
  {
    x_uni = new InterOutArgsT::X_Union();
    x_uni->x_long(11);

    InterOutArgsT::test ttt;
    ttt.x_test = 12;
    ttt.x_teststr = CORBA::string_dup("fff") ;
    seq = new InterOutArgsT::test_seq();
    seq->length(2);
    (*seq)[0]= ttt;
  }

  void
  do_my_foo_exec_i::enum_out (::InterOutArgsT::test_enum_out out_test)
  {
    out_test = ::InterOutArgsT::ONE;
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

  ::InterOutArgsT::CCM_MyFoo_ptr
  Receiver_exec_i::get_do_my_foo (void)
  {
    if ( ::CORBA::is_nil (this->ciao_do_my_foo_.in ()))
      {
        do_my_foo_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          do_my_foo_exec_i (
            this->ciao_context_.in ()),
            ::InterOutArgsT::CCM_MyFoo::_nil ());

          this->ciao_do_my_foo_ = tmp;
      }

    return
      ::InterOutArgsT::CCM_MyFoo::_duplicate (
        this->ciao_do_my_foo_.in ());
  }

  // Operations from Components::SessionComponent.

  void
  Receiver_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::InterOutArgsT::CCM_Receiver_Context::_narrow (ctx);

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

  extern "C" INTEROUTARGS_T_RECEIVER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_InterOutArgsT_Receiver_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      Receiver_exec_i);

    return retval;
  }
}
