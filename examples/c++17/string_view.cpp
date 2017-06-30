// Source encoding: utf-8 with BOM ∩
//
// For Visual C++ 2017 and earlier compile with option “/std::c++latest”.
// For g++, “g++ string_view.cpp -D STDLIB_USE_EXPERIMENTAL_CPP17”.
//
// Based on an example whose behavior I couldn't reproduce, with unintended
// Undefined Behavior, at <url: https://skebanga.github.io/string-view/>.
//
// The machinery at the start here is just to see a concrete example of
// how std::string does dynamic allocations. It’s possibly quite misleading
// because the custom allocator may prevent the compiler from completely
// optimizing away these allocations! Be that as it may, here goes:

#include <stdlib/all/basics.hpp>
#include <stdlib/string_view.hpp>
using namespace std;


//----------------------------------------------------------------------------
// Allocation tracking machinery:

namespace g{
    int allocations[1000] = {};
    int n_allocations = 0;
    bool track_allocations = true;
}  // namespace g

template< class T >
struct Tracking_allocator
    : allocator< T >
{
    template< class U > struct rebind { using other = Tracking_allocator<U>; };
    
    auto allocate( size_t const n, void const* const hint = nullptr )
        -> T*
    {
        (void) hint;
        if( g::track_allocations )
        {
            g::allocations[g::n_allocations++] = n;
        }
        return reinterpret_cast<T*>( malloc( n*sizeof( T ) ) );
    }
    
    void deallocate( T* const p, size_t const n )
    {
        (void) n;
        free( p );
    }
    
};

using String = basic_string<char, char_traits<char>, Tracking_allocator<char>>;
#ifdef USE_STRING
    using S = String;
#else
    using S = string_view;  // Has no allocator, cause is has no allocations.
#endif

//----------------------------------------------------------------------------
// Main example code:

auto compare( S const& s1, S const& s2 )
    -> bool
{
    if( s1 != s2 )
    {
        cout << '\"' << s1 << "\" does not match \"" << s2 << "\"\n";
        return false;
    }
    return true;
}

auto main()
    -> int
{
    String const s = "this is my input string";

    compare( s, "this is the first test string" );
    compare( s, "this is the second test string" );
    compare( s, "this is the third test string, it's a bit longer than the earlier two" );

    g::track_allocations = false;
    cout << g::n_allocations << " dynamic allocation(s)";
    if( g::n_allocations > 0 )
    {
        cout << " of size(s) ";
        for( int i = 0; i < g::n_allocations; ++i )
        {
            if( i > 0 )
            {
                cout << ", ";
            }
            cout << g::allocations[i];
        }
    }
    cout << "." << endl;
}
