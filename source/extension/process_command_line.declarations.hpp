#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/windows_command_line.declarations.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/Size_types_only.hpp>         // stdlib::(Size, Index)
#include <stdlib/extension/type_builders.hpp>           // stdlib::ref_
#include <stdlib/fix/msvc_named_boolean_operators.hpp>  // not

#include <utility>      // std::move
#include <vector>       // std::vector
#include <string>       // std::string

namespace stdlib{ namespace process{
    using std::move;
    using std::string;
    using std::vector;

    constexpr
    inline auto has_original_command_line()             // Platform-dependent.
        -> bool;

    // UTF-8. Original command line as passed to the process, e.g. in Windows.
    // Empty on systems with no such, i.e. where `not has_original_command_line()`.
    inline auto command_line()                          // Platform-dependent.
        -> string;

    class Command_line_args
    {
    protected:
        vector<string>      items_;

    public:
        auto begin() const  { return items_.begin(); }
        auto end() const    { return items_.end(); }

        auto size() const -> Size { return items_.size(); }

        auto operator[]( Index const i ) const
            -> ref_<const string>
        { return items_.at( i ); }

        inline Command_line_args();                     // Platform-dependent.
    };

    class Command_argv_array
        : private Command_line_args
    {
        vector<ptr_<char>>  pointers_;

    public:
        auto argc() const   -> int              { return size(); }
        auto argv()         -> ptr_<ptr_<char>> { return &pointers_[0]; }

        Command_argv_array( Command_line_args args = {} )
            : Command_line_args{ move( args ) }
        {
            for( ref_<string> s : Command_line_args::items_ )
            {
                pointers_.push_back( &s[0] );
            }
            pointers_.push_back( nullptr );
        }
    };

}} // namespace stdlib::process
