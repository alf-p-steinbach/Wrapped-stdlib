#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/filesystem.hpp>
//
// std::path class and supporting functions.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/version.hpp>             // STDLIB_COMPILER_SUPPORTS_CPP17
#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/extension/compatible_path.hpp>     // For stdlib::compatible_string function
#include <stdlib/extension/utf8_conversion.hpp>     // For STDLIB_FIX_GCC_U8PATH

#if STDLIB_USE_EXPERIMENTAL_CPP17
#   include <experimental/filesystem>
#elif STDLIB_COMPILER_SUPPORTS_CPP17
#   include <filesystem>
#else
#   ifdef _MSC_VER
#       error "<filesystem> appears not available (try option `/std:c++latest`?)."
#   else
#       error "<filesystem> appears not available (try define STDLIB_USE_EXPERIMENTAL_CPP17?)."
#   endif
#endif

#ifdef STDLIB_HOIST_UP_FILESYSTEM_NAMESPACE
    namespace std {
        namespace filesystem {
            using namespace experimental::filesystem;
        }  // namespace filesystem
    }  // namespace std;
#endif

#if defined( STDLIB_FIX_GCC_U8PATH ) && defined( __GNUC__ ) && defined( _WIN32 )
    namespace std{ namespace filesystem {
        inline auto u8path( string const& source  )
            -> path
        { return path{ ::stdlib::wide_from_utf8( source ) }; }

        inline auto u8path( char const* const source  )
            -> path
        { return u8path( string( source ) ); }
    }}  // std::namespace filesystem
#endif

namespace stdlib{
    namespace fs = ::std::filesystem;

    // Best effort compatible-with-runtime-library path.
    // In Windows the result is a short path, if that’s available for the file system,
    // and unless the long path is all ASCII, in which case it’s just returned as-is.

    inline auto path_string( ref_<const fs::path> path )
        -> string
    { return compatible_path( path.u8string() ); }

}  // namespace stdlib

#include <stdlib/all/non_io_fixes.hpp>
