#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/windows_command_line.declarations.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/Size_types_only.hpp>         // stdlib::(Size, Index)
#include <stdlib/extension/type_builders.hpp>           // stdlib::ref_
#include <stdlib/extension/version.hpp>                 // stdlib::platform::is_windows

#include <stdlib/fix/msvc_named_boolean_operators.hpp>  // not

#include <utility>      // std::move
#include <vector>       // std::vector
#include <string>       // std::string

namespace stdlib{ namespace ext{ namespace process{
    using std::move;
    using std::string;
    using std::vector;

    constexpr
    inline auto has_original_command_line()                 // Platform-dependent.
        -> bool;

    // UTF-8. Original command line as passed to the process, e.g. in Windows.
    // Empty on systems with no such, i.e. where `not has_original_command_line()`.
    inline auto command_line()                              // Platform-dependent.
        -> string;

    // UTF-8 encoded command line arguments.
    class Command_line_args
    {
        Command_line_args( const int n, ptr_<const ptr_<const char>> args )
            : items_( args, args + n )
        {}

    protected:
        vector<string>      items_;

    public:
        auto begin() const  { return items_.begin(); }
        auto end() const    { return items_.end(); }

        auto size() const -> Size { return items_.size(); }

        auto operator[]( Index const i ) const
            -> ref_<const string>
        { return items_.at( i ); }

        static auto from_os_or_else_from(
            const int               argc,       // Pass 1st argument of `main` here.
            const ptr_<ptr_<char>>  argv        // Pass 2nd argument of `main` here.
            ) -> Command_line_args
        {
            // May be modified later to include other ungood-main-args platforms.
            return (
                platform::is_windows? Command_line_args{}
                : Command_line_args{ argc, argv }
                );
        }

        inline Command_line_args();                         // Platform-dependent.
    };

    // `main`-arguments style argument pointers for e.g. use of `getopt`.
    class Command_argv_array
        : private Command_line_args
    {
        vector<ptr_<char>>  pointers_;

    public:
        explicit operator bool() const { return true; }     // For C++14 `if` as `with`.

        auto argc() -> int              { return size(); }
        auto argv() -> ptr_<ptr_<char>> { return &pointers_[0]; }

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

}}} // namespace stdlib::ext::process
