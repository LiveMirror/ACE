// -*- C++ -*-
// $Id: WU_LateBinding_Sender_exec.cpp 94802 2011-10-20 09:46:10Z mcorino $

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v1.8.2
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

#include "WU_LateBinding_Sender_exec.h"
#include "tao/ORB_Core.h"
#include "ace/Reactor.h"

namespace CIAO_WU_LateBinding_Sender_Impl
{

  /**
   * Timeout_Handler
   */

  Timeout_Handler::Timeout_Handler (Sender_exec_i &callback)
    : callback_ (callback)
  {
  }

  int
  Timeout_Handler::handle_timeout (const ACE_Time_Value &, const void *arg)
  {
    // Notify the subscribers
    unsigned long assingment = reinterpret_cast<unsigned long> (arg);
    if (assingment == 0)
      {
        this->callback_.start_event_test ();
      }
    else if (assingment == 1)
      {
        this->callback_.start_state_test ();
        this->callback_.set_topic_name_writer ();
        this->callback_.set_topic_name_updater ();
      }
    return 0;
  }

  /**
   * Component Executor Implementation Class: Sender_exec_i
   */

  Sender_exec_i::Sender_exec_i (void)
    : iterations_ (0)
      , keys_ (0)
      , to_handler_ (0)
  {
     ACE_NEW_THROW_EX (this->to_handler_,
                       Timeout_Handler (*this),
                       ::CORBA::INTERNAL ());
  }

  Sender_exec_i::~Sender_exec_i (void)
  {
    delete this->to_handler_;
  }

  // Supported operations and attributes.
  ACE_Reactor*
  Sender_exec_i::reactor (void)
  {
    ACE_Reactor* reactor = 0;
    ::CORBA::Object_var ccm_object =
      this->ciao_context_->get_CCM_object();
    if (! ::CORBA::is_nil (ccm_object.in ()))
      {
        ::CORBA::ORB_var orb = ccm_object->_get_orb ();
        if (! ::CORBA::is_nil (orb.in ()))
          {
            reactor = orb->orb_core ()->reactor ();
          }
      }
    if (reactor == 0)
      {
        throw ::CORBA::INTERNAL ();
      }
    return reactor;
  }

