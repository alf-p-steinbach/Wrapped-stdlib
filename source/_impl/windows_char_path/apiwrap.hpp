#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_short_path/apiwrap.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/Size.hpp>                    // stdlib::(Size, array_size)
#include <stdlib/_impl/windows_short_path/api.hpp>      // ...winapi::(DWord, max_path_length, ...)

#include <string>       // std::wstring

namespace stdlib{ namespace impl{ namespace apiwrap{
    using std::wstring;

    // This function isn't used because it doesn't convert certain short non-ASCII items.
    inline auto get_short_path( wstring const& long_path )
        -> wstring
    {
        Size const n = long_path.length();
        if( n == 0 ) { return L""; }
            
        wchar_t buffer[winapi::max_path_length];
        Size const short_length = winapi::GetShortPathNameW(
            long_path.c_str(), buffer, array_size( buffer )
            );
        return wstring{ buffer, buffer + short_length };    // L"" if fail.
    }
 
}}}  // namespace stdlib::impl::apiwrap
