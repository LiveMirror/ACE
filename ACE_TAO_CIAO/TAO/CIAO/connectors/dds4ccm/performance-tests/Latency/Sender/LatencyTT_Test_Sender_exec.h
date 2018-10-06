// -*- C++ -*-
// $Id: LatencyTT_Test_Sender_exec.h 93359 2011-02-11 11:33:12Z mcorino $

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
#ifndef CIAO_LATENCYTT_TEST_SENDER_EXEC_CAXIAK_H_
#define CIAO_LATENCYTT_TEST_SENDER_EXEC_CAXIAK_H_

#include /**/ "ace/pre.h"

#include "LatencyTT_Test_SenderEC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include /**/ "Sender_exec_export.h"
#include "tao/LocalObject.h"

namespace CIAO_LatencyTT_Test_Sender_Impl
{
  typedef ACE_Atomic_Op <TAO_SYNCH_MUTEX, CORBA::Long > Atomic_Long;
  typedef ACE_Atomic_Op <TAO_SYNCH_MUTEX, CORBA::Boolean> Atomic_Boolean;

  class Sender_exec_i;

  /**
   * Write action generator
   */

  class WriteTicker :
    public ACE_Event_Handler
  {
  public:
    WriteTicker (Sender_exec_i &callback);
    int handle_timeout (const ACE_Time_Value &, const void *);
  private:
    Sender_exec_i &callback_;
  };

  /**
   * Provider Executor Implementation Class: ping_listen_data_listener_exec_i
   */

  class ping_listen_data_listener_exec_i
    : public virtual ::LatencyTT_Test::LatencyTTTestConn::CCM_Listener,
      public virtual ::CORBA::LocalObject
  {
  public:
    ping_listen_data_listener_exec_i (
      ::LatencyTT_Test::CCM_Sender_Context_ptr ctx,
      Sender_exec_i &callback);
    virtual ~ping_listen_data_listener_exec_i (void);

    //@{
    /** Operations and attributes from LatencyTT_Test::LatencyTTTestConn::Listener. */

    virtual
    void on_one_data (const ::LatencyTTTest & datum,
    const ::CCM_DDS::ReadInfo & info);

    virtual
    void on_many_data (const ::LatencyTTTestSeq & data,
    const ::CCM_DDS::ReadInfoSeq & infos);
    //@}

  private:
    ::LatencyTT_Test::CCM_Sender_Context_var ciao_context_;
    Sender_exec_i &callback_;
  };

  /**
   * Provider Executor Implementation Class: connector_status_exec_i
   */

  class connector_status_exec_i
    : public virtual ::CCM_DDS::CCM_ConnectorStatusListener,
      public virtual ::CORBA::LocalObject
  {
  public:
    connector_status_exec_i (
      ::LatencyTT_Test::CCM_Sender_Context_ptr ctx,
      Sender_exec_i &callback,
      Atomic_Boolean &matched,
      int number_of_subscribers,
      Atomic_Long &unexpected_count);
    virtual ~connector_status_exec_i (void);

    //@{
    /** Operations and attributes from CCM_DDS::ConnectorStatusListener. */

    virtual
    void on_inconsistent_topic (::DDS::Topic_ptr the_topic,
    const ::DDS::InconsistentTopicStatus & status);

    virtual
    void on_requested_incompatible_qos (::DDS::DataReader_ptr the_reader,
    const ::DDS::RequestedIncompatibleQosStatus & status);

    virtual
    void on_sample_rejected (::DDS::DataReader_ptr the_reader,
    const ::DDS::SampleRejectedStatus & status);

    virtual
    void on_offered_deadline_missed (::DDS::DataWriter_ptr the_writer,
    const ::DDS::OfferedDeadlineMissedStatus & status);

    virtual
    void on_offered_incompatible_qos (::DDS::DataWriter_ptr the_writer,
    const ::DDS::OfferedIncompatibleQosStatus & status);

    virtual
    void on_unexpected_status (::DDS::Entity_ptr the_entity,
    ::DDS::StatusKind status_kind);
    //@}

  private:
    ::LatencyTT_Test::CCM_Sender_Context_var ciao_context_;
    Sender_exec_i &callback_;
    Atomic_Boolean &matched_;
    int number_of_subscribers_;
    Atomic_Long &unexpected_count_;
  };

