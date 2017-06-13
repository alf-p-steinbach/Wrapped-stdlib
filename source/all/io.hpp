#pragma once    // Source encoding: utf-8 with BOM ∩
// #include <stdlib/all/io.hpp>
// Copyright © 2017 Alf P. Steinbach, distributed under Boost license 1.0.

// The i/o headers listed by (http://en.cppreference.com/w/cpp/header),
// except the deprecated <strstream> header; use <sstream> instead.
#include <stdlib/c/stdio.hpp>     // C's i/o functions, e.g. printf.
#include <stdlib/fstream.hpp>     // basic_fstream, basic_ifstream, basic_ofstream, and several typedefs.
#include <stdlib/iomanip.hpp>     // Helper functions to control the format or input and output.
#include <stdlib/ioswfd.hpp>      // Forward declarations of all classes in the input/output part of the library.
#include <stdlib/iostream.hpp>    // Standard stream objects: cin, cout, cerr, clog, wcin, wcout, wcerr, wclog
#include <stdlib/istream.hpp>     // std::basic_istream class template and several typedefs.
#include <stdlib/ostream.hpp>     // std::basic_ostream, std::basic_iostream class templates and several typedefs
#include <stdlib/sstream.hpp>     // basic_stringstream, basic_istringstream, basic_ostringstream, several typedefs.
#include <stdlib/streambuf.hpp>   // basic_streambuf

// Not listed in this category by cppreference, but useful/necessary:
#include <stdlib/all/localization.hpp>
#include <stdlib/all/text.hpp>
