
// -*- C++ -*-
// $Id: Locality_Manager_Impl_Export.h 90214 2010-05-21 13:59:45Z wotte $
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl Locality_Manager_Impl
// ------------------------------
#ifndef LOCALITY_MANAGER_IMPL_EXPORT_H
#define LOCALITY_MANAGER_IMPL_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (LOCALITY_MANAGER_IMPL_HAS_DLL)
#  define LOCALITY_MANAGER_IMPL_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && LOCALITY_MANAGER_IMPL_HAS_DLL */

#if !defined (LOCALITY_MANAGER_IMPL_HAS_DLL)
#  define LOCALITY_MANAGER_IMPL_HAS_DLL 1
#endif /* ! LOCALITY_MANAGER_IMPL_HAS_DLL */

#if defined (LOCALITY_MANAGER_IMPL_HAS_DLL) && (LOCALITY_MANAGER_IMPL_HAS_DLL == 1)
#  if defined (LOCALITY_MANAGER_IMPL_BUILD_DLL)
#    define Locality_Manager_Impl_Export ACE_Proper_Export_Flag
#    define LOCALITY_MANAGER_IMPL_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define LOCALITY_MANAGER_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* LOCALITY_MANAGER_IMPL_BUILD_DLL */
#    define Locality_Manager_Impl_Export ACE_Proper_Import_Flag
#    define LOCALITY_MANAGER_IMPL_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define LOCALITY_MANAGER_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* LOCALITY_MANAGER_IMPL_BUILD_DLL */
#else /* LOCALITY_MANAGER_IMPL_HAS_DLL == 1 */
#  define Locality_Manager_Impl_Export
#  define LOCALITY_MANAGER_IMPL_SINGLETON_DECLARATION(T)
#  define LOCALITY_MANAGER_IMPL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* LOCALITY_MANAGER_IMPL_HAS_DLL == 1 */

// Set LOCALITY_MANAGER_IMPL_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (LOCALITY_MANAGER_IMPL_NTRACE)
#  if (ACE_NTRACE == 1)
#    define LOCALITY_MANAGER_IMPL_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define LOCALITY_MANAGER_IMPL_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !LOCALITY_MANAGER_IMPL_NTRACE */

#if (LOCALITY_MANAGER_IMPL_NTRACE == 1)
#  define LOCALITY_MANAGER_IMPL_TRACE(X)
#else /* (LOCALITY_MANAGER_IMPL_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define LOCALITY_MANAGER_IMPL_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (LOCALITY_MANAGER_IMPL_NTRACE == 1) */

#endif /* LOCALITY_MANAGER_IMPL_EXPORT_H */

// End of auto generated file.
