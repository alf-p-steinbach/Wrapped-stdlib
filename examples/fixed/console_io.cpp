// Source encoding: utf-8 with BOM ∩
//
// Define STDLIB_NO_CONSOLE_IO_FIX to turn off the console i/o fix.
// Define STDLIB_NO_MSVC_UTF8_LITERALS_FIX to turn off forced UTF-8 literals.

#include <stdlib/iostream.hpp>
using namespace std;

auto main() -> int
{
    cout << u8"Every 日本国 кошка likes Norwegian blåbærsyltetøy.\n";
    cout << "I said, every 日本国 кошка likes Norwegian blåbærsyltetøy.\n";
}
