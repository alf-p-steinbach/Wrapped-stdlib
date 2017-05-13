#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/impl/windows_console_io/Codecvt.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#include <codecvt>      // std::codecvt_utf8

namespace stdlib{ namespace impl{ namespace windows_console_io{
    using std::codecvt_utf8_utf16;

    using Codecvt           = codecvt_utf8_utf16<wchar_t>;
    using Codecvt_result    = decltype( Codecvt::ok );
    using Codecvt_state     = Codecvt::state_type;

}}}  // namespace stdlib::impl::windows_console_io
