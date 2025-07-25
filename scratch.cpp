#include <iostream>
#include <map>
#include <string>

std::string fizzbuzz_naive_solution(int start, int end);
std::string fizzbuzz_map_solution(int start, int end);

int main(void)
{
   auto println = [](){ std::cout << '\n'; };
   std::string sol;

   std::cout << "Naive Solution:" << '\n';
   sol = fizzbuzz_naive_solution(1, 100);
   std::cout << sol;
   println();

   std::cout << "Map Solution:" << '\n';
   sol.clear();
   sol = fizzbuzz_map_solution(1, 100);
   std::cout << sol;
   println();
}

std::string fizzbuzz_naive_solution(int start, int end)
{
   // Assume start is less than or equal to end
   std::string sol = "";
   for ( int i = start; i <= end; i++ )
   {
      std::string itr_str = "";
      if ( i % 3 == 0 ) itr_str += "Fizz";
      if ( i % 5 == 0 ) itr_str += "Buzz";
      if ( itr_str.empty() ) itr_str += std::to_string(i);
      sol += itr_str + " ";
   }

   return sol;
}

std::string fizzbuzz_map_solution(int start, int end)
{
   // Assume start is less than or equal to end
   static const std::map<int, std::string> FZMap =
   {
      { 3, "Fizz" },
      { 5, "Buzz" }
   };

   std::string sol = "";
   for ( int i = start; i <= end; i++ )
   {
      std::string itr_str = "";

      for ( auto& [div,fzstr] : FZMap )
      {
         if ( i % div == 0 ) itr_str += fzstr;
      }

      if ( itr_str.empty() ) itr_str += std::to_string(i);

      sol += itr_str + " ";
   }

   return sol;
}
