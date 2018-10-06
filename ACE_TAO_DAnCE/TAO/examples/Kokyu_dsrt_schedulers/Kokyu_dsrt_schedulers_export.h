
// -*- C++ -*-
// $Id: Kokyu_dsrt_schedulers_export.h 52574 2003-10-08 13:26:32Z venkita $
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl -s Kokyu_DSRT_Schedulers
// ------------------------------
#ifndef KOKYU_DSRT_SCHEDULERS_EXPORT_H
#define KOKYU_DSRT_SCHEDULERS_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (KOKYU_DSRT_SCHEDULERS_HAS_DLL)
#  define KOKYU_DSRT_SCHEDULERS_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && KOKYU_DSRT_SCHEDULERS_HAS_DLL */

#if !defined (KOKYU_DSRT_SCHEDULERS_HAS_DLL)
#  define KOKYU_DSRT_SCHEDULERS_HAS_DLL 1
#endif /* ! KOKYU_DSRT_SCHEDULERS_HAS_DLL */

#if defined (KOKYU_DSRT_SCHEDULERS_HAS_DLL) && (KOKYU_DSRT_SCHEDULERS_HAS_DLL == 1)
#  if defined (KOKYU_DSRT_SCHEDULERS_BUILD_DLL)
#    define Kokyu_DSRT_Schedulers_Export ACE_Proper_Export_Flag
#    define KOKYU_DSRT_SCHEDULERS_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define KOKYU_DSRT_SCHEDULERS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* KOKYU_DSRT_SCHEDULERS_BUILD_DLL */
#    define Kokyu_DSRT_Schedulers_Export ACE_Proper_Import_Flag
#    define KOKYU_DSRT_SCHEDULERS_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define KOKYU_DSRT_SCHEDULERS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* KOKYU_DSRT_SCHEDULERS_BUILD_DLL */
#else /* KOKYU_DSRT_SCHEDULERS_HAS_DLL == 1 */
#  define Kokyu_DSRT_Schedulers_Export
#  define KOKYU_DSRT_SCHEDULERS_SINGLETON_DECLARATION(T)
#  define KOKYU_DSRT_SCHEDULERS_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* KOKYU_DSRT_SCHEDULERS_HAS_DLL == 1 */

// Set KOKYU_DSRT_SCHEDULERS_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (KOKYU_DSRT_SCHEDULERS_NTRACE)
#  if (ACE_NTRACE == 1)
#    define KOKYU_DSRT_SCHEDULERS_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define KOKYU_DSRT_SCHEDULERS_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !KOKYU_DSRT_SCHEDULERS_NTRACE */

#if (KOKYU_DSRT_SCHEDULERS_NTRACE == 1)
#  define KOKYU_DSRT_SCHEDULERS_TRACE(X)
#else /* (KOKYU_DSRT_SCHEDULERS_NTRACE == 1) */
#  define KOKYU_DSRT_SCHEDULERS_TRACE(X) ACE_TRACE_IMPL(X)
#endif /* (KOKYU_DSRT_SCHEDULERS_NTRACE == 1) */

#endif /* KOKYU_DSRT_SCHEDULERS_EXPORT_H */

// End of auto generated file.
