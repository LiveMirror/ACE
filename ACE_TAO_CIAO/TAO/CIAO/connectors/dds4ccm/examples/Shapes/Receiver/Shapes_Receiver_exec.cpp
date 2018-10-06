// -*- C++ -*-
// $Id: Shapes_Receiver_exec.cpp 96917 2013-03-14 09:22:28Z johnnyw $

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.0.0
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

#include "Shapes_Receiver_exec.h"
#include "tao/ORB_Core.h"
#include "ace/Reactor.h"
#include "ace/OS_NS_time.h"
#include "dds4ccm/impl/TimeUtilities.h"

namespace CIAO_Shapes_Receiver_Impl
{

  /**
   * Read action generator
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
    if (pulse_callback_.read_data ())
      {
        this->pulse_callback_.read_one();
        this->pulse_callback_.read_all();
      }
    if (pulse_callback_.get_data ())
      {
        this->pulse_callback_.get_one ();
      }
    return 0;
  }


  /**
   * Facet Executor Implementation Class: info_out_data_listener_exec_i
   */

  info_out_data_listener_exec_i::info_out_data_listener_exec_i (
        ::Shapes::CCM_Receiver_Context_ptr ctx)
    : ciao_context_ (
        ::Shapes::CCM_Receiver_Context::_duplicate (ctx))
  {
  }

  info_out_data_listener_exec_i::~info_out_data_listener_exec_i (void)
  {
  }

  // Operations from ::Shapes::Listener

