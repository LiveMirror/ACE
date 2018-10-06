/**
 * @author Johnny Willemsen (jwillemsen@remedy.nl)
 *
 * $Id: UserDataQosPolicy.h 95809 2012-06-03 17:56:00Z johnnyw $
 *
 * Wrapper facade for NDDS.
 */

#ifndef DDS4CCM_USERDATAQOSPOLICY_H
#define DDS4CCM_USERDATAQOSPOLICY_H

#include "OctetSeq.h"
#include "dds4ccm/impl/dds4ccm_conf.h"

inline void
operator<<= (::DDS::UserDataQosPolicy &ddsqos, const ::DDS_UserDataQosPolicy & qos)
{
  ddsqos.value <<= qos.value;
}

inline void
operator<<= (::DDS_UserDataQosPolicy &ddsqos, const ::DDS::UserDataQosPolicy & qos)
{
  ddsqos.value <<= qos.value;
}

#endif /* DDS4CCM_USERDATAQOSPOLICY_H */
