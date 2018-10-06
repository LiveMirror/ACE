// $Id: entity_factory_qos_test.h 92430 2010-10-30 07:02:24Z msmit $

#ifndef ENTITY_FACTORY_QOS_TEST_H_
#define ENTITY_FACTORY_QOS_TEST_H_

#include "dds4ccm/idl/dds_rtf2_dcpsC.h"
#include "ndds/ndds_cpp.h"
#include "dds4ccm/impl/ndds/convertors/EntityFactoryQosPolicy.h"

class EntityFactoryPolicyTest
{
public:
  EntityFactoryPolicyTest ();

  static bool check (const ::DDS_EntityFactoryQosPolicy & dds_qos,
                     const ::DDS::EntityFactoryQosPolicy & qos);
};

#endif /* ENTITY_FACTORY_QOS_TEST_H_ */
