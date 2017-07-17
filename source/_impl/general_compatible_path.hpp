#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/_impl/general_compatible_path.hpp>
//
// Best effort compatible-with-runtime-library path.
// In Windows the result is a short path, if that’s available for the file system,
// and unless the long path is all ASCII, in which case it’s just returned as-is.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/extension/type_builders.hpp>       // stdlib::(ref_)
#include <string>

namespace stdlib{
    using std::string;
    using std::wstring;

    inline auto compatible_path( ref_<const wstring> long_path )
        -> wstring
    { return long_path; }

    inline auto compatible_path( ref_<const string> long_utf8_path )
        -> string
    { return long_utf8_path; }

}  // namespace stdlib
