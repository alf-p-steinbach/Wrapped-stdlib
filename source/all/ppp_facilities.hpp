#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/all/stroustrup_ppp_facilities.hpp>
//
// Corresponds to the `"std_lib_facilities.h"` header for Bjarne Stroustrup's book
// “Programming: Principles and Practice Using C++”, plus `hopefully` and `fail`,
// except that here there's no evil `using namespace std;`.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.


// Silly-warning suppression:
#if defined( _MSC_VER )
#   define _SCL_SECURE_NO_WARNINGS  // Call to 'std::copy' (etc.) may be unsafe.
#endif

#include <stdlib/extension/hopefully_and_fail.hpp>
#include <stdlib/extension/type_builders.hpp>

#include <stdlib/c/math.hpp>
#include <stdlib/c/string.hpp>
#include <stdlib/fstream.hpp>
#include <stdlib/stdexcept.hpp>
#include <stdlib/string.hpp>
#include <stdlib/sstream.hpp>
#include <stdlib/vector.hpp>

//using namespace std;      No, Bjarne. No!

namespace ppp {
    using std::string;
    using std::runtime_error;
    using stdlib::ref_;

    // Bjarne's functions:

    inline STDLIB_NORETURN void error( ref_<const string> message )
    { throw runtime_error( message ); }

    inline STDLIB_NORETURN void error( ref_<const string> s1, ref_<const string> s2 )
    { error( s1 + s2 ); }

}  // namespace ppp

namespace ppp_ex {

    // Functions added here for the same purpose, more convenient:
    using namespace stdlib::hopefully_and_fail;

}  // namespace ppp_ex
