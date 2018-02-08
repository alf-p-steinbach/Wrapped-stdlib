#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_char_path.hpp>
//
// Best effort compatible-with-runtime-library path.
// In Windows some result path items can be alternate short names, if that’s
// available for the file system, unless the long path is all ASCII, in which
// case it’s just returned as-is.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef _WIN32
#   error This file is only meaningful in Windows.
#endif

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/extension/char_path.declarations.hpp>

#include <stdlib/_impl/windows_char_path/api.hpp>// stdlib::impl:winapi::*
#include <stdlib/extension/ascii.hpp>                   // stdlib::ext::ascii::contains_all
#include <stdlib/extension/hopefully_and_fail.hpp>      // stdlib::ext::(hopefully, fail)
#include <stdlib/extension/type_builders.hpp>           // stdlib::ext::(ref_)
#include <stdlib/extension/utf8_conversion.hpp>         // stdlib::ext::(utf8_from, wide_from_utf8)

namespace stdlib{ namespace ext{
    using std::string;
    using std::wstring;
    using namespace std::literals;

    namespace impl {
        using namespace ext;

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

        //inline auto is_pseudo_path_item( ref_<const wstring> name )
        //    -> bool
        //{
        //    if( name == L"." or name == L".." )
        //    {
        //        return true;
        //    }
        //    if( name.find_first_of( L"*?:" ) != wstring::npos )
        //    {
        //        return true;
        //    }
        //    return false;
        //}

        struct Possibly_empty_string
        {
            string value;
            explicit operator bool() const { return (value.length() > 0); }
        };

        inline auto ansi_from(
            const ptr_<const wchar_t>   item,
            const Size                  item_len,
            const bool                  substitution_allowed  = false
            )
            noexcept
            -> Possibly_empty_string
        {
            namespace w = stdlib::impl::winapi;
            assert( item_len > 0 );

            string result( item_len, '\0' );
            w::Bool used_substitution = false;
            Size const n_bytes = static_cast<Size>( w::WideCharToMultiByte(
                w::cp_acp,                          // CodePage
                w::wc_no_best_fit_chars,            // dwFlags
                item,                               // lpWideCharStr
                static_cast<int>( item_len ),       // cchWideChar,
                &result[0],                         // lpMultiByteStr
                static_cast<int>( result.size() ),  // cbMultiByte
                &ascii::bad_char,                   // lpDefaultChar
                &used_substitution                  // lpUsedDefaultChar
                ) );

            if( n_bytes == 0 or used_substitution and not substitution_allowed )
            {
                return {};
            }

            result.resize( n_bytes );
            return { move( result ) };
        }

        struct Possibly_empty_wstring
        {
            wstring value;
            explicit operator bool() const { return (value.length() > 0); }
        };

        inline auto alternate_name(
            const ptr_<const wchar_t> path,
            const ptr_<const wchar_t> last_item
            )
            noexcept
            -> Possibly_empty_wstring
        {
            if( is_pseudo_path_item( last_item ) )
            {
                return {};
            }
            namespace w = stdlib::impl::winapi;
            w::Win32_find_data info{};
            w::Handle const h = w::FindFirstFileW( path, &info );
            w::FindClose( h );
            const ptr_<wchar_t> ws = info.cAlternateFileName;
            bool const ok = (h != w::Handle( -1 ) and ws[0] != L'\0');
            return {ok? ws : L""};
        }

        inline auto ansi_path(
            wstring         long_path,
            const bool      substitution_allowed = false
            )
            -> wstring
        {
            if( long_path.length() == 0 ) { return long_path; }
            long_path.append( L"\0\0", 2 );

            wstring result;
            replace( long_path.begin(), long_path.end(), '\\', '\0' );
    
            for( ptr_<wchar_t> p = &long_path[0]; *p != L'\0'; p += wcslen( p ) + 1 )
            {
                if( result.length() > 0 )
                {
                    result += L'\\';
                    *(p - 1) = L'\\';
                }

                Size const n = wcslen( p );
                if( ascii::contains_all( p, p + n ) )
                {
                    result += p;
                }
                else if( const auto ansi = ansi_from( p, n, false ) )
                {
                    result.append( ansi.value.begin(), ansi.value.end() );
                }
                else if( const auto alt = alternate_name( &long_path[0], p ))
                {
                    result += alt.value;
                }
                else if( substitution_allowed )
                {
                    const auto rough_ansi = ansi_from( p, n, true );
                    assert( rough_ansi.value.length() > 0 );
                    result.append( rough_ansi.value.begin(), rough_ansi.value.end() );
                }
                else
                {
                    fail( string()
                        + "stdlib::impl::ansi_path - unable to represent last item in"
                        + " “" + utf8_from( &long_path[0] ) + "”"
                        );
                }
            }
            return result;
        }
    }  // namespace impl

    inline auto char_path_with_substitution( const bool substitution_allowed, wstring long_path )
        -> string
    {
        if( ascii::contains_all( long_path.begin(), long_path.end() ) )
        {
            return string( long_path.begin(), long_path.end() );
        }
        wstring const ws = impl::ansi_path( long_path, substitution_allowed );
        return string( ws.begin(), ws.end() );
    }

    inline auto char_path_with_substitution( const bool substitution_allowed, string long_utf8_path )
        -> string
    {
        if( ascii::contains_all( long_utf8_path.begin(), long_utf8_path.end() ) )
        {
            return long_utf8_path;
        }
        wstring const ws = impl::ansi_path( wide_from_utf8( long_utf8_path ), substitution_allowed );
        return string( ws.begin(), ws.end() );
    }

}}  // namespace stdlib::ext

