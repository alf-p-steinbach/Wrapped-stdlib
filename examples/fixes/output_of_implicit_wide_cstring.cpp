// Source encoding: utf-8 with BOM ∩
//
// Define STDLIB_NO_OUTPUT_OF_IMPLICIT_WIDE_C_STRING_FIX to avoid the fix.
// Without the fix the address of the string is presented, instead of text.

#include <stdlib/all/basics.hpp>
using namespace std;
using namespace stdlib::type_builders;      // ptr_

struct Implicit_wide_string
{
    operator ptr_<const wchar_t>() const { return L"Blåbærsyltetøy!"; }
};

auto main() -> int
{
    wcout << Implicit_wide_string{} << endl;
}