  void
  info_out_data_listener_exec_i::on_one_data (const ::ShapeType & datum,
  const ::CCM_DDS::ReadInfo & /* info */)
  {
    ::Shapes::Reader_var reader =
      this->ciao_context_->get_connection_info_out_data ();
    ::CORBA::Object_var cmp = reader->_get_component ();
    if (::CORBA::is_nil (cmp.in ()))
      {
        ACE_ERROR ((LM_ERROR, "ERROR: info_out_data_listener_exec_i::on_one_data - "
                              "Unable to get component interface\n"));
        throw ::CORBA::INTERNAL ();
      }
    ::Shapes::CCM_DDS_Event_var conn =
      ::Shapes::CCM_DDS_Event::_narrow (cmp.in ());
    if (::CORBA::is_nil (conn.in ()))
      {
        ACE_ERROR ((LM_ERROR, "ERROR: info_out_data_listener_exec_i::on_one_data - "
                              "Unable to narrow connector interface\n"));
        throw ::CORBA::INTERNAL ();
      }
    CORBA::String_var topic = conn->topic_name ();

    ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("ShapeType_Listener: ")
            ACE_TEXT ("received shape_info <%C> for <%C> at X <%u> Y <%u> size <%u>\n"),
            topic.in (),
            datum.color.in (),
            datum.x,
            datum.y,
            datum.shapesize));
  }

  void
  info_out_data_listener_exec_i::on_many_data (const ::ShapeTypeSeq & /* data */,
  const ::CCM_DDS::ReadInfoSeq & /* infos */)
  {
    /* Your code here. */
  }

  /**
   * Facet Executor Implementation Class: info_out_status_exec_i
   */

  info_out_status_exec_i::info_out_status_exec_i (
        ::Shapes::CCM_Receiver_Context_ptr ctx)
    : ciao_context_ (
        ::Shapes::CCM_Receiver_Context::_duplicate (ctx))
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
   * Facet Executor Implementation Class: info_get_status_exec_i
   */

  info_get_status_exec_i::info_get_status_exec_i (
        ::Shapes::CCM_Receiver_Context_ptr ctx)
    : ciao_context_ (
        ::Shapes::CCM_Receiver_Context::_duplicate (ctx))
  {
  }

  info_get_status_exec_i::~info_get_status_exec_i (void)
  {
  }

  // Operations from ::CCM_DDS::PortStatusListener

  void
  info_get_status_exec_i::on_requested_deadline_missed (::DDS::DataReader_ptr /* the_reader */,
  const ::DDS::RequestedDeadlineMissedStatus & /* status */)
  {
    /* Your code here. */
  }

  void
  info_get_status_exec_i::on_sample_lost (::DDS::DataReader_ptr /* the_reader */,
  const ::DDS::SampleLostStatus & /* status */)
  {
    /* Your code here. */
  }

  /**
   * Component Executor Implementation Class: Receiver_exec_i
   */

  Receiver_exec_i::Receiver_exec_i (void)
    : rate_ (0)
      , get_data_ (true)
      , read_data_ (true)
      , raw_listen_ (false)
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
  Receiver_exec_i::read_one (void)
  {
    ShapeType  shape_info;
    shape_info.color = "GREEN";
    ::CCM_DDS::ReadInfo readinfo;

    try
      {
        ::Shapes::Reader_var reader =
          this->ciao_context_->get_connection_info_out_data ();
        if (! ::CORBA::is_nil (reader.in ()))
          {
            ::CORBA::Object_var cmp = reader->_get_component ();
            if (::CORBA::is_nil (cmp.in ()))
              {
                ACE_ERROR ((LM_ERROR, "ERROR: Receiver_exec_i::read_one - "
                                      "Unable to get component interface\n"));
                throw ::CORBA::INTERNAL ();
              }
            ::Shapes::CCM_DDS_Event_var conn =
              ::Shapes::CCM_DDS_Event::_narrow (cmp.in ());
            if (::CORBA::is_nil (conn.in ()))
              {
                ACE_ERROR ((LM_ERROR, "ERROR: Receiver_exec_i::read_one - "
                                      "Unable to narrow connector interface\n"));
                throw ::CORBA::INTERNAL ();
              }
            CORBA::String_var topic = conn->topic_name ();

            reader->read_one_last (shape_info, readinfo, ::DDS::HANDLE_NIL);
            ACE_Time_Value time;
            time <<= readinfo.source_timestamp;
            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("READ_ONE Read_Info ")
                      ACE_TEXT (" -> date = %#T\n"), &time));
            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("READ ON shape info : ")
                ACE_TEXT ("received shape_info <%C> for <%C> at X <%u> Y <%u> size <%u>\n"),
                topic.in (),
                shape_info.color.in (),
                shape_info.x,
                shape_info.y,
                shape_info.shapesize));
          }
        else
          {
            ACE_ERROR ((LM_ERROR, "Receiver_exec_i::read_one - "
                      "ERROR: reader seems to be nil.\n"));
          }
      }
    catch(const CCM_DDS::NonExistent& )
      {
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("ShapeType_Read_One: ")
                  ACE_TEXT ("no shape_info received\n")));
      }
  }

  void
  Receiver_exec_i::read_all (void)
  {
    ShapeTypeSeq shape_infos;
    ::CCM_DDS::ReadInfoSeq readinfoseq;
    ::Shapes::Reader_var reader =
      this->ciao_context_->get_connection_info_out_data ();
    if (! ::CORBA::is_nil (reader.in ()))
      {
        ::CORBA::Object_var cmp = reader->_get_component ();
        if (::CORBA::is_nil (cmp.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Receiver_exec_i::read_all - "
                                  "Unable to get component interface\n"));
            throw ::CORBA::INTERNAL ();
          }
        ::Shapes::CCM_DDS_Event_var conn =
          ::Shapes::CCM_DDS_Event::_narrow (cmp.in ());
        if (::CORBA::is_nil (conn.in ()))
          {
            ACE_ERROR ((LM_ERROR, "ERROR: Receiver_exec_i::read_all - "
                                  "Unable to narrow connector interface\n"));
            throw ::CORBA::INTERNAL ();
          }
        CORBA::String_var topic = conn->topic_name ();

        reader->read_all(shape_infos, readinfoseq);
        for(CORBA::ULong i = 0; i < readinfoseq.length(); ++i)
          {
            ACE_Time_Value time;
            time <<= readinfoseq[i].source_timestamp;
            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("READ_ALL ReadInfo ")
                ACE_TEXT ("-> UTC date = %#T\n"), &time));
          }
        for(CORBA::ULong i = 0; i < shape_infos.length(); ++i)
          {
            ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("READ_ALL Shape Info : ")
                ACE_TEXT ("received shape_info <%C> for <%C> at X <%u> Y <%u> size <%u>\n"),
                topic.in (),
                shape_infos[i].color.in (),
                shape_infos[i].x,
                shape_infos[i].y,
                shape_infos[i].shapesize));
          }
      }
    else
      {
        ACE_ERROR ((LM_ERROR, "Receiver_exec_i::read_all - "
                  "ERROR: reader seems to be nil.\n"));
      }
  }

  void
  Receiver_exec_i::get_one (void)
  {
    ShapeType_var shape_info;
    ::CCM_DDS::ReadInfo_var readinfo;

    try
      {
        ::Shapes::Getter_var getter =
          this->ciao_context_->get_connection_info_get_fresh_data ();
        if (! ::CORBA::is_nil (getter.in ()))
          {
            ::CORBA::Object_var cmp = getter->_get_component ();
            if (::CORBA::is_nil (cmp.in ()))
              {
                ACE_ERROR ((LM_ERROR, "ERROR: Receiver_exec_i::get_one - "
                                      "Unable to get component interface\n"));
                throw ::CORBA::INTERNAL ();
              }
            ::Shapes::CCM_DDS_Event_var conn =
              ::Shapes::CCM_DDS_Event::_narrow (cmp.in ());
            if (::CORBA::is_nil (conn.in ()))
              {
                ACE_ERROR ((LM_ERROR, "ERROR: Receiver_exec_i::get_one - "
                                      "Unable to narrow connector interface\n"));
                throw ::CORBA::INTERNAL ();
              }
            CORBA::String_var topic = conn->topic_name ();

            if (getter->get_one (shape_info.out (), readinfo.out ()))
              {
                ACE_Time_Value time;
                time <<= readinfo->source_timestamp;
                ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("GET_ONE ReadInfo -> ")
                                      ACE_TEXT ("date = %#T\n"), &time));
                ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("GET_ONE ShapeType : ")
                    ACE_TEXT ("received shape_info <%C> for <%C> at X <%u> Y <%u> size <%u>\n"),
                    topic.in (),
                    shape_info->color.in (),
                    shape_info->x,
                    shape_info->y,
                    shape_info->shapesize));
              }
            else
              {
                ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("GET_ONE No data available for <%C>\n"),
                        shape_info->color.in ()));
              }
          }
        else
          {
            ACE_ERROR ((LM_ERROR, "Receiver_exec_i::get_one - "
                      "ERROR: Getter seems nil\n"));
          }
      }
    catch(const CCM_DDS::NonExistent& )
      {
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("ShapeType_Read_One: no shape_info receieved\n")));
      }
  }

  // Component attributes and port operations.

  ::Shapes::CCM_Listener_ptr
  Receiver_exec_i::get_info_out_data_listener (void)
  {
    if ( ::CORBA::is_nil (this->ciao_info_out_data_listener_.in ()))
      {
        info_out_data_listener_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          info_out_data_listener_exec_i (
            this->ciao_context_.in ()),
            ::Shapes::CCM_Listener::_nil ());

          this->ciao_info_out_data_listener_ = tmp;
      }

    return
      ::Shapes::CCM_Listener::_duplicate (
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

  ::CCM_DDS::CCM_PortStatusListener_ptr
  Receiver_exec_i::get_info_get_status (void)
  {
    if ( ::CORBA::is_nil (this->ciao_info_get_status_.in ()))
      {
        info_get_status_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          info_get_status_exec_i (
            this->ciao_context_.in ()),
            ::CCM_DDS::CCM_PortStatusListener::_nil ());

          this->ciao_info_get_status_ = tmp;
      }

    return
      ::CCM_DDS::CCM_PortStatusListener::_duplicate (
        this->ciao_info_get_status_.in ());
  }

  ::CORBA::ULong
  Receiver_exec_i::rate (void)
  {
    return this->rate_;
  }

  void
  Receiver_exec_i::rate (
    const ::CORBA::ULong rate)
  {
    this->rate_ = rate;
  }

  ::CORBA::Boolean
  Receiver_exec_i::get_data (void)
  {
    return this->get_data_;
  }

  void
  Receiver_exec_i::get_data (
    const ::CORBA::Boolean get_data)
  {
    this->get_data_ = get_data;
  }

  ::CORBA::Boolean
  Receiver_exec_i::read_data (void)
  {
    return this->read_data_;
  }

  void
  Receiver_exec_i::read_data (
    const ::CORBA::Boolean read_data)
  {
    this->read_data_ = read_data;
  }

  ::CORBA::Boolean
  Receiver_exec_i::raw_listen (void)
  {
    return this->raw_listen_;
  }

  void
  Receiver_exec_i::raw_listen (
    const ::CORBA::Boolean raw_listen)
  {
    this->raw_listen_ = raw_listen;
  }

  // Operations from Components::SessionComponent.

  void
  Receiver_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::Shapes::CCM_Receiver_Context::_narrow (ctx);

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
    ::CCM_DDS::DataListenerControl_var lc =
      this->ciao_context_->get_connection_info_out_data_control ();

    if (::CORBA::is_nil (lc.in ()))
      {
        ACE_ERROR ((LM_INFO, ACE_TEXT ("Error:  Listener control receptacle is null!\n")));
        throw ::CORBA::INTERNAL ();
      }

    lc->mode (this->raw_listen_ ? ::CCM_DDS::ONE_BY_ONE : ::CCM_DDS::NOT_ENABLED);

    // calculate the interval time
    long const usec = 1000000 / this->rate_;
    if (this->reactor ()->schedule_timer (this->ticker_,
                                          0,
                                          ACE_Time_Value(0, usec),
                                          ACE_Time_Value(0, usec)) == -1)
      {
        ACE_ERROR ((LM_ERROR, "Unable to schedule Timer\n"));
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
    /* Your code here. */
  }

  extern "C" RECEIVER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_Shapes_Receiver_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      Receiver_exec_i);

    return retval;
  }
}
