#pragma once

#include <vector>

#define PI 3.141592

class SysOfEqui
{
public:
	void set_AOE(CString input);
	void add_equal(CString input);
	double parse_from_str();

private:
	int HowManyEquals;
	std::vector<CString> AllEquals;
	int part = 0;
	unsigned int index = 0;
	std::vector<int> digits;
	std::vector<double> counters;
	std::vector<CString> signs;
	double parse_one_equal(CString equal);
	double from_digits_to_counter(std::vector<int> InputDigits);
	double result;
	double out;
	void make_oper_first();
	void make_oper_second();
	void make_oper_third();
	double SubResult = 0;
	int AmountOfFunc = 0;
	CString HelperStr;
};















//void SysOfEqui::make_oper_third()
//{
//	SubResult = 0;
//	CountersDelets = 0;
//	index = 0;
//	while (index < signs.size())
//		//for (int i = 0; i < signs.size(); i++)
//	{
//		if (signs[index][0] == '+')
//		{
//			SubResult = counters[index/*- CountersDelets + SignsDelets*/] + counters[index + 1/*- CountersDelets + SignsDelets*/];
//			counters[index + 1/* - CountersDelets + SignsDelets*/] = SubResult;
//			counters.erase(counters.begin() + index/* - CountersDelets + SignsDelets*/);
//			//CountersDelets++;
//			//SignsDelets++;
//			signs.erase(signs.begin() + index);
//		}
//		else {
//		if (signs[index][0] == '-')
//		{
//			SubResult = counters[index/*- CountersDelets + SignsDelets*/] - counters[index + 1/*- CountersDelets + SignsDelets*/];
//			counters[index + 1/* - CountersDelets + SignsDelets*/] = SubResult;
//			counters.erase(counters.begin() + index/* - CountersDelets + SignsDelets*/);
//			//CountersDelets++;
//			//SignsDelets++;
//			signs.erase(signs.begin() + index);
//		}
//		else
//		{
//			index++;
//		}
//		}
//	}
//	out = counters[counters.size() - 1];
//}*/

