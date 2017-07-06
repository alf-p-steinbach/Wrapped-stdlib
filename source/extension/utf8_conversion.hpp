// Source encoding: utf-8 with BOM ∩
#pragma once

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/string.hpp>                    // std::(string, wstring)

#include <stdlib/extension/Byte_to_wide_converter.hpp>
#include <stdlib/extension/Wide_to_byte_converter.hpp>
#include <stdlib/extension/Size.hpp>

namespace cppx {
    using std::string;
    using std::wstring;
    using stdlib::Byte_to_wide_converter;
    using stdlib::Wide_to_byte_converter;
    using stdlib::Size;

    inline auto utf8_from( const wstring& s )
        -> string
    {
        string                  result;
        Wide_to_byte_converter  converter;

        const Size n = s.length();
        for( Size read_pos = 0; read_pos < n or converter.n_buffered() > 0; )
        {
            char out_buffer[1024];  // Or anything, modulo stack size.
            const Size max_n_bytes = sizeof( out_buffer );

            const Size n_available_wchars = n - read_pos;
            const Size max_n_wchars = min(
                n_available_wchars, converter.available_space()
                );

            converter.add( max_n_wchars, s.data() + read_pos );
            const Size n_bytes = converter.convert_into( out_buffer, max_n_bytes );
            result.append( out_buffer, n_bytes );

            read_pos += max_n_wchars;
        }
        return result;
    }

    inline auto wide_from_utf8( string const& s )
        -> wstring
    {
        wstring                 result;
        Byte_to_wide_converter  converter;

        const Size n = s.length();
        for( Size read_pos = 0; read_pos < n or converter.n_buffered() > 0; )
        {
            wchar_t out_buffer[1024];   // Or anything, modulo stack size.
            const Size max_n_wchars = sizeof( out_buffer )/sizeof( wchar_t );

            const Size n_available_bytes = n - read_pos;
            const Size max_n_bytes = min(
                n_available_bytes, converter.available_space()
                );

            converter.add( max_n_bytes, s.data() + read_pos );
            const Size n_wchars = converter.convert_into( out_buffer, max_n_wchars );
            result.append( out_buffer, n_wchars );

            read_pos += max_n_bytes;
        }
        return result;
    }
}  // namespace cppx
