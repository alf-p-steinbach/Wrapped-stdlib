// Source encoding: utf-8 with BOM ∩
#include <stdlib/all/basics.hpp>                // Used here: <iostream> and <iomanip>
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
