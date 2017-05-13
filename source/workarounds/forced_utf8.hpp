#pragma once    // Source encoding: utf-8 ∩
// #include <stdlib/workarounds/forced_utf8.hpp>
//
// See e.g. the MSDN article on "pragma execution_character_set"
// at <url:https://msdn.microsoft.com/en-us/library/mt708823.aspx>.
//
// STDLIB_NO_WORKAROUND_FORCED_UTF8 suppresses forced UTF-8 literals.
//
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

#ifndef STDLIB_NO_WORKAROUND_FORCED_UTF8
#   if defined( _MSC_VER )
#       if _MSC_VER >= 1700     // Visual C++ 2015 or later
#           pragma execution_character_set( "utf-8" )   // UTF-8 narrow literals.
#       endif
#   endif
#endif
