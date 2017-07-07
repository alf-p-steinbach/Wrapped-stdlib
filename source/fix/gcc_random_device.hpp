#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/fix/gcc_random_device.hpp>

#ifndef STDLIB_NO_FIX_OF_RANDOM_DEVICE
#   ifdef __GNUC__
#       undef   _GLIBCXX_USE_RANDOM_TR1
#       define  _GLIBCXX_USE_RANDOM_TR1
#   endif
#endif
#include <random>
