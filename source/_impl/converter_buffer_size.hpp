#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/converter_buffer_size.hpp>
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/Size.hpp>        // stdlib::(Size, Index)

namespace stdlib{ namespace impl{
    using ext::Size;

    Size const  converter_buffer_size = 2048;       // Large enough for efficiency.

}}  // namespace stdlib::impl
