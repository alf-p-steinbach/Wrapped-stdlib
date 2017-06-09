#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/impl/windows_console_io/Wide_input_buffer.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/algorithm.hpp>   // std::remove
#include <stdlib/c/stddef.hpp>    // ptrdiff_t
#include <stdlib/streambuf.hpp>   // std::basic_streambuf

#include <stdlib/extension/Size.hpp>        // stdlib::(Size, Index)

namespace stdlib{ namespace impl{ namespace windows_console_io{
    using std::remove;

    namespace winapi{
        using Bool          = int;
        using Handle        = void*;
        using DWord         = unsigned;     static_assert( sizeof( DWord ) == 4, "!" );
        using UInt          = unsigned;

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
            wchar_t const*          lpFileName,
            DWord                   dwDesiredAccess,
            DWord                   dwShareMode,
            Security_attributes*    lpSecurityAttributes,
            DWord                   dwCreationDisposition,
            DWord                   dwFlagsAndAttributes,
            Handle                  hTemplateFile
            ) -> Handle;

        extern "C"
        auto __stdcall GetConsoleMode(
            Handle          hConsoleHandle,
            DWord*          lpMode
            ) -> Bool;

        extern "C"
        auto __stdcall GetStdHandle( DWord nStdHandle )
            -> Handle;

        extern "C"
        auto __stdcall ReadConsoleW(
            Handle          hConsoleInput,
            void*           lpBuffer,
            DWord           nNumberOfCharsToRead,
            DWord*          lpNumberOfCharsRead,
            void*           pInputControl
            ) -> Bool;

        extern "C"
        auto __stdcall SetConsoleMode(
            Handle          hConsoleHandle,
            DWord           dwMode
            ) -> Bool;

        extern "C"
        auto __stdcall WideCharToMultiByte(
            UInt            CodePage,
            DWord           dwFlags,
            wchar_t const*  lpWideCharStr,
            int             cchWideChar,
            char*           lpMultiByteStr,
            int             cbMultiByte,
            char const*     lpDefaultChar,
            Bool*           lpUsedDefaultChar
            ) -> int;

        extern "C"
        auto __stdcall WriteConsoleW(
            Handle          hConsoleOutput,
            void const*     lpBuffer,
            DWord           nNumberOfCharsToWrite,
            DWord*          lpNumberOfCharsWritten,
            void*           lpReserved
            ) -> Bool;
    }  // namespace winapi

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

    inline auto enable_ansi_escape_codes( winapi::Handle const stream_handle )
        -> winapi::DWord        // original console mode
    {
        winapi::DWord const ansi_escape_codes_flag =
            winapi::enable_virtual_terminal_processing;

        winapi::DWord original_mode = 0;
        winapi::GetConsoleMode( stream_handle, &original_mode );
        winapi::SetConsoleMode( stream_handle, original_mode | ansi_escape_codes_flag );
        return original_mode;
    }

    // Each `\r\n` is translated to just `\n`. I.e. the last returned text chunk from
    // a typed in line is terminated with L'\n'.
    inline auto get_text_from_console( wchar_t* const buffer, Size const buffer_size )
        -> Size
    {
        winapi::DWord n = 0;
        bool const success = !!winapi::ReadConsoleW(
            console_input_handle(), buffer, buffer_size, &n, nullptr
            );
        if( !success )
        {
            return 0;
        }
        auto const end = remove( buffer, buffer + n, L'\r' );
        return end - buffer;
    }

    // Each `\n` is translated to `\r\n`.
    inline auto put_text_to_console( wchar_t const* const buffer, Size const buffer_size )
        -> Size
    {
        winapi::DWord n = 0;
        bool const success = !!winapi::WriteConsoleW(
            console_output_handle(), buffer, buffer_size, &n, nullptr
            );
        if( !success )
        {
            return 0;
        }
        return n;
    }
}}}  // namespace stdlib::impl::windows_console_io
