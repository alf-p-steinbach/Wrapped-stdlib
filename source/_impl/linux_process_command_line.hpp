#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/impl/linux_process_command_line.hpp>
//
// Implementation based on C code by blogger “Ivan”, ATTOW presented at
// <url: http://ivbel.blogspot.no/2011/11/how-to-get-process-full-name_30.html>.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef __linux__
#   error This file is only meaningful in Linux.
#endif

#include <stdlib/extension/hopefully_and_fail.hpp>  // stdlib::(hopefully, fail)
#include <stdlib/extension/process_command_line.declarations.hpp>   // 
#include <stdlib/extension/Size.hpp>                // stdlib::array_size
#include <stdlib/extension/type_builders.hpp>       // stdlib::<raw_array_of_>

#include <algorithm>            // std::replace
#include <fstream>
#include <string>
#include <sys/types.h>
#include <unistd.h>

namespace stdlib{
    using std::ifstream;
    using std::getline;
    using std::replace;
    using std::string;
    using std::to_string;

    namespace impl {
        inline auto get_command_line_data()
            -> string
        {
            const string path = "/proc/" + to_string( getpid() ) + "/cmdline";
            ifstream f{ path };
            hopefully( not f.fail() )
                or fail( "stdlib::impl::get_command_line_data - failed to open “" + path + "”" );
            string result;
            getline( f, result )
                or fail( "stdlib::impl::get_command_line_data - failed to read “" + path + "”" );
            return result;
        }
    }  // namespace impl

    inline auto process::command_line()
        -> string
    {
        // TODO: needs quoting of parts as necessary.
        string result = impl::get_command_line_data();
        replace( result.begin(), result.end(), '\0', ' ' );
        return result;
    };

    inline process::Command_line_args::Command_line_args()
    {
        const string s = impl::get_command_line_data();
        int i = 0;
        for( char const* p = &s[0]; *p; p += strlen( p ) + 1 )
        {
            items_.push_back( p );
        }
    }

} // namespace stdlib
