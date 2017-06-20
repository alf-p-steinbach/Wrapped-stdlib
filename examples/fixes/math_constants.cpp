// Source encoding: utf-8 with BOM ∩
//
// Define STDLIB_NO_MATH_CONSTANTS to turn off inclusion of the constants.

#include <stdlib/all/basics.hpp>
using namespace std;
namespace m = stdlib::math;

auto main() -> int
{
    cout << "Did you know, pi is roughly " << M_PI << " :-)" << endl;
    cout << setprecision( numeric_limits<double>::digits10 );
    cout << "Or more precisely, π ≈ " << m::pi << "." << endl;
}
