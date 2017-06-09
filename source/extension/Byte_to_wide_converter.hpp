#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/extension/Byte_to_wide_converter.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <algorithm>    // std::copy
#include <assert.h>     // assert

#include <stdlib/extension/ascii.hpp>       // ascii::bad_char
#include <stdlib/extension/Codecvt.hpp>     // stdlib::(Codecvt, Codecvt_result)
#include <stdlib/extension/Size.hpp>        // stdlib::(Size, Index)
#include <stdlib/extension/impl/converter_buffer_size.hpp>

namespace stdlib{
    using std::begin;
    using std::copy;
    using std::end;

    class Byte_to_wide_converter
    {
    public:
        static Size constexpr in_buf_size = impl::converter_buffer_size;

    private:
        Codecvt                 codecvt_{};
        Codecvt_state           conversion_state_{};    // mb_state
        char                    in_buf_[in_buf_size];
        Size                    n_buffered_ = 0;

        auto start_of_buffer()      -> char*        { return begin( in_buf_ ); }
        auto put_position()         -> char*        { return begin( in_buf_ ) + n_buffered_; }
        auto beyond_buffer()        -> char const*  { return end( in_buf_ ); }

    public:
        auto n_buffered() const -> Size { return n_buffered_; }
        auto available_space() const -> Size { return in_buf_size - n_buffered_; }

        void add( Size const n, char const* const chars )
        {
            assert( n <= available_space() );
            copy( chars, chars + n, put_position() );
            n_buffered_ += n;
        }

        auto convert_into( wchar_t* const result, Size const result_size )
            -> Size
        {
            char const* p_next_in       = start_of_buffer();
            wchar_t*    p_next_out      = result;

            for( ;; )
            {
                auto const p_start_in = p_next_in;
                auto const p_start_out = p_next_out;
                auto const result_code = static_cast<Codecvt_result>( codecvt_.in(
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
                        copy<char const*>( p_next_in, put_position(), start_of_buffer() );
                        n_buffered_ = put_position() - p_next_in;
                        return p_next_out - result;
                    }

                    case Codecvt::error:
                    {
                        *p_next_out++ = static_cast<wchar_t>( ascii::bad_char );
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

}  // namespace stdlib
