// Source encoding: utf-8 ∩
#include <stdlib/iostream.hpp>
#include <stdlib/string.hpp>
using namespace std;

auto main() -> int
{
    wcout << L"Hi, what’s your name? ";
    wstring name;
    getline( wcin, name );
    wcout << L"Pleased to meet you, " << name << L"!" << endl;
}
