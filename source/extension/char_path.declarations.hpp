#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/char_path.declarations.hpp>
//
// Best effort compatible-with-runtime-library path.
// In Windows some result path items can be alternate short names, if that’s
// available for the file system, unless the long path is all ASCII, in which
// case it’s just returned as-is.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/extension/type_builders.hpp>       // stdlib::(ref_)
#include <string>
#include <utility>          // std::move

namespace stdlib{ namespace ext{
    using std::move;
    using std::string;
    using std::wstring;

    inline auto char_path_with_substitution( const bool substitution_allowed, wstring long_path )
        -> string;

    inline auto char_path_with_substitution( const bool substitution_allowed, string long_utf8_path )
        -> string;

    inline auto char_path( wstring long_path )
        -> string
    { return char_path_with_substitution( true, move( long_path ) ); }

    inline auto char_path( string long_utf8_path )
        -> string
    { return char_path_with_substitution( true, move( long_utf8_path ) ); }

    inline auto char_path_or_x( wstring long_path )
        -> string
    { return char_path_with_substitution( false, move( long_path ) ); }

    inline auto char_path_or_x( string long_utf8_path )
        -> string
    { return char_path_with_substitution( false, move( long_utf8_path ) ); }

}}  // namespace stdlib::ext
