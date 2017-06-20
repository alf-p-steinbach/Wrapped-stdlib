// Source encoding: utf-8 with BOM ∩
//
// Define STDLIB_NO_DEFAULT_C_LOCALE_FIX to suppresses the C locale config.
// Define STDLIB_NO_DEFAULT_CPP_LOCALE_FIX to suppresses the C++ locale config.
//
// Note: for wide stream console output this is mostly about *nix-land. In
// Windows the console i/o fix takes care of wide stream console output.

#include <stdlib/all/basics.hpp>
using namespace std;

auto main() -> int
{
    // The locale can affect numerical output, e.g. European decimal comma.
    wcout << L"Did you know, pi is roughly " << M_PI << L" :-)" << endl;
    wcout << L"Norwegian blåbærsyltetøy is a fav of 日本国 кошкаs." << endl;
}
