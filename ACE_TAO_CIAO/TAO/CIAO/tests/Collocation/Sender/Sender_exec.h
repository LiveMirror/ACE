// -*- C++ -*-
// $Id: Sender_exec.h 94919 2011-11-01 11:00:10Z mcorino $

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
#ifndef CIAO_SENDER_EXEC_SV8KRD_H_
#define CIAO_SENDER_EXEC_SV8KRD_H_

#include /**/ "ace/pre.h"

#include "SenderEC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include /**/ "Sender_exec_export.h"
#include "tao/LocalObject.h"
#include "tao/ORB_Core.h"
#include "ace/Reactor.h"


#include <map>

namespace CIAO_Sender_Impl
{
  //Forward declaration
   class Sender_exec_i;

  /**
  * Provider Executor Implementation Class: hello_exec_i
  */

  class hello_exec_i
    : public virtual ::CCM_Hello,
      public virtual ::CORBA::LocalObject
  {
  public:
    hello_exec_i (::CCM_Sender_Context_ptr ctx);
    virtual ~hello_exec_i (void);

    /** @name Operations and attributes from Hello */
    //@{
    virtual
    void set_point (const pointer_id & , const char *);

      //@}

  private:
    ::CCM_Sender_Context_var ciao_context_;
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

    /** @name Supported operations and attributes. */
    //@{

    //@}

    /** @name Component attributes and port operations. */
    //@{

    virtual ::CCM_Hello_ptr
      get_hello (void);
     //@}

    /** @name Operations from Components::SessionComponent. */
    //@{
    virtual void set_session_context (::Components::SessionContext_ptr ctx);
    virtual void configuration_complete (void);
    virtual void ccm_activate (void);
    virtual void ccm_passivate (void);
    virtual void ccm_remove (void);
    //@}

    /** @name User defined public operations. */
    //@{
    //@}

  private:
    ::CCM_Sender_Context_var ciao_context_;

    /** @name Component attributes. */
    //@{
     ::CCM_Hello_var ciao_hello_;

    //@}

    /** @name User defined members. */
    //@{
    //@}
  };

  extern "C" SENDER_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_Sender_Impl (void);
}

#include /**/ "ace/post.h"

#endif /* ifndef */
