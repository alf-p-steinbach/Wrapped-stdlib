#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/process_command_line.hpp>
//
// An UTF-8 alternative to just using the arguments of `main`.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>
#include <stdlib/all/non_io_fixes.hpp>

// For exposition only (each included header below includes this itself):
#include <stdlib/extension/process_command_line.declarations.hpp>

#if defined( STDLIB_USE_CUSTOM_COMMAND_LINE_IMPL )
#   include <stdlib/_impl/custom_process_command_line.hpp>  // Last fallback.
#elif defined( _WIN32 )
#   include <stdlib/_impl/windows_process_command_line.hpp>
#elif defined( __APPLE__ )
#   include "TargetConditionals.h"
#   if defined( TARGET_IPHONE_SIMULATOR )
#       error Process command line is not supported for Apple IPhone Simulator, sorry.
#   elif defined( TARGET_OS_IPHONE )
#       error Process command line is not supported for Apple IPhone, sorry.
#   elif defined( TARGET_OS_MAC )
#       error Process command line is not supported for your macOS, sorry.
#   else
#       error Process command line is not supported for this (unknown) Apple platform.
#   endif
#elif defined( __linux__ )
#   include <stdlib/_impl/linux_process_command_line.hpp>
#elif defined( __unix__ ) // all unices not caught above
#   error Process command line is not supported for non-Linux Unix, sorry.
#elif defined( _POSIX_VERSION )
#   error Process command line is not supported for general Posix, sorry.
#else
#   error Unknown operating system / platform.
#endif
