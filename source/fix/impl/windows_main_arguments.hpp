#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/fix/impl/windows_main_arguments.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef _WIN32
#   error This file is only meaningful in Windows.
#endif

#include <stdlib/fix/impl/main_arguments/winapi.hpp>

#include <stdlib.h>     // __argv, __argc
#include <cstdlib>

namespace stdlib{ namespace impl{ namespace windows_main_arguments{


}}} // namespace stdlib::impl::windows_main_arguments
