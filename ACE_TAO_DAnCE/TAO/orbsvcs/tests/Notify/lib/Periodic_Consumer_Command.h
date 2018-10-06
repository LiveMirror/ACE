/* -*- C++ -*- */
/**
 *  @file Periodic_Consumer_Command.h
 *
 *  $Id: Periodic_Consumer_Command.h 93657 2011-03-28 11:13:39Z johnnyw $
 *
 *  @author Pradeep Gore <pradeep@oomworks.com>
 */

#ifndef TAO_Notify_Tests_PERIODICCONSUMER_COMMAND_H
#define TAO_Notify_Tests_PERIODICCONSUMER_COMMAND_H
#include /**/ "ace/pre.h"

#include "notify_test_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/SString.h"
#include "orbsvcs/CosNotifyChannelAdminC.h"
#include "Command.h"

class TAO_Notify_Tests_Periodic_Consumer;

/**
 * @class TAO_Notify_Tests_Periodic_Consumer_Command
 *
 * @brief Options for Periodic Consumers.
 *
 */
class TAO_NOTIFY_TEST_Export TAO_Notify_Tests_Periodic_Consumer_Command : public TAO_Notify_Tests_Command
{
public:
  /// Constructor
  TAO_Notify_Tests_Periodic_Consumer_Command (void);

  /// Destructor
  ~TAO_Notify_Tests_Periodic_Consumer_Command ();

  /// Parse args and populate options.
  virtual void init (ACE_Arg_Shifter& arg_shifter);

  /// Execute the command.
  virtual void execute_i (void);

  /// Name of object
  virtual const char* get_name (void);
  static const char* name (void);

protected:
  ///= Data Members
#ifdef HPUX_11
   // Remove clash with /usr/include/machine/cpu.h and /usr/include/pa/cpu.h
#undef COMMAND
#endif
  enum COMMAND
  {
    CREATE,
    DESTROY,
    SET_QOS,
    SET_ADMIN,
    SUBSCRIPTION,
    DISCONNECT,
    DEACTIVATE,
    DUMP_STATE
  };

  /// My name.
  ACE_CString name_;

  /// QoS
  CosNotification::QoSProperties qos_;

  // Subscription change
  CosNotification::EventTypeSeq added_;
  CosNotification::EventTypeSeq removed_;

  ///= Methods
  // Retreive the consumer.
  TAO_Notify_Tests_Periodic_Consumer* consumer (void);

  ///= Handlers
  void handle_create (void);
  void handle_subscriptions (void);
  void handle_disconnect (void);
  void handle_deactivate (void);
  void handle_status (void);
  void handle_set_qos (void);
};

#include /**/ "ace/post.h"
#endif /* TAO_Notify_Tests_PERIODICCONSUMER_COMMAND_H */
