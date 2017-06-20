// Source encoding: utf-8 with BOM ∩
//
// For Visual C++ 2017 and earlier compile with option “/std::c++latest”.
// For g++, “g++ filesystem.cpp -D STDLIB_USE_EXPERIMENTAL_CPP17 -lstdc++fs”.

#include <stdlib/all/basics.hpp>
#include <stdlib/filesystem.hpp>
using namespace std;
namespace fs = std::filesystem;

auto main( int, char* args[] ) -> int
{
    const auto program_path         = fs::absolute( args[0] );
    const auto program_folder_path  = program_path.parent_path();

    cout
        << "This program resides in “"
        << program_folder_path.u8string()       //! Always use u8string().
        << "”." << endl;
}
