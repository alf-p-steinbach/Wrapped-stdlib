#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/fix/msvc_named_boolean_operators.hpp>
//
// Standard C++ provides “and”, “or” and “not”. Visual C++ doesn't, by default. See the
// article on “iso646” at <url:https://msdn.microsoft.com/en-us/library/dn494964.aspx>.
//
// STDLIB_NO_FIX_OF_NAMED_BOOLEAN_OPERATORS suppresses this conformance measure.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef STDLIB_NO_FIX_OF_NAMED_BOOLEAN_OPERATORS
#   if defined( _MSC_VER )
#       include <iso646.h>
#   endif
#endif
