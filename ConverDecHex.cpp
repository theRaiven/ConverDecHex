// ConverDecHex.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

std::map<std::string, char> Bin_Hex_Table
{
	{ "0000" , '0' },
	{ "0001" , '1' },
	{ "0010" , '2' },
	{ "0011" , '3'},

	{ "0100" , '4' },
	{ "0101" , '5' },
	{ "0110" , '6' },
	{ "0111" , '7' },

	{ "1000" , '8' },
	{ "1001" , '9' },
	{ "1010" , 'A' },
	{ "1011" , 'B' },

	{ "1100" , 'C' },
	{ "1101" , 'D' },
	{ "1110" , 'E' },
	{ "1111" , 'F' }
};

auto ConverBunary = [](vector<int>& binary_num_INT, vector<int>& binary_num_FRACT, const auto convert_num)
{
	int integer_part = move(fabs(convert_num)); 
	auto fractional_part = move(fabs(convert_num) - integer_part);


	int i = 0;
	while (integer_part >= 2)
	{
		binary_num_INT.push_back(integer_part % 2);
		integer_part /= 2;

		i++;
	}
	binary_num_INT.push_back(integer_part == 1 ? 1 : 0);
	reverse(binary_num_INT.begin(), binary_num_INT.end());

	i = 0;
	while (fractional_part > 0)
	{
		fractional_part *= 2;
		if (fractional_part >= 1)
		{
			fractional_part -= 1;
			
			binary_num_FRACT.push_back(1);
		}
		else
		{
			binary_num_FRACT.push_back(0);
		}

		i++;
		if (is_same_v<decltype(convert_num), const double>)
		{
			if (fractional_part == 0) 
			{
				binary_num_FRACT.push_back(0);
				break;
			}
		}
	}

};
auto ConvertHex = [](const auto convert_num)
{
	vector<int> binary_num_INT_mantissa;
	vector<int> binary_num_FRACT_mantissa;
	
	ConverBunary(binary_num_INT_mantissa, binary_num_FRACT_mantissa, convert_num);

	int Pc = binary_num_INT_mantissa.size() - 1 + (pow(2, is_same_v<decltype(convert_num), const double> ? 10 : 7) - 1);
	vector<int> binary_num_INT;
	vector<int> binary_num_FRACT;

	string hex_num;
	ConverBunary(binary_num_INT, binary_num_FRACT, Pc);

	vector<int> binary_num = { convert_num <= 0 ? 1 : 0 };
	for (int i = 0; i < binary_num_INT.size(); i++)
	{
		binary_num.push_back(binary_num_INT[i]);
	}
	for (int i = 1; i < binary_num_INT_mantissa.size() + binary_num_FRACT_mantissa.size(); i++)
	{
		binary_num.push_back(i < binary_num_INT_mantissa.size() ? binary_num_INT_mantissa[i] : binary_num_FRACT_mantissa[i - binary_num_INT_mantissa.size()]);
	}
	
	for (int i = 0; i < binary_num.size();)
	{
		string temp;
		while(temp.size() < 4)
		{
			temp += to_string(binary_num[i]);
			i++;
		}
		
		hex_num += (Bin_Hex_Table[temp]);

	}
	return hex_num;
};

int main()
{
	setlocale(LC_ALL, "RUS");
	double num0 = -285.563;
	double num = 437.938;
	float num1 = 22.5078;
	float num2 = -86.0156;
	cout << ConvertHex(num0) << endl;
	cout << ConvertHex(num) << endl;
	cout << ConvertHex(num1) << endl;
	cout << ConvertHex(num2) << endl;
	 //ConvertHex(num1);
}

