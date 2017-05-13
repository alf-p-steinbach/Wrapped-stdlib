﻿#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/impl/windows_console_io/Wide_to_byte_converter.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <assert.h>     // assert

#include <stdlib/workarounds/impl/Size.hpp>                         // Size
#include <stdlib/workarounds/impl/windows_console_io/Codecvt.hpp>   // Codecvt, Codecvt_result
#include <stdlib/workarounds/impl/windows_console_io/constants.hpp> // ascii::del

namespace stdlib{ namespace impl{ namespace windows_console_io{
    using std::begin;
    using std::copy;
    using std::end;

    class Wide_to_byte_converter
    {
    public:
        static Size constexpr in_buf_size = general_buffer_size;

    private:
        Codecvt                 codecvt_{};
        Codecvt_state           conversion_state_{};    // mb_state
        wchar_t                 in_buf_[in_buf_size];
        Size                    n_buffered_ = 0;

        auto start_of_buffer()      -> wchar_t*         { return begin( in_buf_ ); }
        auto put_position()         -> wchar_t*         { return begin( in_buf_ ) + n_buffered_; }
        auto beyond_buffer()        -> wchar_t const*   { return end( in_buf_ ); }

    public:
        auto n_buffered() const -> Size { return n_buffered_; }
        auto available_space() const -> Size { return in_buf_size - n_buffered_; }

        void add( Size const n, wchar_t const* const chars )
        {
            assert( n <= available_space() );
            copy( chars, chars + n, put_position() );
            n_buffered_ += n;
        }

        auto convert_into( char* const result, Size const result_size )
            -> Size
        {
            wchar_t const*  p_next_in   = start_of_buffer();
            char*           p_next_out  = result;

            for( ;; )
            {
                auto const p_start_in = p_next_in;
                auto const p_start_out = p_next_out;
                auto const result_code = static_cast<Codecvt_result>( codecvt_.out(
                    conversion_state_,
                    p_start_in, put_position(), p_next_in,          // begin, end, beyond processed
                    p_start_out, result + result_size, p_next_out   // begin, end, beyond processed
                    ) );

                switch( result_code )
                {
                    case Codecvt::ok:
                    case Codecvt::partial:
                    case Codecvt::noconv:
                    {
                        copy<wchar_t const*>( p_next_in, put_position(), start_of_buffer() );
                        n_buffered_ = put_position() - p_next_in;
                        return p_next_out - result;
                    }

                    case Codecvt::error:
                    {
                        *p_next_out++ = ascii::del;
                        break;      // p_next_in points past the offending byte.
                    }

                    default:
                    {
                        assert(( "Should never get here.", false )); throw 0;
                        break;
                    }
                }
            }
        }
    };

}}}  // namespace stdlib::impl::windows_console_io