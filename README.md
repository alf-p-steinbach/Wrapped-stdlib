
What is *stdlib*?
---------------------

*stdlib* wraps the C++ standard library, provides common headers for functional areas like i/o, and fixes various problems with the Visual C++ and g++ implementations, e.g.:
* `char`-based (narrow) console i/o in Windows works with Unicode text, specifically UTF-8 encoding. For example, a novice program using `std::string`, that asks for the user’s name and responds with a personalized greeting, works even for Norwegian students. Or Danish ones.
* `wchar_t`-based (wide) console i/o in *nix-land works by default. This isn't commonly used functionality, but fixing it for *nix-land complements the fix for the narrow console i/o in Windows. It’s just nice to have things working.
* The `<stdlib/c/math.hpp>` header includes both `<math.h>` and `<cmath>`. No problem of which to choose: `<stdlib/c/math.hpp>` chooses both, thank you, for maximum portability. And the same for other C library headers that are available in C++.
    
    ![Winnie the pooh](images/pooh.jpg)
 
Two developments in the C++ infra-structure developments have made *stdlib*’s “always UTF-8” a practical, instead of just an idealistic, choice.

First, • the upcoming C++17 *filesystem* library, part of the C++17 standard library, lets you open or create or remove files via UTF-8 encoded `char` based filenames. This complements *stdlib* in a great way. *stdlib* therefore provides access to *filesystem* already with Visual C++ 2017 and later, and with recent g++ versions, as well as any C++ implementation that supports C++17 and later.

Secondly, • Visual C++, the main compiler on the Windows platform, now supports UTF-8 as the execution character set, i.e. for ordinary `char` based literals.

Visual C++ 2017’s  UTF-8 execution character set support is only partial. For example, as of Visual C++ 2017 command line arguments, the arguments of `main`, are encoded as Windows ANSI no matter what options you use, and output of a narrow string via a wide stream interprets it as Windows ANSI-encoded. But having UTF-8 encoded ordinary narrow literals goes 80% of the way. :)


How does *stdlib* work?
-----------------------

*stdlib* is a pure header library.

Microsoft’s mother-of-all-headers `<windows.h>`, which otherwise would define thousands of macros, isn't used. *stdlib* is clean in this respect. The few API functions that are used to support Unicode console i/o in Windows, are stable and are declared by *stdlib*'s own code.

The wide console i/o in \*nix-land is made to work via an automated call to `setlocale( LC_ALL, "" )`. A ditto global locale is also established at the C++ level. This can easily be foiled, but it's about making things *work by default*, which is generally better.

The Unicode-based narrow console i/o in Windows is made to work for international text by automatically installing special stream buffers in those of `cin`, `cout`, `cerr`, `clog`, `wcin`, `wcout`, `wcerr` and `wclog` that are connected to a console window. The special buffers use the Windows console API vis-à-vis the console, and for the narrow streams they translate between the console’s UCS-2 encoding and the C++ code’s UTF-8 encoding. Byte sequences that are invalid as UTF-8 do not cause a persisting error state, but are instead just replaced with character code 127, the ASCII “del” character.

The same conversion functionality is available to users of *stdlib* via `<stdlib/extension/Byte_to_wide_converter.hpp>` and `<stdlib/extension/Wide_to_byte_converter.hpp>`. These classes wrap use of `std::codecvt`. In particular this code deals with conversion failures such as invalid-as-UTF-8 byte sequences.

Who uses *stdlib*?
------------------

So far only the author has been thinking of using it, and he's too busy still adding to it, to use it. It's useful as-is, though.

What is *stdlib*’s goal?
-----------------------

The main goal is to enable learners and professionals who write small tool or exploratory programs, to be able to do that simply, and have those programs work with international text.

Here’s an example:

    // Source encoding: utf-8 with BOM ∩
    #include <stdlib/iostream.hpp>
    #include <stdlib/string.hpp>
    using namespace std;

    auto main() -> int
    {
        cout << "Hi, what’s your name? ";
        string name;
        getline( cin, name );
        cout << "Pleased to meet you, " << name << "!" << endl;
    }

This same code works in both *nix-land and Windows, when the name input by the user contains non-English characters.

How can your organization benefit from using *stdlib*?
------------------------------------------------------

With *stdlib*’s common headers, such as `<stdlib/c/math.hpp>`, or e.g. `<stdlib/all/io.hpp>`, there are
* fewer headers to include and possibly forget to include in your source code,
* portability problems due to e.g. referring unqualified to `printf` after only including `<cstdio>`, are reduced or eliminated, and
* writing small programs is a breeze compared with direct use of the standard library.

Also, it's nice to have working international text console i/o in Windows, with ordinary `char` based text representation.

License.
-----------

[Boost Software license version 1.0](http://www.boost.org/LICENSE_1_0.txt)