// -*- C++ -*-
// $Id: TypeRegistration_Test_Component_exec.cpp 94175 2011-06-10 11:22:03Z msmit $

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.0.2
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

#include "TypeRegistration_Test_Component_exec.h"
#include "tao/ORB_Core.h"
#include "ace/Reactor.h"

namespace CIAO_MLD_TypeRegistration_Test_CFTTestComponent_Impl
{
  /**
   * WriteTicker
   */
  WriteTicker::WriteTicker (CFTTestComponent_exec_i &callback)
    : callback_ (callback)
  {
  }

  int
  WriteTicker::handle_timeout (const ACE_Time_Value &, const void *)
  {
    // Notify the subscribers
    this->callback_.write_one ();
    return 0;
  }

  /**
   * Facet Executor Implementation Class: listener_data_listener_exec_i
   */

  listener_data_listener_exec_i::listener_data_listener_exec_i (
        ::MLD_TypeRegistration_Test::CCM_CFTTestComponent_Context_ptr ctx)
    : ciao_context_ (
        ::MLD_TypeRegistration_Test::CCM_CFTTestComponent_Context::_duplicate (ctx))
  {
  }

  listener_data_listener_exec_i::~listener_data_listener_exec_i (void)
  {
  }

  // Operations from ::MLDTypeRegistrationTestConn::Listener

  void
  listener_data_listener_exec_i::on_one_data (const ::MLDTypeRegistrationTest & datum,
  const ::CCM_DDS::ReadInfo & /* info */)
  {
    ACE_DEBUG ((LM_DEBUG, "listener_data_listener_exec_i::on_one_data: "
                            "key <%u>\n",
                            datum.key));
  }

  void
  listener_data_listener_exec_i::on_many_data (const ::MLDTypeRegistrationTestSeq & /* data */,
  const ::CCM_DDS::ReadInfoSeq & /* infos */)
  {
    /* Your code here. */
  }

  /**
   * Facet Executor Implementation Class: listener_status_exec_i
   */

  listener_status_exec_i::listener_status_exec_i (
        ::MLD_TypeRegistration_Test::CCM_CFTTestComponent_Context_ptr ctx)
    : ciao_context_ (
        ::MLD_TypeRegistration_Test::CCM_CFTTestComponent_Context::_duplicate (ctx))
  {
  }

  listener_status_exec_i::~listener_status_exec_i (void)
  {
  }

  // Operations from ::CCM_DDS::PortStatusListener

  void
  listener_status_exec_i::on_requested_deadline_missed (::DDS::DataReader_ptr /* the_reader */,
  const ::DDS::RequestedDeadlineMissedStatus & /* status */)
  {
    /* Your code here. */
  }

  void
  listener_status_exec_i::on_sample_lost (::DDS::DataReader_ptr /* the_reader */,
  const ::DDS::SampleLostStatus & /* status */)
  {
    /* Your code here. */
  }

  /**
   * Component Executor Implementation Class: CFTTestComponent_exec_i
   */

  CFTTestComponent_exec_i::CFTTestComponent_exec_i (void)
    : ticker_(0)
    , iterator(0)
  {
    ACE_NEW_THROW_EX (this->ticker_,
                      WriteTicker (*this),
                      ::CORBA::NO_MEMORY ());
  }

  CFTTestComponent_exec_i::~CFTTestComponent_exec_i (void)
  {
    delete this->ticker_;
  }

