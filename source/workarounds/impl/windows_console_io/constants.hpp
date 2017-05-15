#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/impl/windows_console_io/constants.hpp>
//
// Conversion UCS2 (in console) ↔ UTF-8 (in program), with ASCII `del` as
// replacement character on decoding error.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/workarounds/impl/Size.hpp>

namespace stdlib{ namespace impl{ namespace windows_console_io{

    // ASCII DEL, code 127, “delete”, is here used as a replacement for encoding
    // errors or unrepresentable code point.
    //
    // ASCII has a character dedicated to the purpose: SUB “substitute”, code 27, ^Z.
    // But in Windows ^Z is used as an EOF marker for text strems. So ^Z as
    // replacement is not usable in Windows, i.e. it's not a general solution.
    //
    // Unicode, an extension of ASCII, also has its own character dedicated to the
    // purpose, namely code U+FFFD “replacement character”. It translates to at
    // least two UTF-8 bytes so it's not trivial to check for. And it can't be
    // represented in simple single byte encodings such as codepage 437, so it's not
    // usable in single byte encodings, i.e. it's not a general solution.

    namespace ascii {
        char const      del                     = '\x7F';
    }  // namespace ascii

    //char const      error_byte_char             = ascii::del;
    //wchar_t const   error_wide_char             = ascii::del;
    //int const       max_bytes_per_utf8_char     = 4;

    Size const  general_buffer_size = 2048;     // Should be large enough for efficiency.

}}}  // namespace stdlib::impl::windows_console_io
