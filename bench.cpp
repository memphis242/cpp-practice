#include <iostream>
#include <map>
#include <string>
#include <benchmark/benchmark.h>

extern std::string fizzbuzz_naive_solution(int start, int end);
extern std::string fizzbuzz_map_solution(int start, int end);

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
