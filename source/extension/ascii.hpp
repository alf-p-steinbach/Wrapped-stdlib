#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/ascii.hpp>
//
// Names for special ASCII characters.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

namespace stdlib{ namespace ascii {
    char const      null        = '\0';         // '\0' 0x00
    char const      bell        = '\a';         // '\a' 0x07, ^G
    char const      backspace   = '\b';         // '\b' 0x07, ^H
    char const      tab         = '\t';         // '\t' 0x08, ^I, horizontal tab
    char const      linefeed    = '\n';         // '\n' 0x09, ^J
    char const      vtab        = '\v';         // '\v' 0x0A, ^K
    char const      formfeed    = '\f';         // '\f' 0x0B, ^L
    char const      enter       = '\r';         // '\r' 0x0C, ^M
    char const      xon         = '\x11';       //      0x11, ^Q, "continue"
    char const      xoff        = '\x13';       //      0x13, ^S, "stop"
    char const      end_of_text = '\x1A';       //      0x1A, ^Z, non-std MS meaning.
    char const      escape      = '\x1B';       //      0x1B
    char const      del         = '\x7F';       //      0x7F

    // Abbreviations as per ASCII 67:
    char const      NUL         = null;
    char const      BEL         = bell;
    char const      BS          = backspace;
    char const      HT          = tab;          // “Horizontal tab”
    char const      LF          = linefeed;
    char const      VT          = vtab;         // “Vertical tab”
    char const      FF          = formfeed;
    char const      CR          = enter;        // “Carriage return”
    char const      DC1         = xon;          // “Device control 1”
    char const      DC3         = xoff;         // “Device control 3”
    char const      SUB         = end_of_text;  // “Substitute”, but see below!
    char const      ESC         = escape;
    char const      DEL         = del;          // “Delete”

    // ASCII DEL, code 0x7F = 127, “delete”, is used in this library as a
    // replacement for encoding errors or unrepresentable code point.
    //
    // ASCII has a character dedicated to the purpose: SUB “substitute”, code 26,
    // ^Z. But in Windows ^Z is used as an EOF marker for text streams. So ^Z as
    // replacement is not usable in Windows, i.e. it's not a general solution.
    //
    // Unicode, an extension of ASCII, also has its own character dedicated to
    // the purpose, namely code U+FFFD “replacement character”. It translates to
    // at least two UTF-8 bytes so it's not trivial to check for. And it can't be
    // represented in simple single byte encodings such as codepage 437, so it's
    // not usable in single byte encodings, i.e. it's not a general solution.
    char const      bad_char    = del;

    template< class Number >
    inline auto contains( const Number v )
        -> bool
    { return (0 <= v and v <= 127); }

    template< class It >
    inline auto contains_all( const It start, const It beyond )
        -> bool
    {
        for( It it = start; it != beyond; ++it )
        {
            if( not ascii::contains( *it ) ) { return false; }
        }
        return true;
    }
}}  // namespace stdlib::ascii
