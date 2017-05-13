// Source encoding: utf-8 ∩
#include <stdlib/iostream.hpp>
#include <stdlib/string.hpp>
using namespace std;

auto main() -> int
{
    cout << "Hi, what’s your name? ";
    string name;
    getline( cin, name );
    cout << "Pleased to meet you, " << name << "!" << endl;
}
