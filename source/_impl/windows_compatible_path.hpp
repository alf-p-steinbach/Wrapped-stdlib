#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/compatible_path.hpp>
//
// Best effort compatible-with-runtime-library path.
// In Windows the result is a short path, if that’s available for the file system,
// and unless the long path is all ASCII, in which case it’s just returned as-is.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef _WIN32
#   error This file is only meaningful in Windows.
#endif

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/_impl/windows_short_path/api.hpp>      // stdlib::impl:winapi::*
#include <stdlib/extension/ascii.hpp>                   // stdlib::ascii::contains_all
#include <stdlib/extension/type_builders.hpp>           // stdlib::(ref_)
#include <stdlib/extension/utf8_conversion.hpp>         // stdlib::(utf8_from, wide_from_utf8)

namespace stdlib{
    using std::string;
    using std::wstring;

    inline auto is_pseudo_path_item( ptr_<const wchar_t> name )
        -> bool
    {
        if( wcscmp( name, L"." ) == 0 or wcscmp( name, L".." ) == 0 )
        {
            return true;
        }
        if( wcspbrk( name, L"*?:" ) != nullptr )
        {
            return true;
        }
        return false;
    }

    inline auto is_pseudo_path_item( ref_<const wstring> name )
        -> bool
    {
        if( name == L"." or name == L".." )
        {
            return true;
        }
        if( name.find_first_of( L"*?:" ) != wstring::npos )
        {
            return true;
        }
        return false;
    }

    inline auto short_path( wstring long_path )
        -> wstring
    {
        if( long_path.length() == 0 ) { return long_path; }
        long_path += L'\0';

        wstring result;
        replace( long_path.begin(), long_path.end(), '\\', '\0' );
    
        for( ptr_<wchar_t> p = &long_path[0]; *p != L'\0'; p += wcslen( p ) + 1 )
        {
            if( result.length() > 0 )
            {
                result += L'\\';
                *(p - 1) = L'\\';
            }

            bool shortname_added = false;
        
            if( not is_pseudo_path_item( p ) )
            {
                namespace w = impl::winapi;
                w::Win32_find_data info{};
                w::Handle const h = w::FindFirstFileW( &long_path[0], &info );
                w::FindClose( h );
                if( h != w::Handle( -1 ) and info.cAlternateFileName[0] != L'\0' )
                {
                    result += info.cAlternateFileName;
                    shortname_added = true;
                }
            }
        
            if( not shortname_added )
            {
                result += p;
            }
        }
        return result;
    }

    inline auto compatible_path( ref_<const wstring> long_path )
        -> wstring
    {
        if( ascii::contains_all( long_path.begin(), long_path.end() ) )
        {
            return long_path;
        }
        return short_path( long_path );
    }

    inline auto compatible_path( ref_<const string> long_utf8_path )
        -> string
    {
        if( ascii::contains_all( long_utf8_path.begin(), long_utf8_path.end() ) )
        {
            return long_utf8_path;
        }
        return utf8_from( short_path( wide_from_utf8( long_utf8_path ) ) );
    }

}  // namespace stdlib
