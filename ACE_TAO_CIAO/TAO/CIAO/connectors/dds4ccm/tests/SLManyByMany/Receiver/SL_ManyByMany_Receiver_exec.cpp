// -*- C++ -*-
// $Id: SL_ManyByMany_Receiver_exec.cpp 97302 2013-08-29 11:15:22Z johnnyw $

#include "SL_ManyByMany_Receiver_exec.h"
#include "tao/ORB_Core.h"
#include "ace/Reactor.h"

#include "dds4ccm/impl/TimeUtilities.h"

#define ON_CREATION_EXPECTED 4
#define ON_MANY_EXPECTED 4
#define ON_MANY_TRIGGERED 2
#define ON_DELETION_EXPECTED 4
#define ON_READER_EXPECTED 0

namespace CIAO_SL_ManyByMany_Receiver_Impl
{
  /**
   * Facet Executor Implementation Class: info_out_data_listener_exec_i
   */

  read_action_Generator::read_action_Generator (Receiver_exec_i &callback)
    : pulse_callback_ (callback)
  {
  }

  read_action_Generator::~read_action_Generator ()
  {
  }

  int
  read_action_Generator::handle_timeout (const ACE_Time_Value &, const void *)
  {
    this->pulse_callback_.read_all();
    return 0;
  }

