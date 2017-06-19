// Source encoding: utf-8 with BOM ∩

#include <stdlib/all/basics.hpp>
using namespace std;
namespace m = stdlib::math;

auto main() -> int
{
    cout << setprecision( numeric_limits<double>::digits10 );
    cout << "Did you know, that π ≈ " << m::pi << "?" << endl;
}
