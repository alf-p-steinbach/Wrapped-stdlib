#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/Streaming_byte_to_wide_converter.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <algorithm>    // std::copy
#include <assert.h>     // assert
#include <iterator>     // std::(begin, end)

#include <stdlib/extension/ascii.hpp>           // ascii::bad_char
#include <stdlib/extension/Codecvt.hpp>         // stdlib::(Codecvt, Codecvt_result)
#include <stdlib/extension/Size.hpp>            // stdlib::(Size, Index)
#include <stdlib/extension/type_builders.hpp>   // stdlib::(ptr_, raw_array_of_)
#include <stdlib/_impl/converter_buffer_size.hpp>

namespace stdlib{
    using std::begin;
    using std::copy;
    using std::end;

    class Streaming_byte_to_wide_converter
    {
    public:
        static constexpr Size in_buf_size = impl::converter_buffer_size;

    private:
        Codecvt                             codecvt_{};
        Codecvt_state                       conversion_state_{};    // mb_state
        array_of_<in_buf_size, char>        in_buf_;
        Size                                n_buffered_ = 0;

        auto start_of_buffer()  -> ptr_<char>       { return in_buf_.data(); }
        auto put_position()     -> ptr_<char>       { return start_of_buffer() + n_buffered_; }
        auto beyond_buffer()    -> ptr_<const char> { return start_of_buffer() + in_buf_.size(); }

    public:
        auto n_buffered() const         -> Size     { return n_buffered_; }
        auto available_space() const    -> Size     { return in_buf_size - n_buffered_; }

        void add(
            const Size              n,
            const ptr_<const char>  chars
            )
        {
            assert( n <= available_space() );
            copy( chars, chars + n, put_position() );
            n_buffered_ += n;
        }

        auto convert_into(
            const ptr_<wchar_t>     result,
            const Size              result_size
            ) -> Size
        {
            ptr_<const char>    p_next_in       = start_of_buffer();
            ptr_<wchar_t>       p_next_out      = result;

            for( ;; )
            {
                const auto p_start_in = p_next_in;
                const auto p_start_out = p_next_out;
                const auto result_code = static_cast<Codecvt_result>( codecvt_.in(
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
                        copy<ptr_<const char>>( p_next_in, put_position(), start_of_buffer() );
                        n_buffered_ = put_position() - p_next_in;
                        return p_next_out - result;
                    }

                    case Codecvt::error:
                    {
                        *p_next_out++ = static_cast<wchar_t>( ascii::bad_char );
    // The Holy Standard (C++14) declares, in its §22.4.1.4.2/2:
    // “[the do_in function] Stops if it encounters a character it cannot convert.
    // It always leaves the from_next and to_next pointers pointing one beyond the
    // last element successfully converted.” But MSVC 2017 moves it one more byte,
    // which is practical but non-conforming behavior. So, don't do it for MSVC:
    #if !defined( _MSC_VER ) // TODO: Replace with check of behavior.
                        ++p_next_in;
    #endif
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
