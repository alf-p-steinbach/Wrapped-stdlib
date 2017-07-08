#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/version.hpp>
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#ifndef STDLIB_COMPILER_SUPPORTS_CPP11
#   define STDLIB_COMPILER_SUPPORTS_CPP11 (__cplusplus >= 201103)
#endif

#ifndef STDLIB_COMPILER_SUPPORTS_CPP14
#   define STDLIB_COMPILER_SUPPORTS_CPP14 (__cplusplus >= 201402)
#endif

// With Visual C++ 2017 use `/std:c++latest` option to get C++17 lib support.
#if !defined( STDLIB_COMPILER_SUPPORTS_CPP17 ) && defined( _MSVC_LANG )
#   if _MSC_VER < 2000 && _MSVC_LANG > 201402
#       define STDLIB_COMPILER_SUPPORTS_CPP17       1
        // One must include ordinary <filesystem> but the impl is in namespace
        // "experimental", neither fish nor fowl; it's a special case.
#       define STDLIB_HOIST_UP_FILESYSTEM_NAMESPACE
#   endif
#endif

#ifndef STDLIB_COMPILER_SUPPORTS_CPP17
#   define STDLIB_COMPILER_SUPPORTS_CPP17 (__cplusplus > 201700)
#endif

#ifdef STDLIB_USE_EXPERIMENTAL_CPP17
#   define STDLIB_HOIST_UP_FILESYSTEM_NAMESPACE
#else
#   define STDLIB_USE_EXPERIMENTAL_CPP17    0
#endif

#define STDLIB_HAS_CPP17_FEATURES \
    (STDLIB_COMPILER_SUPPORTS_CPP17 || STDLIB_USE_EXPERIMENTAL_CPP17)

namespace stdlib{ namespace platform{
#ifdef _WIN32
    constexpr bool is_windows = true;
#else
    constexpr bool is_windows = false;
#endif
}}  // namespace stdlib::platform
