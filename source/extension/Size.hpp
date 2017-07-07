#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/Size.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <array>            // std::array
#include <bitset>           // std::bitset
#include <iterator>         // std::distance
#include <type_traits>      // std::extent
#include <utility>          // std::(begin, end)
#include <stdlib/extension/Size_types_only.hpp>     // size_t, ptrdiff_t, Size, Index
#include <stdlib/extension/type_builders.hpp>       // stdlib::(array_of_, raw_array_of_)

#define STDLIB_ARRAY_SIZE( a ) ::stdlib::Array_size_<decltype(a)>::value

namespace stdlib{
    using std::begin;
    using std::bitset;
    using std::distance;
    using std::end;

    template< class > struct Array_size_;

    template< class Item, size_t n >
    struct Array_size_      < raw_array_of_<n, Item> >
    {
        static constexpr Size value = n;
    };

    template< class Item, size_t n >
    struct Array_size_      < array_of_<n, Item> >
    {
        static constexpr Size value = n;
    };

    template< size_t n >
    struct Array_size_      < bitset< n > >
    {
        static constexpr Size value = n;
    };

    // As of C++14 this won't be constexpr for an argument that is a formal
    // argument of the calling function. Hence the macro given above.
    template< class Type >
    constexpr inline auto array_size( Type const& a )
        -> Size
    { return Array_size_<decltype(a)>::value; }

    template< class Collection >
    auto n_items_of( Collection const& c )
        -> Size
    { return distance( begin( c ), end( c ) ); }

    template< size_t n >
    auto n_items_of( bitset<n> const& bits )
        -> Size
    { return bits.count(); }

}  // namespace stdlib
