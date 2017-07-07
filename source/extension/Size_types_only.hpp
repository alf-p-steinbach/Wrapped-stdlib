#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/Size.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stddef.h>     // ptrdiff_t, size_t
#include <cstddef>

namespace stdlib{

    using Size              = ptrdiff_t;
    using Index             = Size;

    using U_size            = size_t;
    using U_index           = U_size;

}  // namespace stdlib
