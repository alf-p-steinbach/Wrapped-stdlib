// Source encoding: utf-8 with BOM ∩
#include <stdlib/iostream.hpp>
#include <stdlib/string.hpp>
using namespace std;

auto main() -> int
{
    wcout << L"Hi, what’s your name (æ ø å)? ";
    wstring name;
    getline( wcin, name );
    wcout << L"Pleased to meet you, " << name << L"!" << endl;
}
