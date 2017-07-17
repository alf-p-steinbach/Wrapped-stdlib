﻿#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/winapi_types.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/type_builders.hpp>   // ptr_

namespace stdlib{ namespace impl{ namespace winapi{

    int const max_path_length = 260;            // MAX_PATH
        
    using Bool          = int;
    using Handle        = ptr_<void>;
    using DWord         = unsigned;     static_assert( sizeof( DWord ) == 4, "!" );
    using UInt          = unsigned;

}}}  // namespace stdlib::impl::winapi
