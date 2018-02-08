// Source encoding: utf-8 with BOM ∩
#pragma once

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <algorithm>        // std::(min)
#include <string>           // std::(string, wstring)

#include <stdlib/_impl/converter_buffer_size.hpp>
#include <stdlib/extension/Streaming_byte_to_wide_converter.hpp>
#include <stdlib/extension/Streaming_wide_to_byte_converter.hpp>
#include <stdlib/extension/Size.hpp>                    // Size, Index
#include <stdlib/fix/msvc_named_boolean_operators.hpp>  // or

namespace stdlib{ namespace ext{
    using std::min;
    using std::string;
    using std::wstring;

    inline auto utf8_from( const wstring& s )
        -> string
    {
        string                              result;
        Streaming_wide_to_byte_converter    converter;

        const Size n = s.length();
        for( Index read_pos = 0; read_pos < n or converter.n_buffered() > 0; )
        {
            char out_buffer[stdlib::impl::converter_buffer_size];
            const Size max_n_bytes = array_size( out_buffer );

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
        wstring                             result;
        Streaming_byte_to_wide_converter    converter;

        const Size n = s.length();
        for( Index read_pos = 0; read_pos < n or converter.n_buffered() > 0; )
        {
            wchar_t out_buffer[stdlib::impl::converter_buffer_size];
            const Size max_n_wchars = array_size( out_buffer );

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
}}  // namespace stdlib::ext
