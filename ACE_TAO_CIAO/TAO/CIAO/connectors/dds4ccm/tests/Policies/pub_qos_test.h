// $Id: pub_qos_test.h 92430 2010-10-30 07:02:24Z msmit $

#ifndef PUBLISHER_QOS_TEST_H_
#define PUBLISHER_QOS_TEST_H_

#include "dds4ccm/idl/dds_rtf2_dcpsC.h"
#include "ndds/ndds_cpp.h"
#include "dds4ccm/impl/ndds/convertors/PublisherQos.h"

class PublisherPolicyTest
{
public:
  PublisherPolicyTest ();

  int run ();
};

#endif /* PUBLISHER_QOS_TEST_H_ */
