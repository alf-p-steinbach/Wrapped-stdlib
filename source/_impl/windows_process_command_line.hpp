#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/impl/windows_command_line.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef _WIN32
#   error This file is only meaningful in Windows.
#endif

#include <stdlib/extension/process_command_line.declarations.hpp>   // 
#include <stdlib/extension/utf8_conversion.hpp>                     // stdlib::utf8_from
#include <stdlib/_impl/windows_process_command_line/apiwrap.hpp>    // impl::apiwrap::*

namespace stdlib{ namespace ext{
    constexpr
    inline auto has_original_command_line()
        -> bool
    { return true; }

    inline auto process::command_line()
        -> string
    { return utf8_from( stdlib::impl::apiwrap::command_line_ptr() ); };

    inline process::Command_line_args::Command_line_args()
    {
        const stdlib::impl::apiwrap::Command_line_args wide_items;
        for( int i = 0; i < wide_items.count; ++i )
        {
            items_.push_back( utf8_from( wide_items.items[i] ) );
        }
    }
}} // namespace stdlib::ext

