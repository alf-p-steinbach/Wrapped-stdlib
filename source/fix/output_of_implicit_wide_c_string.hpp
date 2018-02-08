#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/fix/output_of_implicit_wide_c_string.hpp>
//
// This is a fix for a defect in standard library, where an object that's implicitly
// convertible to `char const*` /can/ be output to a narrow stream, but an object
// that's implicitly convertible to `wchar_t const*` /cannot/ be output to a wide
// stream (it's presented as a pointer value because the templated `operator<<` is
// not considered by overload resolution). I reported the defect years ago, as of
// 2017. As far as I know nothing happened with that defect report.
//
// STDLIB_NO_OUTPUT_OF_IMPLICIT_WIDE_C_STRING_FIX suppresses the fix.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/type_builders.hpp>   // stdlib::ext::(ref_, ptr_)
#include <ostream>

#ifndef STDLIB_NO_FIX_OF_OUTPUT_OF_IMPLICIT_WIDE_C_STRING
#pragma push_macro( "REF_" )
#pragma push_macro( "PTR_" )
#undef REF_
#define REF_ ::stdlib::ext::ref_
#undef PTR_
#define PTR_ ::stdlib::ext::ptr_

    namespace std {

        inline auto operator<< (
            REF_<basic_ostream<wchar_t, char_traits<wchar_t>>>  stream,
            const PTR_<const wchar_t>                           s
            )
            -> stdlib::ext::ref_<basic_ostream<wchar_t, char_traits<wchar_t>>>
        { return stream.write( s, char_traits<wchar_t>::length( s ) ); }

    }  // namespace std

#pragma pop_macro( "PTR_" )
#pragma pop_macro( "REF_" )
#endif
