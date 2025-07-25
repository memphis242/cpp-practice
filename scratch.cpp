#include <iostream>
#include <map>
#include <string>
#include <benchmark/benchmark.h>

std::string fizzbuzz_naive_solution(int start, int end);
std::string fizzbuzz_map_solution(int start, int end);

static void BM_FizzBuzz_Naive(benchmark::State& state)
{
   std::string sol;
   for ( auto _ : state )
   {
      sol = fizzbuzz_naive_solution(1, 100);
   }
}

static void BM_FizzBuzz_Map(benchmark::State& state)
{
   std::string sol;
   for ( auto _ : state )
   {
      sol = fizzbuzz_map_solution(1, 100);
   }
}

BENCHMARK(BM_FizzBuzz_Naive);
BENCHMARK(BM_FizzBuzz_Map);
// TODO: Benchmark with many well chosen start and end points
//BENCHMARK(BM_FizzBuzz_MapSol)->Ranges({{1, 1<<10}, {128, 512}});

//int main(void)
//{
//   auto println = [](){ std::cout << '\n'; };
//   std::string sol;
//
//   sol = fizzbuzz_map_solution(1, 100);
//   std::cout << sol;
//   println();
//}

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
         if ( i % div == 0 ) itr_str.append(fzstr);
      }

      if ( itr_str.empty() ) itr_str.append( std::to_string(i) );

      sol += itr_str + " ";
   }

   return sol;
}
