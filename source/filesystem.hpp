#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/filesystem.hpp>
//
// std::path class and supporting functions.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/version.hpp>             // STDLIB_COMPILER_SUPPORTS_CPP17
#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/extension/char_path.hpp>    // For stdlib::char_path(path)
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

namespace stdlib{ namespace ext{
    namespace fs = ::std::filesystem;

    // Best effort compatible-with-runtime-library path.

    inline auto char_path( ref_<const fs::path> path )
        -> string
    { return char_path( path.native() ); }

    inline auto char_path_or_x( ref_<const fs::path> path )
        -> string
    { return char_path_or_x( path.native() ); }

}}  // namespace stdlib::ext

#include <stdlib/all/non_io_fixes.hpp>
