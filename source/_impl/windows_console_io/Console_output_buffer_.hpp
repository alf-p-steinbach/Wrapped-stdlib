#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_console_io/Console_output_buffer_.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <assert.h>     // assert
#include <new>          // placement new
#include <streambuf>    // std::basic_streambuf

#include <stdlib/extension/Streaming_byte_to_wide_converter.hpp>    // Streaming_byte_to_wide_converter
#include <stdlib/_impl/windows_console_io/apiwrap.hpp>           // apiwrap::put_text_to_console

namespace stdlib{ namespace impl{ namespace windows_console_io{
    using std::basic_streambuf;
    using std::min;
    using std::streamsize;
    using std::wstring;

    inline auto write( const ptr_<const wchar_t> data, const Size n )
        -> Size
    { return apiwrap::put_text_to_console( data, n ); }

    inline auto write( const ptr_<const char> data, const Size n )
        -> Size
    {
        // Shenanigans to avoid (too early) destruction of the singleton converter:
        using Byte = unsigned char;
        alignas( Streaming_byte_to_wide_converter )
            static raw_array_of_<sizeof( Streaming_byte_to_wide_converter), Byte> converter_storage;
        static auto* const converter = ::new( &converter_storage ) Streaming_byte_to_wide_converter{};

        constexpr Size result_size = Streaming_byte_to_wide_converter::in_buf_size;
        ptr_<const char>    p_source    = data;
        wchar_t             result[result_size];
        Size                n_consumed  = 0;

        for( ;; )
        {
            const Size n_remaining = n - n_consumed;
            const auto chunk_size = min<Size>( converter->available_space(), n_remaining );
            converter->add( chunk_size, p_source );
            const Size n_converted = converter->convert_into( result, result_size );
            const Size n_written = write( result, n_converted );
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

    template< class Char > struct Complement_of_;
    template<> struct Complement_of_<char> { using T = wchar_t; };
    template<> struct Complement_of_<wchar_t> { using T = char; };

    template< class Char >
    class Console_output_buffer_
        : public basic_streambuf<Char>
    {
        static constexpr Size buffer_size = 8;
        using Base = basic_streambuf<Char>;
        using Traits = typename Base::traits_type;
        using typename Base::char_type;
        using typename Base::int_type;
        using Other_char = typename Complement_of_<Char>::T;
        using Other_buffer = Console_output_buffer_<Other_char>;

        friend Other_buffer;

        ptr_<Other_buffer>              p_buddy_    = nullptr;
        array_of_<buffer_size, Char>    buffer_;

        Console_output_buffer_( ref_<const Console_output_buffer_> ) = delete;

        auto writebuf_start() const     -> ptr_<char_type>  { return Base::pbase(); }
        auto writebuf_beyond() const    -> ptr_<char_type>  { return Base::epptr(); }
        auto write_position() const     -> ptr_<char_type>  { return Base::pptr(); }

        void advance_write_position( const int n )      { Base::pbump( n ); }

        void flush_buddy_buffer()
        {
            if( p_buddy_ != nullptr )
            {
                p_buddy_->flush();
            }
        }

    protected:
        auto flush( const int n_extra = 0 )
            -> bool
        {
            const auto p_start  = writebuf_start();
            const Size n = (write_position() - writebuf_start()) + n_extra;
            const Size n_written = write( p_start, n );
            if( n_written != n )
            {
                return false;
            }
            Base::setp( p_start, p_start + (buffer_size - 1) );
            return true;
        }

        auto overflow( const int_type c )
            -> int_type
            override
        {
            assert( write_position() <= writebuf_beyond() );

            int n_extra = 0;
            if( not Traits::eq_int_type( c, Traits::eof() ) )
            {
                flush_buddy_buffer();
                *write_position() = static_cast<Char>( c );
                ++n_extra;
            }
            const bool success = flush( n_extra );
            return (success? Traits::not_eof( c ) : Traits::eof());
        }

        auto sync()
            -> int
            override
        { return (flush()? 0 : -1); }   // -1 = failure.

        auto xsputn( ptr_<const char_type> s, const streamsize n )
            -> streamsize
            override
        {
            flush_buddy_buffer();
            return Base::xsputn( s, n );
        }

    public:
        void set_buddy( const ptr_<Other_buffer> p_other )
        {
            assert( p_buddy_ == nullptr );
            p_buddy_ = p_other;
        }

        ~Console_output_buffer_()
            override
        { flush(); }

        Console_output_buffer_()
        {
            const ptr_<char_type> buffer_start = buffer_.data();
            const ptr_<char_type> buffer_beyond = buffer_start + (buffer_.size() - 1);
            Base::setp( buffer_start, buffer_beyond );
        }
    };

    using Byte_console_output_buffer    = Console_output_buffer_<char>;
    using Wide_console_output_buffer    = Console_output_buffer_<wchar_t>;

}}}  // namespace stdlib::impl::windows_console_io
