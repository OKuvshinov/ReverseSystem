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
	SubResult = 0; // ������������� ���������
	index = 0;

	/*�������� ���� ���������� (+, -, *, /, ^) ����������� �� ������� �������. �������� ������ ��� ����*/

	while (index < signs.size())
	{
		if (signs[index][0] == '^')
		{
			SubResult = pow(counters[index], counters[index + 1]);
			counters[index + 1] = SubResult;  // ����� �� ����� ������ �� ������������ ������������
											  // ��������� ���������� �����
			counters.erase(counters.begin() + index); // � ������ �������, ��� ��� ��� ������ �� �����
			signs.erase(signs.begin() + index); // �������������� ���� (�������) ����� �������
		}
		else
		{
			switch (signs[index][0])
			{
			case 's':
			{
				counters[index] = sin(counters[index] * PI/180); // ��������� �� ���� � ���
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
			default: index++; // ������ � ��� ������, ���� ����������� ������ ����� ������� ���������,
							  // �� ����������� ������ �������� ��������. � �������� ������ �� �����������
							  // ��� ��� ��-�� �������� ������� ��������� ���������� �� 1 �����
			}
		}
	}
	out = counters[counters.size() - 1]; // � ���������� ������� ��������� �����, ��� ��� ���� ���
										 // �������� ������� ����������, �� ��� � ������� �����
										 // ������������ � ����� �������� �������� �����������
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
			digits.push_back(_ttoi(CString(equal[i]))); // ��������� ����� � ������ ��� ����
		}; break;
		case '+':
		case '-':
		case '*':
		case '/':
		{
			// ����� ����������� ���� ��������, ����������� ����� � ������������ �����
			signs.push_back(CString(equal[i]));
			counters.push_back(from_digits_to_counter(digits));
			digits.clear();

		}; break;
		case '^': // power
		{
			// ���������� ������ ��, ��� ������������������ ������� ��������� ���� ��������,
			// � ���� �������������� �������� "��������� �� ����" ��� �����
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
			i += 2; // ���������� s �� ����� cos, ����� �� ������� �� �� ������ sin
		}; break;
		}
	}
	counters.push_back(from_digits_to_counter(digits));

	make_oper_first(); // �������� ������� ���������� (sin, cos, tg, ^)
	make_oper_second(); // �������� ������� ���������� (*, /)
	make_oper_third(); // �������� �������� ���������� (+, -)

	return out;
}
