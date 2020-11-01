//StsticMathLib.h
#pragma once

#pragma region Includings
#include <vector>
#include <iostream>
#include <random>
#pragma endregion

namespace StsticMathLib
{

#pragma region MATHAN
	float sample_average(std::vector<float>* array, std::vector<int>* average, int& length, int count);
	float estimate_of_variance(std::vector<float>* array, float mathexp, int length);
	float length_partial_interval(int range, int interval);
	int range(int Xmin, int Xmax);
	void round(float& val, int round_to);
	int interval(int length);
	float mid_interval(float& interval_from, float& interval_to);
#pragma endregion

#pragma region support structures
	struct Range;
#pragma endregion

#pragma region display func
	template <class T> void show(T* val);
	template <class T> void show(T* val, std::string info);
#pragma endregion

#pragma region array generators
	std::vector<Range> ranged_array(float& part_interval, int& interval, int& X_min);
	std::vector<int> average_array(std::vector<Range>* ranges, std::vector<int>* array);
	std::vector<float> mid_ranged_array(std::vector<Range>* ranges);
	std::vector<float> relative_frequency_array(std::vector<int>* averages, int& count);
	std::vector<float> accum_relative_frequencyF(std::vector<float>* rel_freq, int& interval);
	std::vector<float> histogram_array(std::vector<float>* rel_freq, float& h);
#pragma endregion

#pragma region sort
	int find_min(std::vector<int>* array, int& count);
	int find_max(std::vector<int>* array, int& count);
#pragma endregion

}

