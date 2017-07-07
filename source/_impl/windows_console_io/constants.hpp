#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/_impl/windows_console_io/constants.hpp>
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <stdlib/_impl/converter_buffer_size.hpp>
#include <stdlib/extension/ascii.hpp>       // stdlib::ascii::*

namespace stdlib{ namespace impl{ namespace windows_console_io{

    const Size general_buffer_size = impl::converter_buffer_size;

}}}  // namespace stdlib::impl::windows_console_io
