// StaticMathLib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "StsticMathLib.h"

namespace StsticMathLib
{
#pragma region MATHAN
	/// <summary>
	/// выборочная средняя
	/// </summary>
	/// <param name="array"></param>
	/// <param name="length"></param>
	/// <returns></returns>
	float sample_average(std::vector<float>* array, std::vector<int>* average, int& length, int count) {
		float sum = 0;
		for (int i = 0; i < count; i++)
			sum += (*array)[i] * (float)(*average)[i];
		return sum / (float)length;
	}

	/// <summary>
	/// оценка дисперсии
	/// </summary>
	/// <param name="array"></param>
	/// <param name="mathexp"></param>
	/// <param name="length"></param>
	/// <returns></returns>
	float estimate_of_variance(std::vector<float>* array, float mathexp, int length) {
		int sum = 0;
		for (auto i : *array)
			sum += i;
		return powf((float)sum, 2.0) / (float)length;
	}

	float length_partial_interval(int range, int interval) {
		return (float)range / interval;
	}

	int range(int Xmin, int Xmax) {
		return Xmax - Xmin;
	}

	void round(float& val, int round_to) {
		val = int(val * round_to + 0.5) / (float)round_to;
	}

	int interval(int length) { //Sturges
		return 1 + (3.322 * (int(log10(length) * 1000 + 0.5) / 1000.0));
	}

	float mid_interval(float& interval_from, float& interval_to) {
		return int(((interval_from + interval_to) / 2.0) * 100 + 0.5) / 100.0;
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
		int counter = 0;
		for (auto i : *val)
		{
			cout << "arr[" << counter << "] = " << i << endl;
			counter++;
		}
	}

	template <class T> void show(T* val, std::string info) {
		cout << "==> " << info << ": ";
		for (auto i : *val)
		{
			cout << i << " ";
		}
		cout << endl;
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
		std::vector<Range> array;
		float _xmin = (float)X_min, _xmax = 0;
		for (int i = 0; i < interval; i++)
		{
			_xmax = _xmin + part_interval;
			round(_xmax, 100);
			Range _range(_xmin, _xmax);
			array.push_back(_range);
			_xmin = _xmax;
		}
		return array;
	}

	/// <summary>
	/// подсчитывает количество чисел в промежутках
	/// </summary>
	/// <param name="ranges"></param>
	/// <param name="array"></param>
	/// <returns></returns>
	std::vector<int> average_array(std::vector<Range>* ranges, std::vector<int>* array) {
		std::vector<int> arr;
		int counter = 0;
		for (auto iterator = ranges->begin(); iterator != ranges->end(); iterator++)
		{
			for (auto iter = array->begin(); iter != array->end(); iter++)
				if (*iterator == *iter)
					counter++;
			arr.push_back(counter);
			counter = 0;
		}
		return arr;
	}

	/// <summary>
	/// усредняет интервалы
	/// </summary>
	/// <param name="ranges"></param>
	/// <returns></returns>
	std::vector<float> mid_ranged_array(std::vector<Range>* ranges) {
		std::vector<float> array;
		for (auto iterator = ranges->begin(); iterator != ranges->end(); iterator++)
			array.push_back(iterator->middle);
		return array;
	} // here allocating memory for *array back in stack

	/// <summary>
	/// относительные частоты попадания случайной величины в i-тый интервал
	/// </summary>
	/// <param name="averages"></param>
	/// <param name="count"></param>
	/// <returns></returns>
	std::vector<float> relative_frequency_array(std::vector<int>* averages, int& count)
	{
		int num = 0;
		float wi = 0.0;
		std::vector<float> array;
		for (std::vector<int>::iterator iterator = averages->begin(); iterator != averages->end(); iterator++)
		{
			num = *iterator;
			wi = (float)num / count;
			array.push_back(wi);
		}
		return array;
	}

	/// <summary>
	/// вычисляет накопленные относительные частоты
	/// </summary>
	/// <param name="rel_freq"></param>
	/// <param name="interval"></param>
	/// <returns></returns>
	std::vector<float> accum_relative_frequencyF(std::vector<float>* rel_freq, int& interval) {
		std::vector<float>array;
		float sum = 0;
		array.push_back(0);
		for (int i = 0; i < interval - 1; i++)
		{
			sum += (*rel_freq)[i];
			array.push_back(sum);
		}
		return array;
	}

	/// <summary>
	/// генерирует массив для построения гистрограммы
	/// </summary>
	/// <param name="averages"></param>
	/// <param name="count"></param>
	/// <returns></returns>
	std::vector<float> histogram_array(std::vector<float>* rel_freq, float& h)
	{
		float hist = 0.0, num = 0.0;
		std::vector<float> array;
		for (std::vector<float>::iterator iterator = rel_freq->begin(); iterator != rel_freq->end(); iterator++)
		{
			num = *iterator;
			hist = num / h;
			array.push_back(hist);
		}
		return array;
	}
#pragma endregion

#pragma region sort
	int find_min(std::vector<int>* array, int& count) {
		int min = 1000;
		for (int i = 0; i < count; i++)
			if ((*array)[i] < min) min = (*array)[i];
		return min;
	}

	int find_max(std::vector<int>* array, int& count) {
		int max = 0;
		for (int i = 0; i < count; i++)
			if ((*array)[i] > max) max = (*array)[i];
		return max;
	}
#pragma endregion

	//GENERATOR UNIFORM CONTINUOUS RANDOM VARIABLES
	std::vector<int> gen_normal(int& range_from, int& range_to, int& length) {
		std::random_device                       rand_dev;
		std::mt19937                             generator(rand_dev());
		std::uniform_int_distribution<int>       distr(range_from, range_to);
		std::vector<int> array;
		for (int i = 0; i < length; i++)
			array.push_back(distr(generator));
		return array;
	}
}
