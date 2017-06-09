#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/impl/windows_console_io/Console_output_buffer_.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <assert.h>     // assert
#include <streambuf>    // std::basic_streambuf

#include <stdlib/extension/Byte_to_wide_converter.hpp>              // Byte_to_wide_converter
#include <stdlib/workarounds/impl/windows_console_io/winapi.hpp>    // put_text_to_console

namespace stdlib{ namespace impl{ namespace windows_console_io{
    using std::basic_streambuf;
    using std::min;
    using std::wstring;

    inline auto write( wchar_t const* const data, Size const n )
        -> Size
    { return put_text_to_console( data, n ); }

    inline auto write( char const* const data, Size const n )
        -> Size
    {
        static Byte_to_wide_converter converter;

        constexpr Size result_size = Byte_to_wide_converter::in_buf_size;
        char const*     p_source    = data;
        wchar_t         result[result_size];
        Size            n_consumed  = 0;

        for( ;; )
        {
            Size const n_remaining = n - n_consumed;
            auto const chunk_size = min<Size>( converter.available_space(), n_remaining );
            converter.add( chunk_size, p_source );
            Size const n_converted = converter.convert_into( result, result_size );
            Size const n_written = write( result, n_converted );
            if( n_written < n_converted )
            {
                break;      // But really, how to signal an i/o error after translate?
            }
            n_consumed += chunk_size;
            assert( n_consumed <= n );
            if( n_consumed == n )
            {
                break;
            }
            p_source += chunk_size;
        }
        return n_consumed;
    }

    template< class Char >
    class Console_output_buffer_
        : public basic_streambuf<Char>
    {
    private:
        static constexpr Size buffer_size = 8;
        using Base = basic_streambuf<Char>;
        using Traits = typename Base::traits_type;
        using typename Base::char_type;
        using typename Base::int_type;

        Char    buffer_[buffer_size];

        Console_output_buffer_( Console_output_buffer_ const& ) = delete;

        auto writebuf_start() const     -> char_type*   { return Base::pbase(); }
        auto writebuf_beyond() const    -> char_type*   { return Base::epptr(); }
        auto write_position() const     -> char_type*   { return Base::pptr(); }

        void advance_write_position( int const n )      { Base::pbump( n ); }

    protected:
        auto flush( int const n_extra = 0 )
            -> bool
        {
            auto const p_start  = writebuf_start();
            Size const n = (write_position() - writebuf_start()) + n_extra;
            Size const n_written = write( p_start, n );
            if( n_written != n )
            {
                return false;
            }
            Base::setp( p_start, p_start + (buffer_size - 1) );
            return true;
        }

        auto sync()
            -> int  override
        { return (flush()? 0 : -1); }   // -1 = failure.

        auto overflow( int_type const c )
            -> int_type  override
        {
            assert( write_position() <= writebuf_beyond() );

            int n_extra = 0;
            if( not Traits::eq_int_type( c, Traits::eof() ) )
            {
                *write_position() = static_cast<Char>( c );
                ++n_extra;
            }
            bool const success = flush( n_extra );
            return (success? Traits::not_eof( c ) : Traits::eof());
        }

    public:
        Console_output_buffer_()
        {
            auto const buffer_beyond = buffer_ + (buffer_size - 1);
            Base::setp( buffer_, buffer_beyond );
        }
    };

    using Byte_console_output_buffer    = Console_output_buffer_<char>;
    using Wide_console_output_buffer    = Console_output_buffer_<wchar_t>;

}}}  // namespace stdlib::impl::windows_console_io
