// -*- C++ -*-
// $Id: HomeT_HomeC_exec.h 95319 2011-12-13 14:54:44Z mhengstmengel $

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.0.6
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
#ifndef CIAO_HOMET_HOMEC_EXEC_P2A1KH_H_
#define CIAO_HOMET_HOMEC_EXEC_P2A1KH_H_

#include /**/ "ace/pre.h"

#include "HomeT_HomeCEC.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include /**/ "HomeT_HomeC_exec_export.h"
#include "tao/LocalObject.h"

namespace CIAO_ConnComp_DDS_Event_Impl
{
  class HOMET_HOMEC_EXEC_Export ConnHome_exec_i
    : public virtual ConnHome_Exec,
      public virtual ::CORBA::LocalObject
  {
  public:
    ConnHome_exec_i (void);

    virtual ~ConnHome_exec_i (void);

    virtual ::Components::EnterpriseComponent_ptr
    new_ConnComp (void);

    // Implicit operations.

    virtual ::Components::EnterpriseComponent_ptr
    create (void);
  };

  extern "C" HOMET_HOMEC_EXEC_Export ::Components::HomeExecutorBase_ptr
  create_ConnHome_Impl (void);
}

#include /**/ "ace/post.h"

#endif /* ifndef */
