#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/impl/windows_console_io/constants.hpp>
//
// Conversion UCS2 (in console) ↔ UTF-8 (in program), with ASCII `del` as
// replacement character on decoding error.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/workarounds/impl/Size.hpp>

namespace stdlib{ namespace impl{ namespace windows_console_io{

    namespace ascii {
        char const      del                     = '\x7F';
    }  // namespace ascii

    //char const      error_byte_char             = ascii::del;
    //wchar_t const   error_wide_char             = ascii::del;
    //int const       max_bytes_per_utf8_char     = 4;

    Size const  general_buffer_size = 2048;     // Should be large enough for efficiency.

}}}  // namespace stdlib::impl::windows_console_io
