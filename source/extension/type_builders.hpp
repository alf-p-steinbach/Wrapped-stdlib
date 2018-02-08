#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/type_builders.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/extension/Size_types_only.hpp>         // stdlib::Size

#include <array>        // std::array
#include <type_traits>  // std::(make_*, add_*, remove_*)

namespace stdlib{ namespace ext{
    namespace impl {
        using std::add_const_t;
        using std::array;
        using std::make_signed_t;
        using std::make_unsigned_t;
        using std::remove_const_t;
        using std::remove_extent_t;
        using std::remove_pointer_t;
        using std::remove_reference_t;

        //---------------------------------------------------

        template< class Some_type >
        using type_ = Some_type;


        //---------------------------------------------------

        // Note: the more safe standard library converters such as std::add_pointer_t
        // are not used for commented builders because they would prevent template
        // argument deduction. The basic builders defined here are just names for the
        // conventional way of writing e.g. formal argument types. As such they carry
        // the same risk of unintended type result as the raw operator notation does,
        // but they have advantages such as supporting uniform `const` first notation,
        // more generally read-left-to-right declarations, and being self-descriptive.

        template< class Some_type >
        using ref_ = Some_type&;                // std::add_lvalue_reference_t<Some_type>;

        template< class Some_type >
        using ptr_ = Some_type*;                // std::add_pointer_t<Some_type>;

        template< class Some_reference_type >
        using unref_ = std::remove_reference_t<Some_reference_type>;
        
        template< class Some_pointer_type >
        using unptr_ = std::remove_pointer_t<Some_pointer_type>;

        template< class Some_type >
        using temp_ref_ = Some_type&&;          // std::add_rvalue_reference_t<Some_type>;

        template< class Some_type >
        using forwarding_ref_ = Some_type&&;    // Also known as a “universal reference”.

        template< size_t n, class Item >
        using array_of_ = array<Item, n>;

        template< class Item >
        using raw_array_ = Item[];

        template< size_t n, class Item >
        using raw_array_of_ = Item[n];

        template< class Some_array_type >
        using array_item_type_of_ = remove_extent_t<Some_array_type>;


        //---------------------------------------------------

        template< class Integer >
        using signed_ = std::make_signed_t< Integer >;

        template< class Some_type >
        using const_ = std::add_const_t< Some_type >;

        template< class Integer >
        using unsigned_ = std::make_unsigned_t< Integer >;

        template< class Some_type >
        using unconst_ = std::remove_const_t< Some_type >;

    }  // namespace impl

    inline namespace type_builders {
        using impl::type_;
        using impl::ref_;
        using impl::ptr_;
        using impl::unref_;
        using impl::unptr_;
        using impl::temp_ref_;
        using impl::forwarding_ref_;
        using impl::array_of_;
        using impl::raw_array_;
        using impl::raw_array_of_;
        using impl::array_item_type_of_;
        using impl::signed_;
        using impl::const_;
        using impl::unsigned_;
        using impl::unconst_;
    }  // inline namespace type_builders
}} // namespace stdlib::ext

