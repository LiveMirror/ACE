
// -*- C++ -*-
// $Id: Compiler_Features_22_DLL_Export.h 97266 2013-08-09 14:28:12Z johnnyw $
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl COMPILER_FEATURES_22_DLL
// ------------------------------
#ifndef COMPILER_FEATURES_22_DLL_EXPORT_H
#define COMPILER_FEATURES_22_DLL_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (COMPILER_FEATURES_22_DLL_HAS_DLL)
#  define COMPILER_FEATURES_22_DLL_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && ! TEST_HAS_DLL */

#if !defined (COMPILER_FEATURES_22_DLL_HAS_DLL)
#  define COMPILER_FEATURES_22_DLL_HAS_DLL 1
#endif /* ! COMPILER_FEATURES_22_DLL_HAS_DLL */

#if defined (COMPILER_FEATURES_22_DLL_HAS_DLL) && (COMPILER_FEATURES_22_DLL_HAS_DLL == 1)
#  if defined (COMPILER_FEATURES_22_DLL_BUILD_DLL)
#    define COMPILER_FEATURES_22_DLL_Export ACE_Proper_Export_Flag
#    define COMPILER_FEATURES_22_DLL_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define COMPILER_FEATURES_22_DLL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* COMPILER_FEATURES_22_DLL_BUILD_DLL */
#    define COMPILER_FEATURES_22_DLL_Export ACE_Proper_Import_Flag
#    define COMPILER_FEATURES_22_DLL_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define COMPILER_FEATURES_22_DLL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* COMPILER_FEATURES_22_DLL_BUILD_DLL */
#else /* COMPILER_FEATURES_22_DLL_HAS_DLL == 1 */
#  define COMPILER_FEATURES_22_DLL_Export
#  define COMPILER_FEATURES_22_DLL_SINGLETON_DECLARATION(T)
#  define COMPILER_FEATURES_22_DLL_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* COMPILER_FEATURES_22_DLL_HAS_DLL == 1 */

// Set COMPILER_FEATURES_22_DLL_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (COMPILER_FEATURES_22_DLL_NTRACE)
#  if (ACE_NTRACE == 1)
#    define COMPILER_FEATURES_22_DLL_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define COMPILER_FEATURES_22_DLL_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !COMPILER_FEATURES_22_DLL_NTRACE */

#if (COMPILER_FEATURES_22_DLL_NTRACE == 1)
#  define COMPILER_FEATURES_22_DLL_TRACE(X)
#else /* (COMPILER_FEATURES_22_DLL_NTRACE == 1) */
#  define COMPILER_FEATURES_22_DLL_TRACE(X) ACE_TRACE_IMPL(X)
#endif /* (COMPILER_FEATURES_22_DLL_NTRACE == 1) */

#endif /* COMPILER_FEATURES_22_DLL_EXPORT_H */

// End of auto generated file.
