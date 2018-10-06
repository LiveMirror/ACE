// -*- C++ -*-
// $Id: TL_ResetTopic_Sender_exec.cpp 95872 2012-06-12 17:27:38Z johnnyw $

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

#include "TL_ResetTopic_Sender_exec.h"
#include "tao/ORB_Core.h"
#include "ace/Reactor.h"

namespace CIAO_TL_ResetTopic_Sender_Impl
{

  /**
   * Timeout_Handler
   */

  Timeout_Handler::Timeout_Handler (Sender_exec_i &callback)
    : callback_ (callback)
  {
  }

  int
  Timeout_Handler::handle_timeout (const ACE_Time_Value &, const void *)
  {
    // Notify the subscribers
    this->callback_.start_event_test ();
    return 0;
  }

  /**
   * Component Executor Implementation Class: Sender_exec_i
   */

  Sender_exec_i::Sender_exec_i (void)
    : iterations_ (0)
    , keys_ (0)
    , to_handler_ (0)
    , topic_name_ ("TopicI")
    , old_topic_name_ ("TopicI")
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

  void Sender_exec_i::set_new_topic (const char * topic_name)
  {
    ACE_GUARD (TAO_SYNCH_RECURSIVE_MUTEX, guard, this->topic_name_lock_);

    this->old_topic_name_ = this->topic_name_;
    this->topic_name_ = topic_name;
    ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::set_new_topic - "
              "New topic name set <%C>\n",
              topic_name));
  }

  void
  Sender_exec_i::create_samples (void)
  {
    for (CORBA::UShort i = 1; i < this->keys_ + 1; ++i)
      {
        char key[7];
        TL_ResetTopicTest *new_key = new TL_ResetTopicTest;
        ACE_OS::sprintf (key, "KEY_%d", i);
        new_key->key = CORBA::string_dup(key);
        new_key->iteration = 0;
        this->tests_[key] = new_key;

        ::TL_ResetTopic::TL_ResetTopicTestConnector::Updater_var updater =
          this->ciao_context_->get_connection_info_update_data();

        updater->create_one (*new_key);
        ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::create_samples - "
                  "Sample <%C> created\n",
                  key));
      }
  }

  bool
  Sender_exec_i::set_topic_name (const char * topic_name)
  {
    if (ACE_OS::strcmp (topic_name, this->old_topic_name_.c_str()) != 0)
      {
        this->old_topic_name_ = topic_name;
        bool ret = this->set_topic_name_writer (topic_name);
        ret |= this->set_topic_name_updater (topic_name);
        return ret;
      }
    if (ACE_OS::strlen (this->topic_name_.c_str()) > 256)
      return false;
    return true;
  }

  bool
  Sender_exec_i::set_topic_name_writer (const char * topic_name)
  {
    try
      {
        ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::set_topic_name_writer - "
                  "Setting topic to <%C>\n",
                  topic_name));
        ::TL_ResetTopic::TL_ResetTopicTestConnector:: Writer_var writer =
          this->ciao_context_->get_connection_info_write_data ();
        if (::CORBA::is_nil (writer.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_writer - "
                                  "Unable to get writer interface\n"));
            return false;
          }
        ::CORBA::Object_var cmp = writer->_get_component ();
        if (::CORBA::is_nil (cmp.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_writer - "
                                  "Unable to get component interface\n"));
            return false;
          }
        ::TL_ResetTopic::TL_ResetTopicTestConnector::CCM_DDS_Event_var conn =
          ::TL_ResetTopic::TL_ResetTopicTestConnector::CCM_DDS_Event::_narrow (cmp.in ());
        if (::CORBA::is_nil (conn.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_writer - "
                                  "Unable to narrow connector interface\n"));
            return false;
          }
        {
          ACE_GUARD_RETURN (TAO_SYNCH_RECURSIVE_MUTEX, guard, this->topic_name_lock_, false);
          conn->topic_name (topic_name);
        }
      }
    catch (const ::CCM_DDS::NonChangeable &)
      {
        ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_writer - "
                    "Caught NonChangeable exception.\n"));
        return false;
      }
    catch (const ::CCM_DDS::InternalError &)
      {
        if (ACE_OS::strlen (topic_name) > 256)
          {
            ACE_DEBUG ((LM_ERROR, "Sender_exec_i::set_topic_name_writer - "
                      "Expected InternalErr exception caught.\n"));
          }
        else
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_writer - "
                      "Caught InternalError exception.\n"));
          }
        return false;
      }
    return true;
  }

  bool
  Sender_exec_i::set_topic_name_updater (const char * topic_name)
  {
    try
      {
        ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::set_topic_name_updater - "
                  "Setting topic to <%C>\n",
                  topic_name));
        ::TL_ResetTopic::TL_ResetTopicTestConnector:: Updater_var updater =
          this->ciao_context_->get_connection_info_update_data ();
        if (::CORBA::is_nil (updater.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_updater - "
                                  "Unable to get updater interface\n"));
            return false;
          }
        ::CORBA::Object_var cmp = updater->_get_component ();
        if (::CORBA::is_nil (cmp.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_updater - "
                                  "Unable to get component interface\n"));
            return false;
          }
        ::TL_ResetTopic::TL_ResetTopicTestConnector::CCM_DDS_State_var conn =
          ::TL_ResetTopic::TL_ResetTopicTestConnector::CCM_DDS_State::_narrow (cmp.in ());
        if (::CORBA::is_nil (conn.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_updater - "
                                  "Unable to narrow connector interface\n"));
            return false;
          }
        {
          ACE_GUARD_RETURN (TAO_SYNCH_RECURSIVE_MUTEX, guard, this->topic_name_lock_, false);
          conn->topic_name (topic_name);
        }
        this->create_samples ();
      }
    catch (const ::CCM_DDS::NonChangeable &)
      {
        ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_updater - "
                    "Caught NonChangeable exception.\n"));
        return false;
      }
    catch (const ::CCM_DDS::InternalError &)
      {
        if (ACE_OS::strlen (topic_name) > 256)
          {
            ACE_DEBUG ((LM_ERROR, "Sender_exec_i::set_topic_name_updater - "
                      "Expected InternalErr exception caught.\n"));
          }
        else
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Sender_exec_i::set_topic_name_updater - "
                      "Caught InternalError exception.\n"));
          }
        return false;
      }
    return true;
  }

  void
  Sender_exec_i::start_event_test (void)
  {
    // Set the topic name on the connector first. Therefor we need to
    // get to the connector first.
    ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::start_event_test - Start\n"));

    try
      {
        for (::CORBA::UShort key = 1; key < this->keys_ + 1; ++key)
          {
            TL_ResetTopicTest sample;
            char tmp[7];
            ACE_OS::sprintf (tmp, "KEY_%d", key);
            sample.key = CORBA::string_dup(tmp);

            for (::CORBA::UShort iter = 1; iter < this->iterations_ + 1; ++iter)
              {
                if (this->set_topic_name (this->topic_name_.c_str ()))
                  {
                    ::TL_ResetTopic::TL_ResetTopicTestConnector:: Writer_var writer =
                      this->ciao_context_->get_connection_info_write_data ();
                    sample.iteration = iter;

                    writer->write_one (sample, ::DDS::HANDLE_NIL);

                    ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::start_event_test - "
                                "Sample for topic <%C> written : key <%C> - iteration <%d>\n",
                                this->topic_name_.c_str (), tmp, iter));
                  }

                ACE_Time_Value tv (0, 5000);
                ACE_OS::sleep (tv);
              }
          }
        for (Sample_Table::iterator iter = this->tests_.begin ();
            iter != this->tests_.end ();
            ++iter)
          {
            for (::CORBA::UShort i = 1; i < this->iterations_ + 1; ++i)
              {
                if (this->set_topic_name (this->topic_name_.c_str ()))
                  {
                    ::TL_ResetTopic::TL_ResetTopicTestConnector:: Updater_var updater =
                      this->ciao_context_->get_connection_info_update_data ();
                    iter->second->iteration = i;
                    updater->update_one (iter->second, ::DDS::HANDLE_NIL);

                    ACE_DEBUG ((LM_DEBUG, "Sender_exec_i::start_event_test - "
                                "Sample for topic <%C> updated : key <%C> - iteration <%d>\n",
                                this->topic_name_.c_str (),
                                iter->second->key.in (),
                                i));
                  }

                ACE_Time_Value tv (0, 5000);
                ACE_OS::sleep (tv);
              }
          }
      }
    catch (const ::CORBA::BAD_INV_ORDER & ex)
      {
        if (this->topic_name_.empty())
          ACE_DEBUG ((LM_DEBUG, "Expected BAD_INV_ORDER caught\n"));
        else
          ex._tao_print_exception("ERROR:");
      }
    catch (const ::CORBA::Exception & ex)
      {
        ex._tao_print_exception("ERROR:");
      }
    catch (...)
      {
        ACE_ERROR ((LM_ERROR, "Sender_exec_i::start_event_test - "
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
      ::TL_ResetTopic::CCM_Sender_Context::_narrow (ctx);

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
    this->create_samples ();
    if (this->reactor ()->schedule_timer (
                this->to_handler_,
                0,
                ACE_Time_Value (5, 0),
                ACE_Time_Value (5, 0)) == -1)
      {
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("Sender_exec_i::start : ")
                              ACE_TEXT ("Error scheduling timer")));
      }
  }

  void
  Sender_exec_i::ccm_passivate (void)
  {
    this->reactor()->cancel_timer(this->to_handler_);
  }

  void
  Sender_exec_i::ccm_remove (void)
  {
    /* Your code here. */
  }

  extern "C" SENDER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_TL_ResetTopic_Sender_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      Sender_exec_i);

    return retval;
  }
}
