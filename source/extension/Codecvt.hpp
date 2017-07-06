#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/Codecvt.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <codecvt>                              // std::codecvt_utf8
#include <stdlib/extension/Byte_order.hpp>      // stdlib::system_byte_order()

namespace stdlib{
    using std::codecvt_mode;
    using std::codecvt_utf8_utf16;
    using std::little_endian;       // A value of bits enumeration std::codecvt_enum.

    using Codecvt           = codecvt_utf8_utf16<
        wchar_t,
        0x10ffff,           // Max value of UTF-16 encoding, i.e. highest code point.
        (system_byte_order() == Byte_order::little_endian? little_endian : codecvt_mode{})
        >;
    using Codecvt_result    = decltype( Codecvt::ok );      // enum
    using Codecvt_state     = Codecvt::state_type;          // enum

}  // namespace stdlib
