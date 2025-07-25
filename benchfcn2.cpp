#include <string>
#include <map>

static const std::map<int, std::string> FZMap =
{
   { 3, "Fizz" },
   { 5, "Buzz" }
};


std::string fizzbuzz_map_solution(int start, int end)
{
   // Assume start is less than or equal to end
   std::string sol = "";
   for ( int i = start; i <= end; i++ )
   {
      std::string itr_str = "";

      for ( auto& [div,fzstr] : FZMap )
      {
         if ( i % div == 0 ) itr_str.append(fzstr);
      }

      if ( itr_str.empty() ) itr_str.append( std::to_string(i) );

      sol += itr_str + " ";
   }

   return sol;
}
