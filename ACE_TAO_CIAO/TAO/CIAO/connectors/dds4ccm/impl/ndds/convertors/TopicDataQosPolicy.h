/**
 * @author Johnny Willemsen (jwillemsen@remedy.nl)
 *
 * $Id: TopicDataQosPolicy.h 95809 2012-06-03 17:56:00Z johnnyw $
 *
 * Wrapper facade for NDDS.
 */

#ifndef DDS4CCM_TOPICDATAQOSPOLICY_H
#define DDS4CCM_TOPICDATAQOSPOLICY_H

#include "OctetSeq.h"
#include "dds4ccm/impl/dds4ccm_conf.h"

inline void
operator<<= (::DDS::TopicDataQosPolicy &ddsqos, const ::DDS_TopicDataQosPolicy & qos)
{
  ddsqos.value <<= qos.value;
}

inline void
operator<<= (::DDS_TopicDataQosPolicy &ddsqos, const ::DDS::TopicDataQosPolicy & qos)
{
  ddsqos.value <<= qos.value;
}

#endif /* DDS4CCM_TOPICDATAQOSPOLICY_H */
