#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/all/of_sublibrary/thread_support.hpp>
//
// The C++ standard's section “Thread support library” (in C++14 that's §30).
// The set of headers included here are those in C++14 §30.1/1 table 149.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.


// Threads
#include <stdlib/thread.hpp>

// Mutual exclusion
#include <stdlib/mutex.hpp>
#include <stdlib/shared_mutex.hpp>

// Condition variables
#include <stdlib/condition_variable.hpp>

// Futures
#include <stdlib/future.hpp>
