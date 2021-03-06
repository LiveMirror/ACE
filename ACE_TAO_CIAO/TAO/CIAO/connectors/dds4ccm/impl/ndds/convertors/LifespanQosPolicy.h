/**
 * @author Johnny Willemsen (jwillemsen@remedy.nl)
 *
 * $Id: LifespanQosPolicy.h 95809 2012-06-03 17:56:00Z johnnyw $
 *
 * Wrapper facade for NDDS.
 */

#ifndef DDS4CCM_LIFESPANQOSPOLICY_H
#define DDS4CCM_LIFESPANQOSPOLICY_H

#include "Duration_t.h"
#include "dds4ccm/impl/dds4ccm_conf.h"

inline void
operator<<= (::DDS::LifespanQosPolicy &ddsqos, const ::DDS_LifespanQosPolicy & qos)
{
  ddsqos.duration <<= qos.duration;
}

inline void
operator<<= (::DDS_LifespanQosPolicy &ddsqos, const ::DDS::LifespanQosPolicy & qos)
{
  ddsqos.duration <<= qos.duration;
}

#endif /* DDS4CCM_LIFESPANQOSPOLICY_H */
