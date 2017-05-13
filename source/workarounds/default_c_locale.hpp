﻿#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/default_c_locale.hpp>
//
// The default locale needs to be set up
// • to make wide streams work in Unix-land, and
// • to make narrow character classification functions work in Windows.
//
// STDLIB_NO_WORKAROUND_DEFAULT_C_LOCALE suppresses the locale auto-config.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <assert.h>
#include <locale.h>
#include <clocale>

namespace stdlib{ namespace impl{ namespace default_c_locale{

    class Envelope
    {
    private:

        ~Envelope() { setlocale( LC_ALL, "C" ); }

        Envelope()
        {
            char const* const s = setlocale( LC_ALL, "" );  assert( s != nullptr );
        }

    public:
        static auto make_singleton()
            -> bool
        {
            static Envelope the_envelope;
            return true;
        }
    };

#   ifndef STDLIB_NO_WORKAROUND_DEFAULT_C_LOCALE
        bool const dummy = Envelope::make_singleton();
#   endif

}}}  // namespace stdlib::impl::default_c_locale