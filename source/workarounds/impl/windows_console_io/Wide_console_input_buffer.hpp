#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/impl/windows_console_io/Wide_console_input_buffer.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <assert.h>     // assert
#include <stddef.h>     // ptrdiff_t
#include <cstddef>
#include <iterator>     // std::(begin, end)
#include <streambuf>    // std::basic_streambuf

#include <stdlib/workarounds/impl/windows_console_io/constants.hpp> // general_buffer_size
#include <stdlib/workarounds/impl/windows_console_io/winapi.hpp>    // winapi::*

namespace stdlib{ namespace impl{ namespace windows_console_io{
    using std::basic_streambuf;
    using std::begin;
    using std::end;

    class Wide_console_input_buffer
        : public basic_streambuf<wchar_t>
    {
    private:
        static constexpr Size buffer_size = general_buffer_size;
        using Base = basic_streambuf<wchar_t>;
        using Traits = traits_type;

        wchar_t     buffer_[buffer_size];

        Wide_console_input_buffer( Wide_console_input_buffer const& ) = delete;

        auto readbuf_start() const      -> char_type*       { return eback(); }
        auto readbuf_beyond() const     -> char_type*       { return egptr(); }

        auto read_position() const      -> char_type*       { return gptr(); }
        void advance_read_position( int const n )           { gbump( n ); }

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
            Size const n        = get_text_from_console( p_start, buffer_size );

            setg( p_start, p_start, p_start + n );
            return (n == 0? Traits::eof() : Traits::to_int_type( *read_position() ));
        }

    public:
        Wide_console_input_buffer()
        { setg( buffer_, buffer_, buffer_ ); }
    };
}}}  // namespace stdlib::impl::windows_console_io
