#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/filesystem.hpp>
//
// std::path class and supporting functions.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/version.hpp>         // STDLIB_COMPILER_SUPPORTS_CPP17
#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#if STDLIB_COMPILER_SUPPORTS_CPP17
#   include <filesystem>
#elif STDLIB_USE_EXPERIMENTAL_CPP17
#   include <experimental/filesystem>
#else
#   ifdef _MSC_VER
#       error "<filesystem> appears not available (try option `/std:c++latest`?)."
#   else
#       error "<filesystem> appears not available (try define STDLIB_USE_EXPERIMENTAL_CPP17?)."
#   endif
#endif

#ifdef STDLIB_HOIST_UP_FILESYSTEM_NAMESPACE
    namespace std {
        namespace filesystem = experimental::filesystem;
    }  // namespace std;
#endif
