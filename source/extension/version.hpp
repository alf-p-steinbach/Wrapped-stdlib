#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/extension/version.hpp>
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef STDLIB_IS_CPP11
#   define STDLIB_IS_CPP11 (__cplusplus >= 201103)
#endif

#ifndef STDLIB_IS_CPP14
#   define STDLIB_IS_CPP14 (__cplusplus >= 201402)
#endif

#ifndef STDLIB_IS_CPP17
#   define STDLIB_IS_CPP17 (__cplusplus > 201402)
#endif
