#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/all/stroustrup_ppp_facilities.unqualified.hpp>
//
// Corresponds to the `"std_lib_facilities.h"` header for Bjarne Stroustrup's book
// “Programming: Principles and Practice Using C++”, plus `hopefully` and `fail`.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.
#pragma once

#include <stdlib/all/ppp_facilities.hpp>
using namespace std;            // This directive is in Stroustrup's original header.
using namespace ppp;            // `error` in global namespace is also in original.
using namespace ppp_ex;         // Same convention for our `hopefully` and `fail`.
