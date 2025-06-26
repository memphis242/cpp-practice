#include <string>
#include <iostream>

int main(void)
{
   std::cout << std::to_string(9) << '\n';
   return 0;
}

/*
When compiled with:
    
   g++ -Wall -Wextra -Wpedantic -pedantic-errors -Wconversion -Wdouble-promotion
      -fsanitize=bool -fsanitize=undefined -fsanitize-trap
      -fanalyzer
      -std=c++17
      -Og -g3
      -I.
      -fdiagnostics-color
      -c to_string_test.cpp
      -o to_string_test.o
   
It seems to just be the GCC static analyzer (-fanalyzer) involved with this.
Removing -fanalyzer produces no warning.
SOLUTION: After further investigation, I see in the GCC docs that even as of
GCC 15.1, -fanalyzer is only suitable for C code, not C++. See the initial
sentences on the option:
   
https://gcc.gnu.org/onlinedocs/gcc-15.1.0/gcc/Static-Analyzer-Options.html

The full warning printout is shown below:
    
In constructor 'std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]':
cc1plus.exe: warning: use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
  'std::string std::__cxx11::to_string(int)': events 1-2
    │
    │C:/w64devkit/lib/gcc/x86_64-w64-mingw32/15.1.0/include/c++/bits/basic_string.h:4530:3:
    │ 4530 |   to_string(int __val)
    │      |   ^~~~~~~~~
    │      |   |
    │      |   (1) entry to 'std::__cxx11::to_string'
    │......
    │ 4536 |     const unsigned __uval = __neg ? (unsigned)~__val + 1u : __val;
    │      |                             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    │      |                                   |
    │      |                                   (2) following 'true' branch (when '__val < 0')... ─>─┐
    │      |                                                                                        │
    │
  'std::string std::__cxx11::to_string(int)': events 3-4
    │
    │      |                                                                                        │
    │      |┌───────────────────────────────────────────────────────────────────────────────────────┘
    │ 4536 |│    const unsigned __uval = __neg ? (unsigned)~__val + 1u : __val;
    │      |│                                    ~~~~~~~~~~~~~~~~~^~~~
    │      |│                                                     |
    │      |└────────────────────────────────────────────────────>(3) ...to here
    │ 4537 |     const auto __len = __detail::__to_chars_len(__uval);
    │ 4538 |     string __str;
    │      |            ~~~~~
    │      |            |
    │      |            (4) calling 'std::__cxx11::basic_string<char>::basic_string' from 'std::__cxx11::to_string'
    │
    └──> 'std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]': event 5
           │
           │  585 |       basic_string()
           │      |       ^~~~~~~~~~~~
           │      |       |
           │      |       (5) entry to 'std::__cxx11::basic_string<char>::basic_string'
           │
         'std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]': event 6
           │
           │  586 |       _GLIBCXX_NOEXCEPT_IF(is_nothrow_default_constructible<_Alloc>::value)
           │      |       ^~~~~~~~~~~~~~~~~~~~
           │      |       |
           │      |       (6) region created on stack here
           │
         'std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]': event 7
           │
           │  586 |       _GLIBCXX_NOEXCEPT_IF(is_nothrow_default_constructible<_Alloc>::value)
           │      |       ^~~~~~~~~~~~~~~~~~~~
           │      |       |
           │      |       (7) capacity: 8 bytes
           │
         'std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]': event 8
           │
           │cc1plus.exe:
           │ (8): use of uninitialized value '<unknown>' here
           │
cc1plus.exe: warning: use of uninitialized value '<unknown>' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
  'int main()': events 1-2
    │
    │to_string_test.cpp:4:5:
    │    4 | int main(void)
    │      |     ^~~~
    │      |     |
    │      |     (1) entry to 'main'
    │    5 | {
    │    6 |    std::cout << std::to_string(9) << '\n';
    │      |                 ~~~~~~~~~~~~~~~~~
    │      |                               |
    │      |                               (2) calling 'std::__cxx11::to_string' from 'main'
    │
    └──> 'std::string std::__cxx11::to_string(int)': events 3-4
           │
           │C:/w64devkit/lib/gcc/x86_64-w64-mingw32/15.1.0/include/c++/bits/basic_string.h:4530:3:
           │ 4530 |   to_string(int __val)
           │      |   ^~~~~~~~~
           │      |   |
           │      |   (3) entry to 'std::__cxx11::to_string'
           │......
           │ 4536 |     const unsigned __uval = __neg ? (unsigned)~__val + 1u : __val;
           │      |                             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
           │      |                                   |
           │      |                                   (4) following 'false' branch (when '__val >= 0')... ─>─┐
           │      |                                                                                          │
           │
         'std::string std::__cxx11::to_string(int)': events 5-6
           │
           │      |                                                                                          │
           │      |┌─────────────────────────────────────────────────────────────────────────────────────────┘
           │ 4536 |│    const unsigned __uval = __neg ? (unsigned)~__val + 1u : __val;
           │      |│                   ^~~~~~
           │      |│                   |
           │      |└──────────────────>(5) ...to here
           │ 4537 |     const auto __len = __detail::__to_chars_len(__uval);
           │ 4538 |     string __str;
           │      |            ~~~~~
           │      |            |
           │      |            (6) calling 'std::__cxx11::basic_string<char>::basic_string' from 'std::__cxx11::to_string'
           │
           └──> 'std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]': event 7
                  │
                  │  585 |       basic_string()
                  │      |       ^~~~~~~~~~~~
                  │      |       |
                  │      |       (7) entry to 'std::__cxx11::basic_string<char>::basic_string'
                  │
                'std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]': event 8
                  │
                  │  586 |       _GLIBCXX_NOEXCEPT_IF(is_nothrow_default_constructible<_Alloc>::value)
                  │      |       ^~~~~~~~~~~~~~~~~~~~
                  │      |       |
                  │      |       (8) region created on stack here
                  │
                'std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]': event 9
                  │
                  │  586 |       _GLIBCXX_NOEXCEPT_IF(is_nothrow_default_constructible<_Alloc>::value)
                  │      |       ^~~~~~~~~~~~~~~~~~~~
                  │      |       |
                  │      |       (9) capacity: 8 bytes
                  │
                'std::__cxx11::basic_string<_CharT, _Traits, _Alloc>::basic_string() [with _CharT = char; _Traits = std::char_traits<char>; _Alloc = std::allocator<char>]': event 10
                  │
                  │cc1plus.exe:
                  │ (10): use of uninitialized value '<unknown>' here
                  │
*/
