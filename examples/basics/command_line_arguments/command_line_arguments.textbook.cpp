// Source encoding: utf-8 with BOM ∩
#include <iostream>
#include <iomanip>          // std::setw
using namespace std;

auto main( int n_args, char* args[] )
    -> int
{
    cout << n_args << " command line arguments:\n";
    for( int i = 0; i < n_args; ++i )
    {
        cout << setw( 2 ) << i << ": “" << args[i] << "”.\n";
    }
}
