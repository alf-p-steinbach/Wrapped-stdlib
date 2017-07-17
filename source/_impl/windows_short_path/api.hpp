#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_short_path/api.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/type_builders.hpp>   // ptr_

#include <stdlib/_impl/winapi_types.hpp>     // winapi::(DWord, max_path_length, ...)

namespace stdlib{ namespace impl{ namespace winapi{

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

}}}  // namespace stdlib::impl::winapi
