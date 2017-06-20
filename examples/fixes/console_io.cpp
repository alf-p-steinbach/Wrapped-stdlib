// Source encoding: utf-8 with BOM ∩
//
// Define STDLIB_NO_CONSOLE_IO_FIX to turn off the console i/o fix.
// Define STDLIB_NO_MSVC_UTF8_LITERALS_FIX to turn off forced UTF-8 literals.

#include <stdlib/all/basics.hpp>
using namespace std;

auto main() -> int
{
    cout << u8"Every 日本国 кошка likes Norwegian blåbærsyltetøy." << endl;
    cout << "I said, every 日本国 кошка likes Norwegian blåbærsyltetøy." << endl;
    cout << endl;
    cout << "By the way, what’s your name? ";
    string name;
    getline( cin, name );
    cout << "Pleased to meet you, " << name << "!" << endl;
}
