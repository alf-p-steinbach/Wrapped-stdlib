#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/all/of_sublibrary/language_support.hpp>
//
// The C++ standard's section “Language support library” (in C++14 that's §18).
// The set of headers included here are those in C++14 §18/2 table 29.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.


// Types:
#include <stdlib/c/stddef.hpp>

// Implementation properties:
#include <stdlib/limits.hpp>
#include <stdlib/c/limits.hpp>
#include <stdlib/c/float.hpp>

// Integer types:
#include <stdlib/c/stdint.hpp>

// Start and termination:
#include <stdlib/c/stdlib.hpp>

// Dynamic memory management:
#include <stdlib/new.hpp>

// Type identification:
#include <stdlib/typeinfo.hpp>

// Exception handling:
#include <stdlib/exception.hpp>

// Initializer lists:
#include <stdlib/initializer_list.hpp>

// Other runtime support:
#include <stdlib/c/signal.hpp>
#include <stdlib/c/setjmp.hpp>
#include <stdlib/c/stdalign.hpp>
#include <stdlib/c/stdarg.hpp>
#include <stdlib/c/stdbool.hpp>
#include <stdlib/c/stdlib.hpp>
#include <stdlib/c/time.hpp>
