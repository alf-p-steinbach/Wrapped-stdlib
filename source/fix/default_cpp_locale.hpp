#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/fix/default_cpp_locale.hpp>
//
// The default locale needs to be set up
// • to make wide streams work in Unix-land, and
// • to make narrow character classification functions work in Windows.
//
// STDLIB_NO_FIX_OF_DEFAULT_CPP_LOCALE suppresses the locale auto-config.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/default_c_locale.hpp>      // Do this first.

#include <assert.h>
#include <locale>

namespace stdlib{ namespace impl{ namespace default_cpp_locale{
    using std::locale;

    class Envelope
    {
    private:

        // A.k.a. `locale::classic()`.
        ~Envelope() { locale::global( locale( "C" ) ); }

        Envelope() { locale::global( locale( "" ) ); }

    public:
        static auto make_singleton()
            -> bool
        {
            static Envelope the_envelope;
            return true;
        }
    };

#   ifndef STDLIB_NO_FIX_OF_DEFAULT_CPP_LOCALE
        const bool dummy = Envelope::make_singleton();
#   endif

}}}  // namespace stdlib::impl::default_cpp_locale
