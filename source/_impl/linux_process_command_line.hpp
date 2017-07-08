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
#include <stdlib/extension/type_builders.hpp>       // stdlib::raw_array_

#include <algorithm>            // std::replace
#include <fstream>
#include <string>

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
            static const raw_array_<char> funcname = "stdlib::impl::get_command_line_data";

            const string path = "/proc/self/cmdline";   // "self" provides getpid()
            ifstream f{ path };
            hopefully( not f.fail() )
                or fail( string() + funcname + " - failed to open “" + path + "”" );
            string result;
            getline( f, result )
                or fail( string() + funcname + " - failed to read “" + path + "”" );
            return result;
        }
    }  // namespace impl

    constexpr
    inline auto has_original_command_line()
        -> bool
    { return false; }

    inline auto process::command_line()
        -> string
    { return ""; }

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
