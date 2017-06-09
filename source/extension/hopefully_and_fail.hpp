#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/extension/hopefully_and_fail.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/STDLIB_NORETURN.hpp>
#endif

namespace stdlib {
    inline namespace hopefully_and_fail {
        using std::string;
        using std::runtime_error;

            -> bool
        { return condition; }

            -> bool
        { throw runtime_error( message ); }

    }  // inline namespace hopefully_and_fail
}  // namespace ppp_ex
