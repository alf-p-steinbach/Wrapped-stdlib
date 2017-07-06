#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/Size.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stddef.h>     // ptrdiff_t
#include <cstddef>

namespace stdlib{

    using Size              = ptrdiff_t;
    using Index             = Size;

}  // namespace stdlib
