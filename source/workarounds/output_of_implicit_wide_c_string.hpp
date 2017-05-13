#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/output_of_implicit_wide_c_string.hpp>
//
// This is a fix for a defect in standard library, where an object that's implicitly
// convertible to `char const*` /can/ be output to a narrow stream, but an object
// that's implicitly convertible to `wchar_t const*` /cannot/ be output to a wide
// stream (it's presented as a pointer value because the templated `operator<<` is
// not considered by overload resolution). I reported the defect years ago, as of
// 2017. As far as I know nothing happened with that defect report.
//
// STDLIB_NO_WORKAROUND_OUTPUT_OF_IMPLICIT_WIDE_C_STRING suppresses the fix.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <ostream>

#ifndef STDLIB_NO_WORKAROUND_OUTPUT_OF_IMPLICIT_WIDE_C_STRING
    namespace std {

        inline auto operator<< (
            basic_ostream<wchar_t, char_traits<wchar_t>>&   stream,
            wchar_t const* const                            s
            ) -> basic_ostream<wchar_t, char_traits<wchar_t>>&
        { return stream.write( s, char_traits<wchar_t>::length( s ) ); }

    }  // namespace std
#endif
