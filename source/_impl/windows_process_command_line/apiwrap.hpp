#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_main_arguments/apiwrap.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/hopefully_and_fail.hpp>              // stdlib::(hopefully, fail)
#include <stdlib/extension/type_builders.hpp>                   // stdlib::(raw_array_, ptr_)
#include <stdlib/_impl/windows_process_command_line/api.hpp>    // winapi::*
#include <stdlib/fix/msvc_named_boolean_operators.hpp>          // and

#include <memory>       // std::unique_ptr

namespace stdlib{ namespace impl{ namespace apiwrap{
    using std::unique_ptr;

    inline auto command_line_ptr()
        -> ptr_<const wchar_t>
    { return winapi::GetCommandLineW(); }

    inline void local_free( const ptr_<void> p ) { winapi::LocalFree( p ); }

    struct Command_line_args
    {
        using Ptr = unique_ptr<
            raw_array_< ptr_< wchar_t > >,
            ptr_< void(ptr_<void>) >
            >;

        int     count;
        Ptr     items;

        Command_line_args(
            const ptr_<const wchar_t> command_line = command_line_ptr()
            )
            : items{
                winapi::CommandLineToArgvW( command_line, &count ),
                &local_free
                }
        {
            hopefully( items != nullptr )
                or fail( "stdlib::impl::apiwrap - API-function CommandLineToArgvW failed" );
        }
    };

}}}  // stdlib::impl::apiwrap
