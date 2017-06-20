#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/filesystem.hpp>
//
// std::path class and supporting functions.
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/extension/version.hpp>         // STDLIB_COMPILER_SUPPORTS_CPP17

#if STDLIB_COMPILER_SUPPORTS_CPP17
#   include <filesystem>
#elif STDLIB_USE_EXPERIMENTAL_CPP17
#   include <experimental/filesystem>
    namespace std {
        using namespace std::experimental;
    }  // namespace std;
#else
#   ifdef _MSC_VER
#       error "<filesystem> is apparently not available (use option `/std:c++latest`?)."
#   else
#       error "<filesystem> is apparently not available with this compiler & options."
#   endif
#endif
