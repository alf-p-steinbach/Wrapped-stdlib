#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/fix/impl/windows_console_io/api.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/type_builders.hpp>   // ptr_

#include <stdlib/fix/msvc_named_boolean_operators.hpp>      // and
#include <stdlib/fix/impl/winapi_types.hpp>     // winapi::(DWord, ...)

namespace stdlib{ namespace impl{ namespace winapi{
    enum: DWord
    {
        std_input_handle    = DWord( -10 ),
        std_output_handle   = DWord( -11 ),
        std_error_handle    = DWord( -12 )
    };

    enum: DWord
    {
        enable_virtual_terminal_processing = 0x0004
    };

    enum: DWord
    {
        generic_read        = (0x80000000L),
        generic_write       = (0x40000000L),
        generic_execute     = (0x20000000L),
        generic_all         = (0x10000000L)         // (sic)
    };

    enum: DWord
    {
        create_new          = 1,
        create_always       = 2,
        open_existing       = 3,
        open_always         = 4,
        truncate_existing   = 5
    };

    enum: UInt
    {
        cp_acp              = 0,            // ANSI codepage id
        cp_utf8             = 65001         // UTF-8 codepage id
    };

    using Security_attributes = void;       // We don't need security attributes.

    extern "C"
    auto _stdcall CreateFileW(
        ptr_<const wchar_t>         lpFileName,
        DWord                       dwDesiredAccess,
        DWord                       dwShareMode,
        ptr_<Security_attributes>   lpSecurityAttributes,
        DWord                       dwCreationDisposition,
        DWord                       dwFlagsAndAttributes,
        Handle                      hTemplateFile
        ) -> Handle;

    extern "C"
    auto __stdcall GetConsoleMode(
        Handle          hConsoleHandle,
        ptr_<DWord>     lpMode
        ) -> Bool;

    extern "C"
    auto __stdcall GetStdHandle( DWord nStdHandle )
        -> Handle;

    extern "C"
    auto __stdcall ReadConsoleW(
        Handle          hConsoleInput,
        ptr_<void>      lpBuffer,
        DWord           nNumberOfCharsToRead,
        ptr_<DWord>     lpNumberOfCharsRead,
        ptr_<void>      pInputControl
        ) -> Bool;

    extern "C"
    auto __stdcall SetConsoleMode(
        Handle          hConsoleHandle,
        DWord           dwMode
        ) -> Bool;

    extern "C"
    auto __stdcall WideCharToMultiByte(
        UInt                    CodePage,
        DWord                   dwFlags,
        ptr_<const wchar_t>     lpWideCharStr,
        int                     cchWideChar,
        ptr_<char>              lpMultiByteStr,
        int                     cbMultiByte,
        ptr_<const char>        lpDefaultChar,
        ptr_<Bool>              lpUsedDefaultChar
        ) -> int;

    extern "C"
    auto __stdcall WriteConsoleW(
        Handle                  hConsoleOutput,
        ptr_<const void>        lpBuffer,
        DWord                   nNumberOfCharsToWrite,
        ptr_<DWord>             lpNumberOfCharsWritten,
        ptr_<void>              lpReserved
        ) -> Bool;
}}}  // namespace stdlib::impl::winapi

namespace stdlib{ namespace impl{ namespace windows_console_io{
    using std::equal;
    using std::remove;

    //inline auto input_stream_handle()
    //    -> winapi::Handle
    //{
    //    static winapi::Handle const the_handle =
    //        winapi::GetStdHandle( winapi::std_input_handle );
    //    return the_handle;
    //}

    //inline auto output_stream_handle()
    //    -> winapi::Handle
    //{
    //    static winapi::Handle const the_handle =
    //        winapi::GetStdHandle( winapi::std_output_handle );
    //    return the_handle;
    //}

    //inline auto error_stream_handle()
    //    -> winapi::Handle
    //{
    //    static winapi::Handle const the_handle =
    //        winapi::GetStdHandle( winapi::std_error_handle );
    //    return the_handle;
    //}

    inline auto console_input_handle()
        -> winapi::Handle
    {
        static const winapi::Handle the_handle = winapi::CreateFileW(
            L"CONIN$", winapi::generic_read, 0, nullptr, winapi::open_existing, 0, 0
        );
        return the_handle;
    }

    inline auto console_output_handle()
        -> winapi::Handle
    {
        static const winapi::Handle the_handle = winapi::CreateFileW(
            L"CONOUT$", winapi::generic_write, 0, nullptr, winapi::open_existing, 0, 0
        );
        return the_handle;
    }

    inline auto enable_ansi_escape_codes( const winapi::Handle stream_handle )
        -> winapi::DWord        // original console mode
    {
        const winapi::DWord ansi_escape_codes_flag =
            winapi::enable_virtual_terminal_processing;

        winapi::DWord original_mode = 0;
        winapi::GetConsoleMode( stream_handle, &original_mode );
        winapi::SetConsoleMode( stream_handle, original_mode | ansi_escape_codes_flag );
        return original_mode;
    }

    // Each `\r\n` is translated to just `\n`. I.e. the last returned text chunk from
    // a typed in line is terminated with L'\n'. Exception: a line consisting of only
    // ^Z, ASCII 26, is treated as zero bytes read, signaling EOF to a C++ iostream.
    inline auto get_text_from_console( const ptr_<wchar_t> buffer, const Size buffer_size )
        -> Size
    {
        winapi::DWord n_read = 0;
        const bool success = !!winapi::ReadConsoleW(
            console_input_handle(), buffer, buffer_size, &n_read, nullptr
            );
        if( !success )
        {
            return 0;
        }
        const auto end = remove( buffer, buffer + n_read, L'\r' );
        const int n = end - buffer;
        static const raw_array_of_<2, wchar_t> eot_line = { wchar_t( ascii::end_of_text ), L'\n' };
        return (n == 2 and equal( buffer, buffer + 2, eot_line )? 0 : n);
    }

    // Each `\n` is translated to `\r\n` down in the WriteConsoleW code (or "as-if").
    inline auto put_text_to_console( const ptr_<const wchar_t> buffer, const Size buffer_size )
        -> Size
    {
        winapi::DWord n = 0;
        const bool success = !!winapi::WriteConsoleW(
            console_output_handle(), buffer, buffer_size, &n, nullptr
            );
        if( !success )
        {
            return 0;
        }
        return n;
    }
}}}  // namespace stdlib::impl::windows_console_io
