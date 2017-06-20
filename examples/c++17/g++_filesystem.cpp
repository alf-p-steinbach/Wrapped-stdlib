// Source encoding: utf-8 with BOM ∩
//
// g++ "g++_filesystem.cpp" -lstdc++fs -include stdlib/fix/console_io.hpp

#include <iostream>
#include <locale>
#include <string>
#include <experimental/string_view>
#include <experimental/filesystem>
namespace std{
    namespace filesystem = experimental::filesystem;
}
using namespace std;
namespace fs = std::filesystem;

auto main( int, char* args[] ) -> int
{
    auto const program_path         = fs::absolute( args[0] );
    auto const program_folder_path  = program_path.parent_path();

    cout
        << "This program resides in “"
        << program_folder_path.u8string()       //! Always use u8string().
        << "”." << endl;
}
