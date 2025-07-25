#include <string>

std::string fizzbuzz_naive_solution(int start, int end)
{
   // Assume start is less than or equal to end
   std::string sol = "";
   for ( int i = start; i < end; i++ )
   {
      std::string itr_str = "";
      if ( i % 3 == 0 ) itr_str += "Fizz";
      if ( i % 5 == 0 ) itr_str += "Buzz";
      sol += itr_str + " ";
   }

   return sol;
}
