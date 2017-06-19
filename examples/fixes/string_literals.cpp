// Source encoding: utf-8 with BOM ∩
//
// Define NO_STDLIB_STRING_LITERALS to not add `s` literal operator to the
// global namespace (i.e., not do `using namespace std::string_literals;`).

#include <stdlib/all/basics.hpp>
using std::cout;
using std::endl;
using std::setw;
using std::to_string;

auto main( int n_args, char* args[] )
    -> int
{
    cout << "Arguments:" << endl;
    for( int i = 0; i < n_args; ++i )
    {
        // The concatenation here works because "“"s is a std::string.
        cout << setw( 2 ) << i << ": " << setw( 40 ) << "“"s + args[i] + "”" << endl;
    }
}
