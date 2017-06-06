#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/extension/Byte_order.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/STDLIB_BYTE_ORDER.hpp>

namespace stdlib {
    struct Byte_order
    {
        enum Enum
        {
            little_endian   = STDLIB_LITTLE_ENDIAN,
            big_endian      = STDLIB_BIG_ENDIAN,
            mixed_endian    = STDLIB_MIXED_ENDIAN
        };
    };

    constexpr
    inline auto byte_order()
        -> Byte_order::Enum
    { return static_cast<Byte_order::Enum>( STDLIB_BYTE_ORDER ); }

}  // namespace stdlib
