#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/all/stroustrup_ppp_facilities.hpp>
//
// Corresponds to the `"std_lib_facilities.h"` header for Bjarne Stroustrup's book
// “Programming: Principles and Practice Using C++”, plus `hopefully` and `fail`,
// except that here there's no evil `using namespace std;`.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

// Silly-warning suppression:
#if defined( _MSC_VER )
#   pragma warning( disable: 4646 ) // 'noreturn' function has non-void return type.
#   define _SCL_SECURE_NO_WARNINGS  // Call to 'std::copy' (etc.) may be unsafe.
#endif

#include <stdlib/c/math.hpp>
#include <stdlib/c/string.hpp>
#include <stdlib/fstream.hpp>
#include <stdlib/stdexcept.hpp>
#include <stdlib/string.hpp>
#include <stdlib/sstream.hpp>
#include <stdlib/vector.hpp>

//using namespace std;      No, Bjarne. No!

#if !defined( PPP_NORETURN )
#   if defined( _MSC_VER )
#       define PPP_NORETURN     __declspec( noreturn )
#   elif defined( __GNUC__ )
#       define PPP_NORETURN     __attribute__(( noreturn ))
#   else
#       define PPP_NORETURN     [[noreturn]]
#   endif
#endif

namespace ppp {
    using std::string;
    using std::runtime_error;

    inline PPP_NORETURN void error( string const& message )
    { throw runtime_error( message ); }

    inline PPP_NORETURN void error( string const& s1, string const& s2 )
    { error( s1 + s2 ); }

}  // namespace ppp

namespace ppp_ex {
    using std::string;
    using std::runtime_error;

   // Functions added here for the same purpose, more convenient:

    inline auto hopefully( bool const condition )
        -> bool
    { return condition; }

    inline PPP_NORETURN auto fail( string const& message )
        -> bool
    { throw runtime_error( message ); }
}  // namespace ppp_ex
