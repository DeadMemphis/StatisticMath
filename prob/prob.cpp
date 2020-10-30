#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;



#pragma region MATHAN
/// <summary>
/// выборочная средняя
/// </summary>
/// <param name="array"></param>
/// <param name="length"></param>
/// <returns></returns>
float sample_average(vector<float>* array, vector<int>* average, int& length, int count) {
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
float estimate_of_variance(vector<float>* array, float mathexp, int length) {
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

template <class T> void show(T* val, string info) {
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
vector<Range> ranged_array(float& part_interval, int& interval, int& X_min){
	vector<Range> array;
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
vector<int> average_array(vector<Range>* ranges, vector<int>* array){
	vector<int> arr;
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
vector<float> mid_ranged_array(vector<Range>* ranges){
	vector<float> array;
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
vector<float> relative_frequency_array(vector<int>* averages, int& count)
{
	int num = 0;
	float wi = 0.0;
	vector<float> array;
	for (vector<int>::iterator iterator = averages->begin(); iterator != averages->end(); iterator++)
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
vector<float> accum_relative_frequencyF(vector<float>* rel_freq, int& interval) {
	vector<float>array;
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
vector<float> histogram_array(vector<float>* rel_freq, float& h)
{
	float hist = 0.0, num = 0.0;
	vector<float> array;
	for (vector<float>::iterator iterator = rel_freq->begin(); iterator != rel_freq->end(); iterator++)
	{
		num = *iterator;
		hist = num / h;
		array.push_back(hist);
	}
	return array;
}
#pragma endregion

#pragma region sort
int find_min(vector<int>* array, int& count) {
	int min = 1000;
	for (int i = 0; i < count; i++)
		if ((*array)[i] < min) min = (*array)[i];
	return min;
}

int find_max(vector<int>* array, int& count) {
	int max = 0;
	for (int i = 0; i < count; i++)
		if ((*array)[i] > max) max = (*array)[i];
	return max;
}
#pragma endregion

//GENERATOR UNIFORM CONTINUOUS RANDOM VARIABLES
vector<int> gen_normal(int& range_from, int& range_to, int& length){
	random_device                       rand_dev;
	mt19937                             generator(rand_dev());
	uniform_int_distribution<int>       distr(range_from, range_to);
	vector<int> array;
	for (int i = 0; i < length; i++)
		array.push_back(distr(generator));
	return array;
}

int main()
{
#pragma region values
	
	vector<int> arr;
	vector<Range> ranged;
	vector<int> average_ranged;
	vector<float> mid_ranged;
	vector<float> relative_frequency;
	vector<float> accum_relative_frequency;
	vector<float> histogram;

	
	int range_from = 150;
	int range_to = 185;
	int count = 50;
	int Xmin = 0;
	int Xmax = 0;
	int counter = 0;
	int _interval = 0;
	
	float  mexp = 0.0;
	float part_intervalf = 0.0;
	float interval_from = 0.0;
	float interval_to = 0.0;
	float _mid_interval = 0.0;
	float current = 0.0;
	float wi = 0.0;
	float histf = 0.0;
#pragma endregion

#pragma region init
	arr = gen_normal(range_from, range_to, count);
	show(&arr);

	Xmin = find_min(&arr, count);
	Xmax = find_max(&arr, count);
	cout << " ==> Xmax = " << Xmax << endl << " ==> Xmin = " << Xmin << endl;
	
	sort(arr.begin(), arr.end());
	
	_interval = interval(count);
	cout << " ==> interval = " << _interval << endl;
	
	part_intervalf = length_partial_interval(range(Xmin, Xmax), _interval);
	round(part_intervalf, 100);
	cout << " ==> length = " << part_intervalf << endl;
	
	show(&arr);

	ranged = ranged_array(part_intervalf, _interval, Xmin);
	
	average_ranged = average_array(&ranged, &arr);
	show(&average_ranged, "average");
	
	mid_ranged = mid_ranged_array(&ranged);
	show(&mid_ranged, "mid_ranged");

	relative_frequency = relative_frequency_array(&average_ranged, count);
	show(&relative_frequency, "relative_frequency");
	
	accum_relative_frequency = accum_relative_frequencyF(&relative_frequency, _interval);
	show(&accum_relative_frequency, "accum_freq");
	
	histogram = histogram_array(&relative_frequency, part_intervalf);
	show(&histogram, "histogram");
#pragma endregion

	

	//interval_from = interval_to = Xmin;
	//for (int i = 0; i < _interval; i++)
	//{
	//	interval_to += part_intervalf;
	//	for (int j = 0; j < count; j++)
	//		/*if ((float)(*arr)[j] >= interval_from && (float)(*arr)[j] <= interval_to)
	//			counter += 1;*/
	//		
	//	aver_array->push_back((float)counter);
	//	round(interval_to, 100);
	//	_mid_interval = mid_interval(interval_from, interval_to);
	//	mid_intervals->push_back(_mid_interval);
	//	wi = (float)counter / count;
	//	relative_frequency->push_back(wi);
	//	round((histf = wi / part_intervalf), 1000);
	//	frequency_hist_array->push_back(histf);
	//	cout << "==> number of values for interval from " << interval_from
	//		<< " to " << interval_to << " is " << counter << endl << "==> mid-interval = " << (*mid_intervals)[i] << endl;
	//	interval_from = interval_to;
	//	counter = 0;
	//}

	//accum_relative_frequency->push_back(0);
	//for (int i = 0; i < _interval - 1; i++)
	//{
	//	current += (*relative_frequency)[i];
	//	accum_relative_frequency->push_back(current);
	//}

		
	
	
	mexp = sample_average(&mid_ranged, &average_ranged, count, mid_ranged.size());
	cout << "mathexp = " << mexp << endl;
	cout << "estimate of variance = " << estimate_of_variance(&mid_ranged, mexp, count) << endl;
	//clear

	system("PAUSE");
}