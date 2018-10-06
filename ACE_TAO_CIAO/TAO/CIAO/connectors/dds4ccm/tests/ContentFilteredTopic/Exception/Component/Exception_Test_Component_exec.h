// -*- C++ -*-
// $Id: Exception_Test_Component_exec.h 90522 2010-06-10 11:38:10Z msmit $

#ifndef CIAO_COMPONENT_EXEC_H_
#define CIAO_COMPONENT_EXEC_H_

#include "Exception_Test_ComponentEC.h"

#include /**/ "Component_exec_export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "tao/LocalObject.h"

namespace CIAO_CFT_Exception_Test_CFTTestComponent_Impl
{
  //============================================================
  // Component_exec_i
  //============================================================
  class COMPONENT_EXEC_Export Component_exec_i
    : public virtual CFTTestComponent_Exec,
      public virtual ::CORBA::LocalObject
  {
  public:
    Component_exec_i (void);
    virtual ~Component_exec_i (void);

    // Operations from Components::SessionComponent.
    virtual void
    set_session_context (
      ::Components::SessionContext_ptr ctx);

    virtual ::CCM_DDS::CCM_PortStatusListener_ptr
    get_getter_status(void);

    virtual void configuration_complete (void);

    virtual void ccm_activate (void);
    virtual void ccm_passivate (void);
    virtual void ccm_remove (void);

  private:
    ::CFT_Exception_Test::CCM_CFTTestComponent_Context_var context_;
    ::CCM_DDS::ContentFilterSetting_var filter_config_;

    void
    test_set_query_parameters ();
  };

  extern "C" COMPONENT_EXEC_Export ::Components::EnterpriseComponent_ptr
  create_CFTTest_Component_Impl (void);
}

#endif /* ifndef */

