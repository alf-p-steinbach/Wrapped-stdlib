#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/Size.hpp>
//
// Size types and signed result size functions.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <array>            // std::array
#include <bitset>           // std::bitset
#include <iterator>         // std::distance
#include <type_traits>      // std::remove_reference_t
#include <utility>          // std::(begin, end)
#include <stdlib/extension/Size_types_only.hpp>     // size_t, ptrdiff_t, Size, Index
#include <stdlib/extension/type_builders.hpp>       // stdlib::(array_of_, raw_array_of_)

#define STDLIB_ARRAY_SIZE( a ) ::stdlib::Array_size_<std::remove_reference_t<decltype(a)>>::value

namespace stdlib{ namespace ext{
    using std::begin;
    using std::bitset;
    using std::distance;
    using std::end;
    using std::remove_reference_t;

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
    // argument of the calling function. This is the same issue as with
    // C++17 std::size, at least in clang ATTOW. Hence the macro given above.

    template< class Result, class Type >
    constexpr inline auto array_size_( Type const& a )
        -> Result
    { return static_cast<Result>( Array_size_<remove_reference_t<decltype(a)>>::value ); }

    template< class Type >
    constexpr inline auto array_size( Type const& a )
        -> Size
    { return array_size_<Size>( a ); }

    template< class Collection >
    auto n_items_of( Collection const& c )
        -> Size
    { return distance( begin( c ), end( c ) ); }

    template< size_t n >
    auto n_items_of( bitset<n> const& bits )
        -> Size
    { return bits.count(); }

}}  // namespace stdlib::ext