  /**
   * Component Executor Implementation Class: Sender_exec_i
   */

  class Sender_exec_i
    : public virtual Sender_Exec,
      public virtual ::CORBA::LocalObject
  {
  public:
    Sender_exec_i (void);
    virtual ~Sender_exec_i (void);

    //@{
    /** Supported operations and attributes. */

    //@}

    //@{
    /** Component attributes and port operations. */

    virtual ::LatencyTT_Test::LatencyTTTestConn::CCM_Listener_ptr
    get_ping_listen_data_listener (void);

    virtual ::CCM_DDS::CCM_PortStatusListener_ptr
    get_ping_listen_status (void);

    virtual ::CCM_DDS::CCM_ConnectorStatusListener_ptr
    get_connector_status (void);

    virtual ::CORBA::ULong iterations (void);

    virtual void iterations (::CORBA::ULong iterations);

    virtual ::CORBA::UShort sleep (void);

    virtual void sleep (::CORBA::UShort sleep);

    virtual ::CORBA::UShort number_of_sub (void);

    virtual void number_of_sub (::CORBA::UShort number_of_sub);
    //@}

    //@{
    /** Operations from Components::SessionComponent. */
    virtual void set_session_context (::Components::SessionContext_ptr ctx);
    virtual void configuration_complete (void);
    virtual void ccm_activate (void);
    virtual void ccm_passivate (void);
    virtual void ccm_remove (void);
    //@}

    //@{
    /** User defined public operations. */
    void write_one (void);
    void read (LatencyTTTest & instance, ACE_UINT64 receive_time);
    void start (void);

    //@}

  private:
    ::LatencyTT_Test::CCM_Sender_Context_var ciao_context_;

    //@{
    /** Component attributes. */
    ::LatencyTT_Test::LatencyTTTestConn::CCM_Listener_var ciao_ping_listen_data_listener_;
    ::CCM_DDS::CCM_ConnectorStatusListener_var ciao_connector_status_;

    ::CORBA::ULong iterations_;

    ::CORBA::UShort sleep_;

    ::CORBA::UShort number_of_sub_;
    //@}

    //@{
    /** User defined members. */
    ::LatencyTT_Test::LatencyTTTestConn::Writer_var writer_;
    WriteTicker *ticker_;

    ::CORBA::UShort datalen_;
    ::CORBA::UShort datalen_idx_;
    ::CORBA::UShort nr_of_runs_;
    Atomic_Boolean matched_;
    ACE_UINT64 tv_total_;
    ACE_UINT64 tv_max_;
    ACE_UINT64 tv_min_;
    ::CORBA::UShort count_;
    ::CORBA::UShort number_of_msg_;
    Atomic_Boolean timer_;
    Atomic_Boolean received_;
    ::CORBA::Long seq_num_;
    ::CORBA::Double sigma_duration_squared_;
    ACE_UINT64 start_time_;
    ACE_UINT64 start_time_test_;
    ACE_UINT64 end_time_test_;

    LatencyTTTest test_topic_;
    ACE_UINT64* duration_times_;
    ::CORBA::Short* datalen_range_;
    ::CORBA::Long _clock_overhead_;
    Atomic_Long unexpected_count_;

    //@}

    //@{
    /** User defined private operations. */
    void stop (void);
    void calc_results (void);
    void reset_results (void);
    void init_values (void);
    void calculate_clock_overhead (void);
    void record_time (ACE_UINT64 receive_time);

    //@}

    /// Get the ACE_Reactor
    ACE_Reactor* reactor (void);
  };

  extern "C" SENDER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_LatencyTT_Test_Sender_Impl (void);
}

#include /**/ "ace/post.h"

#endif /* ifndef */