  // Supported operations and attributes.
  ACE_Reactor*
  CFTTestComponent_exec_i::reactor (void)
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
  CFTTestComponent_exec_i::write_one (void)
  {
    MLDTypeRegistrationTest new_key;
    new_key.key = ++this->iterator;

    MLDTypeRegistrationTestConn::Writer_var writer =
      this->ciao_context_->get_connection_writer_data ();
    if (::CORBA::is_nil (writer.in ()))
      {
        ACE_ERROR ((LM_ERROR, "CFTTestComponent_exec_i::write_one - "
                    "ERROR: Writer seems to be nil\n"));
        return;
      }
    try
      {
        writer->write_one (new_key, ::DDS::HANDLE_NIL);
      }
    catch (const CCM_DDS::InternalError& )
      {
        ACE_ERROR ((LM_ERROR, "CFTTestComponent_exec_i::write_one - "
                    "ERROR: caught InternalError exception while writing <%d> to DDS.\n",
                    this->iterator));
      }
    catch (const ::CORBA::Exception& )
      {
        ACE_ERROR ((LM_ERROR, "CFTTestComponent_exec_i::write_one - "
                    "ERROR: caught CORBA exception while writing <%d> to DDS.\n",
                    this->iterator));
      }
  }

  // Component attributes and port operations.

  ::MLDTypeRegistrationTestConn::CCM_Listener_ptr
  CFTTestComponent_exec_i::get_listener_data_listener (void)
  {
    if ( ::CORBA::is_nil (this->ciao_listener_data_listener_.in ()))
      {
        listener_data_listener_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          listener_data_listener_exec_i (
            this->ciao_context_.in ()),
            ::MLDTypeRegistrationTestConn::CCM_Listener::_nil ());

          this->ciao_listener_data_listener_ = tmp;
      }

    return
      ::MLDTypeRegistrationTestConn::CCM_Listener::_duplicate (
        this->ciao_listener_data_listener_.in ());
  }

  ::CCM_DDS::CCM_PortStatusListener_ptr
  CFTTestComponent_exec_i::get_listener_status (void)
  {
    if ( ::CORBA::is_nil (this->ciao_listener_status_.in ()))
      {
        listener_status_exec_i *tmp = 0;
        ACE_NEW_RETURN (
          tmp,
          listener_status_exec_i (
            this->ciao_context_.in ()),
            ::CCM_DDS::CCM_PortStatusListener::_nil ());

          this->ciao_listener_status_ = tmp;
      }

    return
      ::CCM_DDS::CCM_PortStatusListener::_duplicate (
        this->ciao_listener_status_.in ());
  }

  // Operations from Components::SessionComponent.

  void
  CFTTestComponent_exec_i::set_session_context (
    ::Components::SessionContext_ptr ctx)
  {
    this->ciao_context_ =
      ::MLD_TypeRegistration_Test::CCM_CFTTestComponent_Context::_narrow (ctx);

    if ( ::CORBA::is_nil (this->ciao_context_.in ()))
      {
        throw ::CORBA::INTERNAL ();
      }
  }

  void
  CFTTestComponent_exec_i::configuration_complete (void)
  {
    /* Your code here. */
  }

  void
  CFTTestComponent_exec_i::ccm_activate (void)
  {
    if (this->reactor ()->schedule_timer (
            this->ticker_,
            0,
            ACE_Time_Value (5, 50000),
            ACE_Time_Value (1, 0)) == -1)
      {
        ACE_ERROR ((LM_ERROR, ACE_TEXT ("Sender_exec_i::start : ")
                              ACE_TEXT ("Error scheduling timer")));
      }

    ::CCM_DDS::DataListenerControl_var dlc =
    this->ciao_context_->get_connection_listener_data_control();
    dlc->mode (::CCM_DDS::ONE_BY_ONE);
  }

  void
  CFTTestComponent_exec_i::ccm_passivate (void)
  {
    this->reactor ()->cancel_timer(this->ticker_);
  }

  void
  CFTTestComponent_exec_i::ccm_remove (void)
  {
    /* Your code here. */
  }

  extern "C" COMPONENT_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_MLD_TypeRegistration_Test_CFTTestComponent_Impl (void)
  {
    ::Components::EnterpriseComponent_ptr retval =
      ::Components::EnterpriseComponent::_nil ();

    ACE_NEW_NORETURN (
      retval,
      CFTTestComponent_exec_i);

    return retval;
  }
}
