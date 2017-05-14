﻿#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/impl/windows_console_io/Wide_console_input_buffer.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <algorithm>    // std::min
#include <array>        // std::array
#include <assert.h>     // assert
#include <stddef.h>     // ptrdiff_t
#include <cstddef>
#include <iterator>     // std::(begin, end)
#include <streambuf>    // std::basic_streambuf

#include <stdlib/workarounds/impl/windows_console_io/constants.hpp>                 // general_buffer_size
#include <stdlib/workarounds/impl/windows_console_io/Wide_to_byte_converter.hpp>    // Wide_to_byte_converter
#include <stdlib/workarounds/impl/windows_console_io/winapi.hpp>                    // winapi::*

namespace stdlib{ namespace impl{ namespace windows_console_io{
    using std::array;
    using std::basic_streambuf;
    using std::begin;
    using std::end;
    using std::min;

    class Utf8_line_input
    {
    private:
        static constexpr Size in_buffer_size = general_buffer_size;

        wchar_t                     in_buffer_[in_buffer_size];
        int                         read_pos_   = 0;
        int                         length_     = 0;
        Wide_to_byte_converter      converter_;

        auto n_available_chars() const { return length_ - read_pos_; }

        auto read_from_buffer( char* const out_buffer, Size const out_buffer_size )
            -> Size
        {
            if( read_pos_ == length_ and converter_.n_buffered() == 0 )
            {
                length_ = get_text_from_console( in_buffer_, in_buffer_size );
                read_pos_ = 0;
                if( length_ == 0 )
                {
                    return 0;
                }
            }

            Size const max_n_bytes = out_buffer_size;
            Size const max_n_wides = min( n_available_chars(), converter_.available_space() );

            converter_.add( max_n_wides, in_buffer_ + read_pos_ );
            read_pos_ += max_n_wides;
            return converter_.convert_into( out_buffer, max_n_bytes );
        }

    public:
        auto read( char* const out_buffer, Size const out_buffer_size )
            -> Size
        {
            Size n_bytes_read = 0;
            for( ;; )
            {
                Size const n_more_bytes = read_from_buffer(
                    out_buffer + n_bytes_read, out_buffer_size - n_bytes_read
                    );
                n_bytes_read += n_more_bytes;
                if( n_more_bytes == 0 or
                    n_bytes_read == out_buffer_size or
                    out_buffer[n_bytes_read - 1] == '\n' )
                {
                    return n_bytes_read;
                }
            }
        }
    };

    inline auto utf8_line_input()
        -> Utf8_line_input&
    {
        static Utf8_line_input the_line_input;
        return the_line_input;
    }

    class Byte_console_input_buffer
        : public basic_streambuf<char>
    {
    private:
        static constexpr Size buffer_size = general_buffer_size;
        using Base = basic_streambuf<char>;
        using Traits = traits_type;

        char    buffer_[buffer_size];

        Byte_console_input_buffer( Byte_console_input_buffer const& ) = delete;

        auto readbuf_start() const      -> char_type*       { return Base::eback(); }
        auto readbuf_beyond() const     -> char_type*       { return Base::egptr(); }

        auto read_position() const      -> char_type*       { return Base::gptr(); }
        void advance_read_position( int const n )           { Base::gbump( n ); }

    protected:
        auto pbackfail( int_type const ch )
            -> int_type
            override
        { (void) ch; return traits_type::eof(); }          // TODO:

        auto underflow()            // Called by uflow()
            -> int_type
            override
        {
            assert( read_position() == readbuf_beyond() );

            auto const p_start  = readbuf_start();
            Size const n        = utf8_line_input().read( p_start, buffer_size );

            Base::setg( p_start, p_start, p_start + n );
            return (n == 0? Traits::eof() : Traits::to_int_type( *read_position() ));
        }

    public:
        Byte_console_input_buffer()
        { Base::setg( buffer_, buffer_, buffer_ ); }
    };
}}}  // namespace stdlib::impl::windows_console_io
