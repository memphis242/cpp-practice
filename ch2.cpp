#include <iostream>
#include <cstdint>
#include <cassert>
#include <algorithm>

/* constexpr helper functions */

/* Forward Declarations of Local Functions */
static size_t count_occurrences( const std::string&, char c );

/* Main Program */
int main(void)
{
   std::cout << "This program presents some concepts from"
                " \"Chapter 2: A Tour of C++: The Basics\""
                " in Bjorne's book." << std::endl;

   std::cout << "Example range-for loop output: \n";
   int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
   for ( auto e : arr )
   {
      std::cout << e << " ";
   }
   std::cout << std::endl;
   std::cout << std::endl;

   std::cout << "Example range-for loop to modify container elements: "
                "Incrementing by 1...\n";
   // 🗒: The reference operator differs from the "pointer to" '*' operator as
   //     follows:
   //       - After declaration, you don't use the prefix '*' (dereferencing op)
   //         to access the value held by the reference.
   //       - A reference cannot be made to refer to a different object after
   //         initialization.
   for ( auto& e : arr )
   {
      std::cout << ++e << " ";
   }
   std::cout << std::endl;
   std::cout << std::endl;

   // 🗒: nullptr is the C++ null pointer value
   //const char * TEST_STRING = "Hello world!";
   const std::string TestStr = "Hello world!";
   std::cout << "h:       "  << count_occurrences( TestStr, 'h'  ) << std::endl;
   std::cout << "a:       "  << count_occurrences( TestStr, 'a'  ) << std::endl;
   std::cout << "l:       "  << count_occurrences( TestStr, 'l'  ) << std::endl;
   std::cout << "\\0:      " << count_occurrences( TestStr, '\0' ) << std::endl;
   //std::cout << "nullptr: "  << count_occurrences( nullptr, '\0' ) << std::endl;
   std::cout << std::endl;
}

/**
 * @brief Counts how many times a character appears in a string.
 *
 * @param str The std::string
 * @param c The character to count occurrences of.
 * @return size_t The number of times the character 'c' appears in the string
 *
 * @note If 'str' is nullptr or 'len' is 0, the function returns 0.
 * @note If 'c' is the null terminator ('\0'), the function returns 1.
 */
static size_t count_occurrences( const std::string& str, char c )
{
   return std::count(str.begin(), str.end(), c);
}
