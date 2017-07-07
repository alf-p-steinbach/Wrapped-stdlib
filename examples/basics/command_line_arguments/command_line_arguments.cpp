// Source encoding: utf-8 with BOM ∩
#include <stdlib/all/basics.hpp>                // Used here: <iostream> and <iomanip>
#include <stdlib/extension/process_command_line.hpp>
using namespace std;

auto main()
    -> int
{
    const stdlib::process::Command_line_args args;
    cout << args.size() << " command line arguments:\n";
    for( int i = 0; i < args.size(); ++i )
    {
        cout << setw( 2 ) << i << ": “" << args[i] << "”.\n";
    }
}
