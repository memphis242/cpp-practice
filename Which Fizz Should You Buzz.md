# Which Fizz Should You Buzz?
## Problem Statement
Generally, the problem statement goes something like (i being the number):
```
Print the numbers 1 through n with the following rules:
- "FizzBuzz" if i is divisible by 3 and 5.
- "Fizz" if i is divisible by 3.
- "Buzz" if i is divisible by 5.
- i itself if none of the above conditions are true.
```

## Design Considerations
Of course, part of the point of the map-based solution is to decouple the logic from some of its configuration/data - in this case, the set of divisors and their corresponding words to print. Generally, this is a good idea and makes code easier-to-change. That said, I value simplicity, and it feels unnatural to solve such a trivial problem statement with such abstractions. My vote goes to the naive solution, and the performance stats support that.

## Solutions
### Naive
```c++
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
```
### Map-Based (Interview-Style)
```c++
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

```

## Speed
I just called the functions above with a start of 1 and end of 100.
From [Google Benchmark](https://github.com/google/benchmark):
```bash
./bench.exe
2025-07-25T15:32:37-00:00
Running ./bench.exe
Run on (8 X 2419 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 1280 KiB (x4)
  L3 Unified 8192 KiB (x1)
------------------------------------------------------------
Benchmark                  Time             CPU   Iterations
------------------------------------------------------------
BM_FizzBuzz_Naive       3609 ns         3610 ns       194783
BM_FizzBuzz_Map         4642 ns         4653 ns       154483
```

## Memory Usage
### Stack
```
benchfcn1.cpp:3:13:std::string fizzbuzz_naive_solution(int, int)	192	static
benchfcn2.cpp:11:13:std::string fizzbuzz_map_solution(int, int)	416	static
```
### Heap
```
TODO
```
### Static
```
(none for fizzbuzz_naive_solution)
benchfcn2.cpp:4:41:void __tcf_ZL5FZMap()	64	static
```
