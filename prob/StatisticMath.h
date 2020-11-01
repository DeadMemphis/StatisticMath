//StatisticMath.h
#pragma once

#pragma region Includings

#include <vector>
#include <iostream>

#pragma endregion

#pragma region MATHAN

/// <summary>
/// выборочная средняя
/// </summary>
/// <param name="array"></param>
/// <param name="length"></param>
/// <returns></returns>
float sample_average(std::vector<float>* array, std::vector<int>* average, int& length, int count) {

}

/// <summary>
/// оценка дисперсии
/// </summary>
/// <param name="array"></param>
/// <param name="mathexp"></param>
/// <param name="length"></param>
/// <returns></returns>
float estimate_of_variance(std::vector<float>* array, float mathexp, int length) {

}

float length_partial_interval(int range, int interval) {

}

int range(int Xmin, int Xmax) {

}

void round(float& val, int round_to) {

}

int interval(int length) {

}

float mid_interval(float& interval_from, float& interval_to) {

}

#pragma endregion

#pragma region support structures

struct Range
{
public:
	float range_from = 0.0;
	float range_to = 0.0;
	float middle = 0.0;
	Range(float val_from, float val_to)
	{
		this->range_from = val_from;
		this->range_to = val_to;
		this->middle = mid_interval();
	}
private:

	float mid_interval() {
		return int(((this->range_from + this->range_to) / 2.0) * 100 + 0.5) / 100.0;
	}
};

bool operator == (Range range, int val)
{
	return val >= range.range_from && val <= range.range_to;
}

#pragma endregion

#pragma region display func

template <class T> void show(T* val) {

}

template <class T> void show(T* val, std::string info) {

}

#pragma endregion

#pragma region array generators

/// <summary>
/// содержит в себе интервалы чисел, равных количество промежутков, вычичляемых по формуле Стерджеса
/// </summary>
/// <param name="part_interval"></param>
/// <param name="interval"></param>
/// <param name="X_min"></param>
/// <returns></returns>
std::vector<Range> ranged_array(float& part_interval, int& interval, int& X_min) {

}

/// <summary>
/// подсчитывает количество чисел в промежутках
/// </summary>
/// <param name="ranges"></param>
/// <param name="array"></param>
/// <returns></returns>
std::vector<int> average_array(std::vector<Range>* ranges, std::vector<int>* array) {

}

/// <summary>
/// усредняет интервалы
/// </summary>
/// <param name="ranges"></param>
/// <returns></returns>
std::vector<float> mid_ranged_array(std::vector<Range>* ranges) {

} // here allocating memory for *array back in stack

/// <summary>
/// относительные частоты попадания случайной величины в i-тый интервал
/// </summary>
/// <param name="averages"></param>
/// <param name="count"></param>
/// <returns></returns>
std::vector<float> relative_frequency_array(std::vector<int>* averages, int& count) {

}

/// <summary>
/// вычисляет накопленные относительные частоты
/// </summary>
/// <param name="rel_freq"></param>
/// <param name="interval"></param>
/// <returns></returns>
std::vector<float> accum_relative_frequencyF(std::vector<float>* rel_freq, int& interval) {

}

/// <summary>
/// генерирует массив для построения гистрограммы
/// </summary>
/// <param name="averages"></param>
/// <param name="count"></param>
/// <returns></returns>
std::vector<float> histogram_array(std::vector<float>* rel_freq, float& h) {

}

#pragma endregion

#pragma region sort

int find_min(std::vector<int>* array, int& count) {

}

int find_max(std::vector<int>* array, int& count) {

}

#pragma endregion