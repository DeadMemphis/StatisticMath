// StatisticMath.h - Contains declarations of math functions
#include <vector>
#pragma once

#ifdef STATISTICMATH_EXPORTS
#define STATISTICMATH_API __declspec(dllexport)
#else
#define STATISTICMATH_API __declspec(dllimport)
#endif

//Description TODO

// The Fibonacci recurrence relation describes a sequence F
// where F(n) is { n = 0, a
//               { n = 1, b
//               { n > 1, F(n-2) + F(n-1)
// for some initial integral values a and b.
// If the sequence is initialized F(0) = 1, F(1) = 1,
// then this relation produces the well-known Fibonacci
// sequence: 1, 1, 2, 3, 5, 8, 13, 21, 34, ...

extern "C" STATISTICMATH_API void sample_average(std::vector<float>* array, std::vector<int>* average, int& length, int count);