#include "pch.h"
#include "SysOfEqui.h"

void SysOfEqui::set_AOE(CString input)
{
	HowManyEquals = _ttoi(input);
}

void SysOfEqui::add_equal(CString input)
{
	AllEquals.push_back(input);
}

double SysOfEqui::parse_from_str()
{
	for (int i = 0; i < AllEquals.size(); i++)
	{
		result = parse_one_equal(AllEquals[i]);
	}
	return result;
}


double SysOfEqui::from_digits_to_counter(std::vector<int> InputDigits)
{
	part = 0;
	for (int i = 0; i < InputDigits.size(); i++) {
		part += InputDigits[i] * int(pow(10, InputDigits.size() - i - 1));
	}
	return part;
}

void SysOfEqui::make_oper_first()
{
	SubResult = 0; // промежуточный результат
	index = 0;

	/*Операции двух переменных (+, -, *, /, ^) выполняются по единому шаблону. Меняется только сам знак*/

	while (index < signs.size())
	{
		if (signs[index][0] == '^')
		{
			SubResult = pow(counters[index], counters[index + 1]);
			counters[index + 1] = SubResult;  // сразу на месте одонго из составляющих посчитанного
											  // выражения записываем ответ
			counters.erase(counters.begin() + index); // а второе удаляем, так как оно больше не нужно
			signs.erase(signs.begin() + index); // использованный знак (функцию) также удаляем
		}
		else
		{
			switch (signs[index][0])
			{
			case 's':
			{
				counters[index] = sin(counters[index] * PI/180); // переводим из град в рад
				signs.erase(signs.begin() + index);
			}; break;
			case 't':
			{
				counters[index] = tan(counters[index] * PI / 180);
				signs.erase(signs.begin() + index);
			}; break;
			case 'l':
			{
				counters[index] = log(counters[index]);
				signs.erase(signs.begin() + index);
			}; break;
			case 'c':
			{
				if (signs[index][1] == 'o')
				{
					counters[index] = cos(counters[index] * PI / 180);
				}
				else
				{
					counters[index] = 1/tan(counters[index] * PI / 180);
				}
				signs.erase(signs.begin() + index);
			}; break;
			default: index++; // только в том случае, если встреченный символ имеет меньший приоритет,
							  // мы увеличиваем индекс текущего элемента. В обратном случае не увеличиваем
							  // так как из-за удаления символа нумерация сдвигается на 1 назад
			}
		}
	}
	out = counters[counters.size() - 1]; // в результате запишем последнее число, так как если нет
										 // операций низшего приоритета, то оно в массиве будет
										 // единственным и будет являться конечным результатом
}

void SysOfEqui::make_oper_second()
{
	SubResult = 0;
	index = 0;

	while (index < signs.size())
	{
		if (signs[index][0] == '*')
		{
			SubResult = counters[index] * counters[index + 1];
			counters[index + 1] = SubResult;
			counters.erase(counters.begin() + index);
			signs.erase(signs.begin() + index);
		}
		else {
			if (signs[index][0] == '/')
			{
				SubResult = counters[index] / counters[index + 1];
				counters[index + 1] = SubResult;
				counters.erase(counters.begin() + index);
				signs.erase(signs.begin() + index);
			}
			else
			{
				index++;
			}
		}
	}
	out = counters[counters.size() - 1];
}

void SysOfEqui::make_oper_third()
{
	SubResult = 0;
	index = 0;

	while (index < signs.size())
	{
		if (signs[index][0] == '+')
		{
			SubResult = counters[index] + counters[index + 1];
			counters[index + 1] = SubResult;
			counters.erase(counters.begin() + index);
			signs.erase(signs.begin() + index);
		}
		else {
			if (signs[index][0] == '-')
			{
				SubResult = counters[index] - counters[index + 1];
				counters[index + 1] = SubResult;
				counters.erase(counters.begin() + index);
				signs.erase(signs.begin() + index);
			}
			else
			{
				index++;
			}
		}
	}
	out = counters[counters.size() - 1];
}


double SysOfEqui::parse_one_equal(CString equal)
{
	AmountOfFunc = 0;

	for (int i = 0; i < equal.GetLength(); i++)
	{
		switch (equal[i])
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			digits.push_back(_ttoi(CString(equal[i]))); // добавляем цифры в массив для цифр
		}; break;
		case '+':
		case '-':
		case '*':
		case '/':
		{
			// когда встречается знак действия, преобразуем цифры в многозначное число
			signs.push_back(CString(equal[i]));
			counters.push_back(from_digits_to_counter(digits));
			digits.clear();

		}; break;
		case '^': // power
		{
			// необходимо учесть то, что тригонометрические функции принимают ОДИН аргумент,
			// а одна алгебраическая операция "принимает на себя" ДВА числа
			HelperStr.Format(_T("%d"), (signs.size() - AmountOfFunc));
			signs.push_back(CString(equal[i] + HelperStr));
			counters.push_back(from_digits_to_counter(digits));
			digits.clear();
		}; break;
		case 's': // sin
		case 't': // tg
		case 'l': // ln
		{
			signs.push_back(CString(equal[i]));
			AmountOfFunc++;
		}; break;
		case 'c': // cos or ctg
		{
			if (equal[i + 1] == 'o') // cos
			{
				signs.push_back(CString(equal[i]) + _T("o"));
			}
			else // ctg
			{
				signs.push_back(CString(equal[i]) + _T("t"));
			}
			AmountOfFunc++;
			i += 2; // пропускаем s на конце cos, чтобы не принять ее за начало sin
		}; break;
		}
	}
	counters.push_back(from_digits_to_counter(digits));

	make_oper_first(); // действия первого приоритета (sin, cos, tg, ^)
	make_oper_second(); // действия второго приоритета (*, /)
	make_oper_third(); // действия третьего приоритета (+, -)

	return out;
}
