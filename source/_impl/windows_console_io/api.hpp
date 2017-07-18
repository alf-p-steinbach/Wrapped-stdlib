#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_console_io/api.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/type_builders.hpp>   // ptr_

#include <stdlib/_impl/winapi_types.hpp>        // winapi::(DWord, ...)
#include <stdlib/_impl/winapi_constants.hpp>    // winapi::(max_path_length, cp_utf8, ...)

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

    using Security_attributes = void;       // We don't need security attributes.

    extern "C"
    auto __stdcall CreateFileW(
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
