#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/windows_command_line.declarations.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/Size_types_only.hpp>     // stdlib::(Size, Index)
#include <stdlib/extension/type_builders.hpp>       // stdlib::ref_

#include <vector>       // std::vector
#include <string>       // std::string

namespace stdlib{ namespace process{
    using std::string;
    using std::vector;

    inline auto command_line() -> string;

    class Command_line_args
    {
    private:
        vector<string>      items_;

    public:
        auto begin() const  { return items_.begin(); }
        auto end() const    { return items_.end(); }

        auto size() const -> Size { return items_.size(); }

        auto operator[]( Index const i ) const
            -> ref_<const string>
        { return items_.at( i ); }

        inline Command_line_args();
    };

}} // namespace stdlib::process
