#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_short_path/api.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/type_builders.hpp>   // ptr_

#include <stdlib/_impl/winapi_types.hpp>        // winapi::(DWord, max_path_length, ...)
#include <stdlib/_impl/winapi_constants.hpp>    // winapi::(max_path_length, cp_acp, ...)

namespace stdlib{ namespace impl{ namespace winapi{

    const DWord wc_no_best_fit_chars    = 0x00000400;   // From <winnls.h>.

    struct FileTime
    {
        DWord           dwLowDateTime;
        DWord           dwHighDateTime;
    };

    struct Win32_find_data
    {
        DWord           dwFileAttributes;
        FileTime        ftCreationTime;
        FileTime        ftLastAccessTime;
        FileTime        ftLastWriteTime;
        DWord           nFileSizeHigh;
        DWord           nFileSizeLow;
        DWord           dwReserved0;
        DWord           dwReserved1;
        wchar_t         cFileName[max_path_length];
        wchar_t         cAlternateFileName[14];
    };

    extern "C"
    auto __stdcall GetShortPathNameW(
        ptr_<const wchar_t>     lpszLongPath,
        ptr_<wchar_t>           lpszShortPath,
        DWord                   cchBuffer
        ) -> DWord ;

    extern "C"
    auto __stdcall FindFirstFileW(
        ptr_<const wchar_t>     lpFileName,
        ptr_<Win32_find_data>   lpFindFileData
        ) -> Handle;

    extern "C"
    auto __stdcall FindClose( Handle hFindFile )
        -> Bool;

    extern "C"
    auto __stdcall WideCharToMultiByte(
        UInt                CodePage,
        DWord               dwFlags,
        ptr_<const wchar_t> lpWideCharStr,
        int                 cchWideChar,
        ptr_<char>          lpMultiByteStr,
        int                 cbMultiByte,
        ptr_<const char>    lpDefaultChar,
        ptr_<Bool>          lpUsedDefaultChar
        ) -> int;

}}}  // namespace stdlib::impl::winapi
