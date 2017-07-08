// Source encoding: utf-8 with BOM ∩
#include <stdlib/all/basics.hpp>
using namespace stdlib::type_builders;      // ptr_, ref_
using stdlib::process::Command_line_args;   // Command_line_args

namespace my{
    void cppmain( ref_<const Command_line_args> args )
    {
        using namespace std;
        cout << args.size() << " command line arguments:\n";
        for( int i = 0; i < args.size(); ++i )
        {
            cout << setw( 2 ) << i << ": “" << args[i] << "”.\n";
        }
    }
}  // namespace my

auto main( const int n, const ptr_<ptr_<char>> arg_pointers )
    -> int
{ my::cppmain( Command_line_args::from_os_or_else_from( n, arg_pointers ) ); }
