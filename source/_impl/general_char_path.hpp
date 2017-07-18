#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/_impl/general_ascii_path.hpp>
//
// Best effort compatible-with-runtime-library path.
// In Windows some result path items can be alternate short names, if that’s
// available for the file system, unless the long path is all ASCII, in which
// case it’s just returned as-is.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/extension/char_path.declarations.hpp>
#include <stdlib/extension/utf8_conversion.hpp>

#include <string>

namespace stdlib{
    using std::string;
    using std::wstring;

    inline auto char_path_with_substitution( const bool substitution_allowed, wstring long_path )
        -> string
    { (void) substitution_allowed; return utf8_from( long_path ); }

    inline auto char_path_with_substitution( const bool substitution_allowed, string long_utf8_path )
        -> string
    { (void) substitution_allowed; return long_utf8_path; }

}  // namespace stdlib
