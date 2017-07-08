#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_console_io/Wide_console_input_buffer.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <assert.h>     // assert
#include <stddef.h>     // ptrdiff_t
#include <cstddef>
#include <iterator>     // std::(begin, end)
#include <streambuf>    // std::basic_streambuf

#include <stdlib/extension/type_builders.hpp>               // ptr_, array_of_
#include <stdlib/_impl/windows_console_io/constants.hpp> // general_buffer_size
#include <stdlib/_impl/windows_console_io/apiwrap.hpp>   // apiwrap::*

namespace stdlib{ namespace impl{ namespace windows_console_io{
    using std::basic_streambuf;
    using std::begin;
    using std::end;

    class Wide_console_input_buffer
        : public basic_streambuf<wchar_t>
    {
        static constexpr Size buffer_size = general_buffer_size;
        using Base = basic_streambuf<wchar_t>;
        using Traits = traits_type;

        array_of_<buffer_size, wchar_t> buffer_;

        Wide_console_input_buffer( Wide_console_input_buffer const& ) = delete;

        auto readbuf_start() const      -> ptr_<char_type>      { return eback(); }
        auto readbuf_beyond() const     -> ptr_<char_type>      { return egptr(); }

        auto read_position() const      -> ptr_<char_type>      { return gptr(); }

        void advance_read_position( const int n ) { gbump( n ); }

    protected:
        auto pbackfail( const int_type ch )
            -> int_type
            override
        { (void) ch; return traits_type::eof(); }               // TODO:

        auto underflow()            // Called by uflow()
            -> int_type
            override
        {
            assert( read_position() == readbuf_beyond() );

            const auto p_start  = readbuf_start();
            const Size n        = apiwrap::get_text_from_console( p_start, buffer_size );

            setg( p_start, p_start, p_start + n );              // first, next, last
            return (n == 0? Traits::eof() : Traits::to_int_type( *read_position() ));
        }

    public:
        Wide_console_input_buffer()
        {
            const ptr_<char_type> buffer_start = buffer_.data();
            setg( buffer_start, buffer_start, buffer_start );   // first, next, last
        }
    };
}}}  // namespace stdlib::impl::windows_console_io
