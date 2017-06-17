#include <iostream>
#include <string>
using namespace std;

auto main() -> int
{
    string line;
    while( getline( cin, line ) )
    {
        cout << line << endl;
    }
}
