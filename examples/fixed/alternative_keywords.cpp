// Source encoding: utf-8 with BOM ∩
//
// Define STDLIB_NO_NAMED_BOOLEAN_OPERATORS_FIX to turn off <iso646.h> inclusion.

#include <stdlib/all/basics.hpp>
using std::cout;
using std::cerr;
using std::endl;
namespace m = stdlib::math;

auto main( int n_args, char* args[] )
    -> int
{
    if( n_args == 2 and args[1] == "secret_password"s )
    {
        cout << "You guessed the secret password! Fantastic!" << endl;
        return EXIT_SUCCESS;
    }
    else if( n_args != 2 or args[1] == "/?"s or args[1] == "--help"s )
    {
        cerr << "Usage: " << args[0] << " YOUR-PASSWORD-GUESS" << endl;
    }
    return EXIT_FAILURE;
}
