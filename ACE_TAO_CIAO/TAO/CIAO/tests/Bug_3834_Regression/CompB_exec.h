// -*- C++ -*-
// $Id: CompB_exec.h 91744 2010-09-13 18:27:20Z johnnyw $

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v1.7.6
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

// TAO_IDL - Generated from
// be/be_codegen.cpp:1212

#ifndef CIAO_COMPB_EXEC_H_
#define CIAO_COMPB_EXEC_H_


#include "CompBEC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include /**/ "CompB_exec_export.h"
#include "tao/LocalObject.h"


namespace CIAO_CompB_Impl
{
  class COMPB_EXEC_Export CompB_exec_i
    : public virtual CompB_Exec,
      public virtual ::CORBA::LocalObject
  {
  public:
    CompB_exec_i (void);
    virtual ~CompB_exec_i (void);

    //@{
    /** Supported operations and attributes. */

    //@}

    //@{
    /** Component attributes and port operations. */

    //@}

    //@{
    /** Operations from Components::SessionComponent. */

    virtual void
    set_session_context (
      ::Components::SessionContext_ptr ctx);

    virtual void configuration_complete (void);

    virtual void ccm_activate (void);
    virtual void ccm_passivate (void);
    virtual void ccm_remove (void);
    //@}


  private:
    ::CCM_CompB_Context_var context_;
  };

  extern "C" COMPB_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_CompB_Impl (void);
}

#endif /* ifndef */

