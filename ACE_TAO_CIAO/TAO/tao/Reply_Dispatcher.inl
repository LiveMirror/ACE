// -*- C++ -*-
//
// $Id: Reply_Dispatcher.inl 79705 2007-09-24 07:45:37Z johnnyw $


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE GIOP::LocateStatusType
TAO_Reply_Dispatcher::locate_reply_status (void) const
{
  return this->locate_reply_status_;
}

ACE_INLINE GIOP::ReplyStatusType
TAO_Reply_Dispatcher::reply_status (void) const
{
  return this->reply_status_;
}

TAO_END_VERSIONED_NAMESPACE_DECL