  /**
   * Facet Executor Implementation Class: info_out_data_listener_exec_i
   */

  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
        ::SL_ManyByMany::CCM_Receiver_Context_ptr ctx,
        Atomic_Long &no_operation,
        Atomic_Long &on_creation,
        Atomic_Long &on_many_update,
        Atomic_Long &on_many_upd_trigger,
        Atomic_Long &on_deletion,
        Atomic_Bool &create_data,
        Atomic_Bool &update_data,
        Atomic_Long &samples_read)
    : ciao_context_ (
        ::SL_ManyByMany::CCM_Receiver_Context::_duplicate (ctx))
      , no_operation_ (no_operation)
      , on_creation_ (on_creation)
      , on_many_update_ (on_many_update)
      , on_many_upd_trigger_ (on_many_upd_trigger)
      , on_deletion_ (on_deletion)
      , create_data_ (create_data)
      , update_data_ (update_data)
      , samples_read_ (samples_read)
  {
  }

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i (void)
  {
  }

  // Operations from ::SL_ManyByMany::SLManyByManyConnector::StateListener

  void
  info_out_data_listener_exec_i::on_creation (const ::TestTopic & datum,
  const ::CCM_DDS::ReadInfo & info)
  {
    ++this->on_creation_;
    ACE_Time_Value tv;
    tv <<= info.source_timestamp;
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("on_creation ReadInfo ")
                          ACE_TEXT ("-> UTC date =%#T\n"),
                          &tv));

    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("Statelistener:on_creation : ")
                          ACE_TEXT ("Received datum for <%C> at %u\n"),
                          datum.key.in (),
                          datum.x));
    // One of the data must have the key 'KEY_1' with x == 1
    if (ACE_OS::strcmp (datum.key.in(), "KEY_1") == 0 && datum.x == 1L)
      {
        this->create_data_ = true;
      }
  }

  void
  info_out_data_listener_exec_i::on_one_update (const ::TestTopic & /* datum */,
  const ::CCM_DDS::ReadInfo & /* info */)
  {
    ++this->no_operation_;
  }

  void
  info_out_data_listener_exec_i::on_many_updates (const ::TestTopicSeq & data,
  const ::CCM_DDS::ReadInfoSeq & infos)
  {
    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("on_many_update triggered,")
                          ACE_TEXT (" received sequence of ")
                          ACE_TEXT ("<%u> samples\n"),
                          infos.length()));
    //number of times this is triggered
    this->on_many_upd_trigger_ ++;

    //number of total samples received
    this->on_many_update_ += infos.length();
    for(CORBA::ULong i = 0; i < infos.length(); ++i)
      {
        if (infos[i].instance_status != CCM_DDS::INSTANCE_UPDATED)
          {
            ACE_ERROR ((LM_ERROR,
                        ACE_TEXT ("ERROR: did not receive the expected ")
                        ACE_TEXT ("info.instance_status ")
                        ACE_TEXT ("'CCM_DDS::INSTANCE_UPDATED' ")
                        ACE_TEXT ("with operation 'on_many_updates' ")
                        ACE_TEXT ("from StateListener in Receiver\n")
                        ));

          }
        ACE_Time_Value tv;
        tv <<= infos[i].source_timestamp;
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("on_many_updates ReadInfo ")
                              ACE_TEXT ("-> UTC date =%#T\n"),
                              &tv));
      }
    for (CORBA::ULong i = 0; i < data.length(); ++i)
      {
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("on_many_updates info : Number <%d> :")
                              ACE_TEXT (" received TestTopic_info ")
                              ACE_TEXT ("for <%C> at %u\n"),
                              i,
                              data[i].key.in (),
                              data[i].x));
        // one of the data must have the key 'KEY_1' with x == 2
        if (ACE_OS::strcmp(data[i].key,"KEY_1") == 0 && data[i].x == 2L)
          {
            this->update_data_ = true;
          }
       }

    // When we have received all updates, check if there is
    // something left in the cache
    if(this->on_many_update_.value () == ON_MANY_EXPECTED)
      {
        try
          {
            SL_ManyByMany::SLManyByManyConnector::Reader_var reader =
              this->ciao_context_->get_connection_info_out_data ();
            if (::CORBA::is_nil (reader.in ()))
              {
                ACE_ERROR ((LM_ERROR, "info_out_data_listener_exec_i::on_many_updates - "
                          "ERROR: Reader seems nil\n"));
              }
            ::TestTopicSeq seq;
            ::CCM_DDS::ReadInfoSeq infos;
            reader->read_all (seq, infos);
            this->samples_read_ += seq.length ();

            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("info_out_data_listener_exec_i::on_many_updates - ")
                                  ACE_TEXT ("Read <%u> samples\n"),
                                  seq.length ()));
          }
        catch (const CCM_DDS::InternalError& ex)
          {
            ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR: Internal Error ")
                        ACE_TEXT ("when using reader->read_all: index <%d> - retval <%d>\n"),
                        ex.index, ex.error_code));
          }
      }
  }

  void
  info_out_data_listener_exec_i::on_deletion (const ::TestTopic & datum,
  const ::CCM_DDS::ReadInfo & info)
  {
    if (info.instance_status != CCM_DDS::INSTANCE_DELETED)
      {
        ACE_ERROR ((LM_ERROR,
                    ACE_TEXT ("ERROR: did not receive the expected ")
                    ACE_TEXT ("info.instance_status ")
                    ACE_TEXT ("'CCM_DDS::INSTANCE_DELETED' with operation ")
                    ACE_TEXT ("'on_deletion' from StateListener in Receiver\n")
                   ));

      }
    else
      {
        // Because of the settings <serialize_key_with_dispose> and
        // <propagate_dispose_of_unregistered_instances> in the QoS , we expect
        // an existing datum.key
        // Since these are RTI DDS specific QOS settings, we only need to test
        // this in case RTI DDS
#if (CIAO_DDS4CCM_NDDS==1)
        if ((ACE_OS::strncmp (datum.key.in(), "KEY", 3) == 0  ) ||
            (ACE_OS::strncmp (datum.key.in(), "many", 4) == 0  ))
          {
            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("Statelistener:on_deletion : ")
                        ACE_TEXT ("Received datum for <%C> \n"),
                        datum.key.in ()));
            ++this->on_deletion_;
           }
        else
          {
            ACE_ERROR ((LM_ERROR,
                        ACE_TEXT ("ERROR Statelistener:on_deletion : did not ")
                        ACE_TEXT ("receive the expected datum, received <%C>")
                        ACE_TEXT (", expected <KEY_.> or <many_.>\n"),
                        datum.key.in ()));
          }
