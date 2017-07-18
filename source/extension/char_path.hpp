#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/char_path.hpp>
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

// For exposition only (each included header below includes this itself):
#include <stdlib/extension/char_path.declarations.hpp>

#ifdef _WIN32
#   include <stdlib/_impl/windows_char_path.hpp>
#else
#   include <stdlib/_impl/general_char_path.hpp>
#endif
