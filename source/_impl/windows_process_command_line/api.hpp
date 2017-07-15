#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_main_arguments/api.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/type_builders.hpp>   // ptr_

#include <stdlib/_impl/winapi_types.hpp>     // winapi::(DWord, ...)

#ifdef _MSC_VER
#   pragma comment( lib, "shell32.lib" )        // For CommandLineToArgvW
#endif

namespace stdlib{ namespace impl{ namespace winapi{

    extern "C"
    auto __stdcall GetCommandLineW()
        -> ptr_<wchar_t>;

    extern "C"
    auto __stdcall CommandLineToArgvW(
        ptr_<const wchar_t>     lpCmdLine,
        ptr_<int>               pNumArgs
        ) -> ptr_<ptr_<wchar_t>>;

    extern "C"
    auto __stdcall LocalFree( Handle hMem )
        -> Handle;

}}}  // stdlib::impl::winapi
