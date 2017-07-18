#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/winapi_constants.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/type_builders.hpp>   // ptr_

namespace stdlib{ namespace impl{ namespace winapi{

    int const max_path_length = 260;        // MAX_PATH
        
    enum: UInt
    {
        cp_acp              = 0,            // ANSI codepage id
        cp_utf8             = 65001         // UTF-8 codepage id
    };

}}}  // namespace stdlib::impl::winapi
