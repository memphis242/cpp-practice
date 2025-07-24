#include <iostream>
#include <string>
#include <map>

static const std::map<int, std::string> fzmap =
{
   { 3, "Fizz" },
   { 5, "Buzz" }
};

int main(void)
{
   const int start = 1;
   const int end   = 100;

   std::string outstr = "";
   for ( int i = start; i <= end; i++ )
   {
      std::string str = "";
      for ( const auto& [div, fzstr] : fzmap )
      {
         if ( i % div == 0 ) str += fzstr;
      }
      if ( str.empty() ) str += std::to_string(i);
      outstr += str;
      outstr += ' ';
   }
   
   std::cout << outstr << std::endl;
}