  void
  Sender_exec_i::test_exception (void)
  {
    try
      {
        ::WU_LateBinding::WU_LateBindingTestConnector::Writer_var writer =
          this->ciao_context_->get_connection_info_write_data ();
        if (::CORBA::is_nil (writer.in ()))
          {
            ACE_ERROR ((LM_ERROR, "Sender_exec_i::test_exception - "
                        "ERROR: Unable to get writer interface from the "
                        "CIAO context\n"));
            return;
          }
        WU_LateBindingTest sample;
        sample.key = ::CORBA::string_dup ("KEY_1");
        sample.iteration = 1;
        writer->write_one (sample, ::DDS::HANDLE_NIL);
        ACE_ERROR ((LM_ERROR, "Sender_exec_i::test_exception - "
                    "ERROR: No exception thrown while calling write_one "
                    "on a late binded connector (port).\n"));
      }
    catch (const ::CORBA::BAD_INV_ORDER &)
      {
        ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::test_exception - "
                    "Expected BAD_INV_ORDER thrown.\n"));
      }
    catch (const CORBA::Exception &e)
      {
        e._tao_print_exception("ERROR: Unexpected exception");
      }
    catch (...)
      {
        ACE_ERROR ((LM_ERROR, "Sender_exec_i::test_exception - "
                    "ERROR: expected and unknown exception caught\n"));
      }
  }

  void
  Sender_exec_i::set_topic_name_writer (void)
  {
    try
      {
        ::WU_LateBinding::WU_LateBindingTestConnector:: Writer_var writer =
          this->ciao_context_->get_connection_info_write_data ();
        if (::CORBA::is_nil (writer.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_writer - "
                                  "Unable to get writer interface\n"));
            throw ::CORBA::INTERNAL ();
          }
        ::CORBA::Object_var cmp = writer->_get_component ();
        if (::CORBA::is_nil (cmp.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_writer - "
                                  "Unable to get component interface\n"));
            throw ::CORBA::INTERNAL ();
          }
        ::WU_LateBinding::WU_LateBindingTestConnector::CCM_DDS_Event_var conn =
          ::WU_LateBinding::WU_LateBindingTestConnector::CCM_DDS_Event::_narrow (cmp.in ());
        if (::CORBA::is_nil (conn.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_writer - "
                                  "Unable to narrow connector interface\n"));
            throw ::CORBA::INTERNAL ();
          }
        conn->topic_name ("LateBindingTopic");
      }
    catch (const ::CCM_DDS::NonChangeable &)
      {
        ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_writer - "
                    "Caught NonChangeable exception.\n"));
      }
    catch (const ::CORBA::Exception &ex)
      {
        ex._tao_print_exception("ERROR: Sender_exec_i::set_topic_name_writer - ");
      }
  }

  void
  Sender_exec_i::start_event_test (void)
  {
    // Set the topic name on the connector first. Therefor we need to
    // get to the connector first.
    ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::start_event_test - "
                "Set topic name.\n"));
    try
      {
        this->set_topic_name_writer ();
        ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::start_event_test - "
                    "Topic name set, start writing.\n"));

        ::WU_LateBinding::WU_LateBindingTestConnector:: Writer_var writer =
          this->ciao_context_->get_connection_info_write_data ();
        for (::CORBA::UShort key = 1; key < this->keys_ + 1; ++key)
          {
            WU_LateBindingTest sample;
            char tmp[7];
            ACE_OS::sprintf (tmp, "KEY_%d", key);
            sample.key = CORBA::string_dup(tmp);

            for (::CORBA::UShort iter = 1; iter < this->iterations_ + 1; ++iter)
              {
                sample.iteration = iter;
                writer->write_one (sample, ::DDS::HANDLE_NIL);
                ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::start_event_test - "
                            "Sample written : key <%C> - iteration <%d>\n",
                            tmp, iter));
                ACE_Time_Value tv (0, 50000);
                ACE_OS::sleep (tv);
              }
          }
      }
    catch (...)
      {
        ACE_ERROR ((LM_ERROR, "Sender_exec_i::start_event_test - "
                    "ERROR: Unexpected and unknown exception caught.\n"));
      }
  }

  void
  Sender_exec_i::set_topic_name_updater(void)
  {
    try
      {
        ::WU_LateBinding::WU_LateBindingTestConnector:: Updater_var updater =
          this->ciao_context_->get_connection_info_update_data ();
        if (::CORBA::is_nil (updater.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_updater - "
                                  "Unable to get updater interface\n"));
            throw ::CORBA::INTERNAL ();
          }
        ::CORBA::Object_var cmp = updater->_get_component ();
        if (::CORBA::is_nil (cmp.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_updater - "
                                  "Unable to get component interface\n"));
            throw ::CORBA::INTERNAL ();
          }
        ::WU_LateBinding::WU_LateBindingTestConnector::CCM_DDS_State_var conn =
          ::WU_LateBinding::WU_LateBindingTestConnector::CCM_DDS_State::_narrow (cmp.in ());
        if (::CORBA::is_nil (conn.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_updater - "
                                  "Unable to narrow connector interface\n"));
            throw ::CORBA::INTERNAL ();
          }
        conn->topic_name ("LateBindingTopic");
      }
    catch (const ::CCM_DDS::NonChangeable &)
      {
        ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_updater - "
                    "Caught NonChangeable exception.\n"));
      }
    catch (const ::CORBA::Exception &ex)
      {
        ex._tao_print_exception("ERROR: Sender_exec_i::set_topic_name_writer - ");
      }
  }

  void
  Sender_exec_i::start_state_test (void)
  {
    ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::start_state_test - "
                          "Start\n"));
    try
      {
        this->set_topic_name_updater ();
        ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::start_state_test - "
                    "Topic name set, start updating.\n"));
        ::WU_LateBinding::WU_LateBindingTestConnector:: Updater_var updater =
          this->ciao_context_->get_connection_info_update_data ();
        for (::CORBA::UShort key = this->keys_ + 1;
             key < (2 * this->keys_) + 1;
             ++key)
          {
            WU_LateBindingTest sample;
            char tmp[7];
            ACE_OS::sprintf (tmp, "KEY_%d", key);
            sample.key = CORBA::string_dup(tmp);
            sample.iteration = 0;
            updater->create_one (sample);

            for (::CORBA::UShort iter = this->iterations_ + 1;
                 iter < (2 * this->iterations_) + 1;
                 ++iter)
              {
                sample.iteration = iter;
                updater->update_one (sample, ::DDS::HANDLE_NIL);
                ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::start_state_test - "
                            "Sample updated : key <%C> - iteration <%d>\n",
                            tmp, iter));
                ACE_Time_Value tv (0, 50000);
                ACE_OS::sleep (tv);
              }
          }
      }
    catch (...)
      {
        ACE_ERROR ((LM_ERROR, "Sender_exec_i::start_state_test - "
                    "ERROR: Unexpected and unknown exception caught.\n"));
      }
  }

  // Component attributes and port operations.

  ::CORBA::UShort
  Sender_exec_i::iterations (void)
  {
    return this->iterations_;
  }

  void
  Sender_exec_i::iterations (
    const ::CORBA::UShort iterations)
  {
    this->iterations_ = iterations;
  }

  ::CORBA::UShort
  Sender_exec_i::keys (void)
  {
    return this->keys_;
  }

  void
  Sender_exec_i::keys (
    const ::CORBA::UShort keys)
  {
    this->keys_ = keys;
  }

  // Operations from Components::SessionComponent.

  void
  Sender_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::WU_LateBinding::CCM_Sender_Context::_narrow (ctx);

    if ( ::CORBA::is_nil (this->ciao_context_.in ()))
      {
        throw ::CORBA::INTERNAL ();
      }
  }

  void
  Sender_exec_i::configuration_complete (void)
  {
    /* Your code here. */
  }

  void
  Sender_exec_i::ccm_activate (void)
  {
     this->test_exception ();
     if (this->reactor ()->schedule_timer (
                 this->to_handler_,
                 reinterpret_cast<const void *> (0),
                 ACE_Time_Value (5, 0)) == -1)
       {
         ACE_ERROR ((LM_ERROR, ACE_TEXT ("Sender_exec_i::start : ")
                               ACE_TEXT ("Error scheduling timer")));
       }
     if (this->reactor ()->schedule_timer (
                 this->to_handler_,
                 reinterpret_cast<const void *> (1),
                 ACE_Time_Value (10, 0)) == -1)
       {
         ACE_ERROR ((LM_ERROR, ACE_TEXT ("Sender_exec_i::start : ")
                               ACE_TEXT ("Error scheduling timer")));
       }
  }

  void
  Sender_exec_i::ccm_passivate (void)
  {
  }

  void
  Sender_exec_i::ccm_remove (void)
  {
    /* Your code here. */
  }

  extern "C" SENDER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_WU_LateBinding_Sender_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      Sender_exec_i);

    return retval;
  }
}
