// -*- C++ -*-
//
// $Id: CSD_TP_Servant_State.inl 69182 2005-11-03 17:38:46Z ossama $

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
TAO::CSD::TP_Servant_State::TP_Servant_State()
  : busy_flag_(false)
{
}


ACE_INLINE
bool
TAO::CSD::TP_Servant_State::busy_flag() const
{
  return this->busy_flag_;
}


ACE_INLINE
void
TAO::CSD::TP_Servant_State::busy_flag(bool new_value)
{
  this->busy_flag_ = new_value;
}

TAO_END_VERSIONED_NAMESPACE_DECL
