#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_console_io.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef _WIN32
#   error This file is only meaningful in Windows.
#endif

#include <iostream>
#include <stddef.h>         // size_t

#include <stdlib/extension/type_builders.hpp>       // ptr_
#include <stdlib/fix/default_locale.hpp>
#include <stdlib/_impl/windows_console_io/Byte_console_input_buffer.hpp>
#include <stdlib/_impl/windows_console_io/Console_output_buffer_.hpp>
#include <stdlib/_impl/windows_console_io/Wide_console_input_buffer.hpp>

#include <io.h>     // _isatty, _get_osfhandle (Visual C++ extensions supported by g++).

// Output of a pure ASCII narrow string to a wide stream is safe. Output of a narrow
// string with characters outside the ASCII range is likely to produce garbage, because
// the machinery in Microsoft's runtime library interprets those bytes as Windows ANSI.
// The following overload prevents inadvertent garbage result for attempted output of a
// narrow literal to a wide stream, by making the call ambiguous. You can force such
// output (resolving the ambiguity) by converting the literal to pointer, e.g. by
// placing a `0+` in front of it: `wcout << 0+"Woo hoo, I'm using '+' instead of 'L'!";`.
// But really, just use a wide literal, `L`. Unless it's a named narrow literal.
//
using STDLIB_MAKES_THIS_CALL_AMBIGUOUS_TO_PREVENT_GARBAGE_OUTPUT = char const;
template< size_t n >
auto operator<<( 
    std::wostream&,
    STDLIB_MAKES_THIS_CALL_AMBIGUOUS_TO_PREVENT_GARBAGE_OUTPUT (&)[n]
    )
    -> std::wostream&;

namespace stdlib{ namespace impl{ namespace windows_console_io{
    using std::cin; using std::cout; using std::cerr; using std::clog;
    using std::wcin; using std::wcout; using std::wcerr; using std::wclog;
    using std::basic_ios;
    using std::streambuf;
    using std::wstreambuf;

    class Envelope
    {
    private:
        static constexpr int n_std_streams = 4;
        const array_of_<n_std_streams, ptr_<basic_ios<char>>>
            byte_streams_ = { &cin, &cout, &cerr, &clog };
        const array_of_<n_std_streams, ptr_<basic_ios<wchar_t>>>
            wide_streams_ = { &wcin, &wcout, &wcerr, &wclog };

        array_of_<n_std_streams, ptr_<streambuf>>   default_byte_buffer_ = {};  // Assigned by <init>.
        array_of_<n_std_streams, ptr_<wstreambuf>>  default_wide_buffer_ = {};  // Assigned by <init>.

        winapi::DWord   original_console_mode_ = winapi::DWord( -1 );

        static auto is_console( const int stream_id )
            -> bool
        {
            // return !!_isatty( stream_id );  //! False positive for redirection to nul device. :(
            auto const output_handle = reinterpret_cast<winapi::Handle>( _get_osfhandle( stream_id ) );
            winapi::DWord dummy;
            return !!winapi::GetConsoleMode( output_handle, &dummy );
        }

        ~Envelope()
        {
            for( int i = 0; i < n_std_streams; ++i )
            {
                if( default_byte_buffer_[i] != nullptr )
                {
                    byte_streams_[i]->rdbuf( default_byte_buffer_[i] );
                }
                if( default_wide_buffer_[i] != nullptr )
                {
                    wide_streams_[i]->rdbuf( default_wide_buffer_[i] );
                }
            }
        }

        Envelope()
        {
            static Byte_console_input_buffer    byte_in_buf;
            static Byte_console_output_buffer   byte_out_buf;
            static Byte_console_output_buffer   byte_err_buf;
            static Byte_console_output_buffer   byte_log_buf;

            static Wide_console_input_buffer    wide_in_buf;
            static Wide_console_output_buffer   wide_out_buf;
            static Wide_console_output_buffer   wide_err_buf;
            static Wide_console_output_buffer   wide_log_buf;

            byte_out_buf.set_buddy( &wide_out_buf );
            wide_out_buf.set_buddy( &byte_out_buf );

            byte_err_buf.set_buddy( &wide_err_buf );
            wide_err_buf.set_buddy( &byte_err_buf );

            byte_log_buf.set_buddy( &wide_log_buf );    // TODO: consider err streams too.
            wide_log_buf.set_buddy( &byte_log_buf );

            const raw_array_<ptr_<streambuf>> byte_buffers =
            {
                &byte_in_buf, &byte_out_buf, &byte_err_buf, &byte_log_buf
            };

            const raw_array_<ptr_<wstreambuf>> wide_buffers =
            {
                &wide_in_buf, &wide_out_buf, &wide_err_buf, &wide_log_buf
            };

            for( int i = 0; i < n_std_streams; ++i )
            {
                const int c_stream_id = (i > 2? 2 : i);
                if( is_console( c_stream_id ) )
                {
                    default_byte_buffer_[i] = byte_streams_[i]->rdbuf( byte_buffers[i] );
                    default_wide_buffer_[i] = wide_streams_[i]->rdbuf( wide_buffers[i] );

#ifndef STDLIB_NO_ANSI_ESCAPES_FIX
                    if( i > 0 )
                    {
                        // enable_ansi_escape_codes() doesn't work with a direct i/o
                        // handle, must use a stream handle; possibly it's per stream.
                        const auto h = reinterpret_cast<winapi::Handle>(
                            _get_osfhandle( c_stream_id )
                            );
                        winapi::DWord const old_mode = apiwrap::enable_ansi_escape_codes( h );
                        if( original_console_mode_ == winapi::DWord( -1 ) )
                        {
                            original_console_mode_ = old_mode;
                        }
                    }
#endif
                }
            }
        }

    public:
        static auto make_singleton()
            -> bool
        {
            static Envelope the_envelope;
            return true;
        }
    };

    const bool dummy = Envelope::make_singleton();

}}}  // namespace stdlib::impl::windows_console_io