#else
        ++this->on_deletion_;
        ACE_UNUSED_ARG (datum);
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("Statelistener:on_deletion : ")
                    ACE_TEXT ("Received on_deletion event\n")));

#endif
      }
  }

  /**
   * Facet Executor Implementation Class: info_out_status_exec_i
   */

  info_out_status_exec_i::info_out_status_exec_i (
        ::SL_ManyByMany::CCM_Receiver_Context_ptr ctx)
    : ciao_context_ (
        ::SL_ManyByMany::CCM_Receiver_Context::_duplicate (ctx))
  {
  }

  info_out_status_exec_i::~info_out_status_exec_i (void)
  {
  }

  // Operations from ::CCM_DDS::PortStatusListener

  void
  info_out_status_exec_i::on_requested_deadline_missed (::DDS::DataReader_ptr /* the_reader */,
  const ::DDS::RequestedDeadlineMissedStatus & /* status */)
  {
    /* Your code here. */
  }

  void
  info_out_status_exec_i::on_sample_lost (::DDS::DataReader_ptr /* the_reader */,
  const ::DDS::SampleLostStatus & /* status */)
  {
    /* Your code here. */
  }

  /**
   * Component Executor Implementation Class: Receiver_exec_i
   */

  Receiver_exec_i::Receiver_exec_i (void)
    : no_operation_ (0)
      , on_creation_ (0)
      , on_many_update_ (0)
      , on_many_upd_trigger_ (0)
      , on_deletion_ (0)
      , create_data_ (false)
      , update_data_ (false)
      , reader_data_ (0)
      , samples_read_ (0)
  {
    ACE_NEW_THROW_EX (this->ticker_,
                      read_action_Generator (*this),
                      ::CORBA::NO_MEMORY ());
  }

  Receiver_exec_i::~Receiver_exec_i (void)
  {
    delete this->ticker_;
  }

  // Supported operations and attributes.
  ACE_Reactor*
  Receiver_exec_i::reactor (void)
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
  Receiver_exec_i::read_all (void)
  {
    ::SL_ManyByMany::SLManyByManyConnector::Reader_var reader =
      this->ciao_context_->get_connection_info_out_data ();

    if ( ::CORBA::is_nil (reader.in ()))
      {
        ACE_ERROR ((LM_ERROR, "Receiver_exec_i::read_all - "
                  "Reader seems nil\n"));
        return;
      }
    try
      {
       TestTopicSeq TestTopic_infos;
        ::CCM_DDS::ReadInfoSeq readinfoseq;
        reader->read_all (TestTopic_infos, readinfoseq);
        this->reader_data_ += TestTopic_infos.length ();
        for (CORBA::ULong i = 0; i < readinfoseq.length (); ++i)
          {
            ACE_Time_Value tv;
            tv <<= readinfoseq[i].source_timestamp;
            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("READ_ALL ReadInfo ")
                                  ACE_TEXT ("-> UTC date =%#T\n"),
                                  &tv));
          }
        for (CORBA::ULong i = 0; i < TestTopic_infos.length (); ++i)
          {
            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("READ_ALL info : ")
                        ACE_TEXT ("Number <%d> : received TestTopic_info for <%C> at %u\n"),
                        i,
                        TestTopic_infos[i].key.in (),
                        TestTopic_infos[i].x));
          }
      }
    catch (const CCM_DDS::InternalError& )
      {
        ACE_DEBUG ((LM_DEBUG, "Receiver_exec_i::read_all - "
                  "internal error or no data\n"));
      }
  }
  // Component attributes and port operations.

  ::SL_ManyByMany::SLManyByManyConnector::CCM_StateListener_ptr
  Receiver_exec_i::get_info_out_data_listener (void)
  {
    if ( ::CORBA::is_nil (this->ciao_info_out_data_listener_.in ()))
      {
        info_out_data_listener_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          info_out_data_listener_exec_i (
            this->ciao_context_.in (),
            this->no_operation_,
            this->on_creation_,
            this->on_many_update_,
            this->on_many_upd_trigger_,
            this->on_deletion_,
            this->create_data_,
            this->update_data_,
            this->samples_read_),
            ::SL_ManyByMany::SLManyByManyConnector::CCM_StateListener::_nil ());

          this->ciao_info_out_data_listener_ = tmp;
      }

    return
      ::SL_ManyByMany::SLManyByManyConnector::CCM_StateListener::_duplicate (
        this->ciao_info_out_data_listener_.in ());
  }

  ::CCM_DDS::CCM_PortStatusListener_ptr
  Receiver_exec_i::get_info_out_status (void)
  {
    if ( ::CORBA::is_nil (this->ciao_info_out_status_.in ()))
      {
        info_out_status_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          info_out_status_exec_i (
            this->ciao_context_.in ()),
            ::CCM_DDS::CCM_PortStatusListener::_nil ());

          this->ciao_info_out_status_ = tmp;
      }

    return
      ::CCM_DDS::CCM_PortStatusListener::_duplicate (
        this->ciao_info_out_status_.in ());
  }

  // Operations from Components::SessionComponent.

  void
  Receiver_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::SL_ManyByMany::CCM_Receiver_Context::_narrow (ctx);

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
    ::CCM_DDS::StateListenerControl_var lc =
    this->ciao_context_->get_connection_info_out_data_control ();

    if (::CORBA::is_nil (lc.in ()))
      {
         ACE_ERROR ((LM_INFO, "Receiver_exec_i::ccm_activate - "
                   "ERROR:  Listener control receptacle is null!\n"));
        throw ::CORBA::INTERNAL ();
      }

    lc->mode (::CCM_DDS::MANY_BY_MANY);
    if (this->reactor ()->schedule_timer (this->ticker_,
                                          0,
                                        ACE_Time_Value(18, 0),
                                        ACE_Time_Value(1, 0)) == -1)
   //                                        ACE_Time_Value(1, 0),
   //                                        ACE_Time_Value(1, 0)) == -1)
      {
         ACE_ERROR ((LM_INFO, "Receiver_exec_i::ccm_activate - "
                   "ERROR:  Unable to schedule timer!\n"));
      }
  }

  void
  Receiver_exec_i::ccm_passivate (void)
  {
    this->reactor ()->cancel_timer (this->ticker_);
  }

  void
  Receiver_exec_i::ccm_remove (void)
  {
    if (this->no_operation_.value () > 0)
      {
         ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR: did receive an unexpected ")
                               ACE_TEXT ("operation 'on_one_update' from ")
                               ACE_TEXT ("StateListener in Receiver\n")
                    ));
      }
    else
      {
         ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("OK: did not receive an unexpected ")
                               ACE_TEXT ("operation 'on_one_update' from ")
                               ACE_TEXT ("StateListener in Receiver\n")
                    ));
      }

    if (this->on_creation_.value () != ON_CREATION_EXPECTED)
      {
         ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR: didn't receive the expected ")
                               ACE_TEXT ("number of 'on_creation' calls: ")
                               ACE_TEXT ("expected <%d> - received <%d>\n"),
                               ON_CREATION_EXPECTED,
                               this->on_creation_.value ()
                    ));
      }
    else
      {
         ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("OK: did receive the expected ")
                               ACE_TEXT ("number of 'on_creation' calls: ")
                               ACE_TEXT ("expected <%d> - received <%d>\n"),
                               ON_CREATION_EXPECTED,
                               this->on_creation_.value ()
                    ));
      }

    if (!this->create_data_ .value ())
      {
         ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR: didn't receive the expected ")
                               ACE_TEXT ("sample in 'on_creation' from ")
                               ACE_TEXT ("StateListener in Receiver\n")
                    ));
      }
    else
      {
         ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("OK: did receive the expected ")
                               ACE_TEXT ("sample in 'on_creation' from ")
                               ACE_TEXT ("StateListener in Receiver\n")
                    ));
      }

    if(this->on_many_upd_trigger_.value  () < ON_MANY_TRIGGERED)
      {
         ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR: didn't trigger the expected ")
                               ACE_TEXT ("number of 'on_many_update': ")
                               ACE_TEXT ("expected minimum <%d> - received <%d>\n"),
                               ON_MANY_TRIGGERED,
                               this->on_many_upd_trigger_.value ()
                    ));
      }
    else
      {
         ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("OK: did trigger the minimum expected ")
                               ACE_TEXT ("number of 'on_many_update': ")
                               ACE_TEXT ("expected <%d> - received <%d>\n"),
                               ON_MANY_TRIGGERED,
                               this->on_many_upd_trigger_.value ()
                    ));
      }
    if(this->on_many_update_.value  () != ON_MANY_EXPECTED)
      {
         ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR: didn't receive the expected ")
                               ACE_TEXT ("number of 'on_many_update' samples: ")
                               ACE_TEXT ("expected <%d> - received <%d>\n"),
                               ON_MANY_EXPECTED,
                               this->on_many_update_.value ()
                    ));
      }
    else
      {
         ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("OK: did receive the expected ")
                               ACE_TEXT ("number of 'on_many_update' samples: ")
                               ACE_TEXT ("expected <%d> - received <%d>, ")
                               ACE_TEXT ("on_many_update triggered at <%d> times.\n"),
                               ON_MANY_EXPECTED,
                               this->on_many_update_.value (),
                               ON_MANY_TRIGGERED
                    ));
      }

    if (!this->update_data_.value ())
      {
         ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR:didn't receive the expected ")
                               ACE_TEXT (" data with 'on_many_updates' from ")
                               ACE_TEXT ("StateListener in Receiver\n")
                    ));
      }
    else
      {
         ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("OK: did receive the expected ")
                               ACE_TEXT ("sample in 'on_many_updates' from ")
                               ACE_TEXT ("StateListener in Receiver\n")
                    ));
      }

    if (this->on_deletion_.value () != ON_DELETION_EXPECTED)
      {
         ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR: didn't receive the expected ")
                               ACE_TEXT ("number of 'on_deletion' calls: ")
                               ACE_TEXT ("expected <%d> - received <%d>\n"),
                               ON_DELETION_EXPECTED,
                               this->on_deletion_.value ()
                    ));
      }
    else
      {
         ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("OK: did receive the expected ")
                               ACE_TEXT ("number of 'on_deletion' calls: ")
                               ACE_TEXT ("expected <%d> - received <%d>\n"),
                               ON_DELETION_EXPECTED,
                               this->on_deletion_.value ()
                    ));
      }

    if (this->reader_data_.value () != ON_READER_EXPECTED)
      {
         ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR: didn't read the expected ")
                               ACE_TEXT ("number of samples: ")
                               ACE_TEXT ("expected <%d> - received <%d>\n"),
                               ON_READER_EXPECTED,
                               this->reader_data_.value ()
                    ));
      }
    else
      {
         ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("OK: read the expected ")
                               ACE_TEXT ("number of samples: ")
                               ACE_TEXT ("expected <%d> - received <%d>\n"),
                               ON_READER_EXPECTED,
                               this->reader_data_.value ()
                    ));
      }
    if (this->samples_read_.value () == 0)
      {
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("ERROR: read no samples\n")));
      }
    else
      {
        ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("OK: read <%u> samples\n"),
                this->samples_read_.value ()));
      }
  }

  extern "C" RECEIVER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_SL_ManyByMany_Receiver_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      Receiver_exec_i);

    return retval;
  }
}
