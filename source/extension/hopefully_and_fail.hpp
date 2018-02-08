#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/hopefully_and_fail.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/fix/msvc_wolfcalls_about_std_functions.hpp>

#include <stdlib/extension/STDLIB_NORETURN.hpp>
#include <stdlib/extension/type_builders.hpp>       // stdlib::(ref_)

#include <stdlib/stdexcept.hpp>
#include <stdlib/string.hpp>

// Silly-warning suppression:
#if defined( _MSC_VER )
#   pragma warning( disable: 4646 ) // 'noreturn' function has non-void return type.
#endif

namespace stdlib{ namespace ext{
    namespace impl {
        using std::string;
        using std::runtime_error;

        struct Success{};
        struct Failure{};

        template< class Value >
        auto operator>>( Value const& v, Failure )
            -> bool
        { return not (v >> Success{}); }

        inline auto hopefully( const bool condition )
            -> bool
        { return condition; }

        inline STDLIB_NORETURN auto fail( ref_<const string> message )
            -> bool
        { throw runtime_error( message ); }
    }  // namespace impl

    inline namespace hopefully_and_fail {
        using impl::Success;
        using impl::Failure;
        using impl::operator>>;
        using impl::hopefully;
        using impl::fail;
    }  // inline namespace hopefully_and_fail

}}  // namespace stdlib::ext
