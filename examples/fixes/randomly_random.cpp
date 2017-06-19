// Source encoding: utf-8 with BOM ∩
//
// Run this program a number of times to see that the sequence is
// different each time.
//
// Define STDLIB_NO_FIX_RANDOM_DEVICE to turn off the g++ fix.

#include <stdlib/all/basics.hpp>
using namespace std;

auto main()
    -> int
{
    random_device entropy;
    uniform_int_distribution<int> random_digit{ 0, 9 };
    for( int i = 1; i <= 7; ++i )
    {
        cout << random_digit( entropy ) << ' ';
    }
    cout << endl;
}
