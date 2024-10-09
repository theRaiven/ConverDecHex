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
	{ "1111" , 'F' },
};
std::map<char, std::vector<int>> Hex_Bin_Table
{
	{ '0', {0, 0, 0, 0} },
	{ '1', {0, 0, 0, 1} },
	{ '2', {0, 0, 1, 0} },
	{ '3', {0, 0, 1, 1} },

	{ '4', {0, 1, 0, 0} },
	{ '5', {0, 1, 0, 1} },
	{ '6', {0, 1, 1, 0} },
	{ '7', {0, 1, 1, 1} },

	{ '8', {1, 0, 0, 0} },
	{ '9', {1, 0, 0, 1} },
	{ 'A', {1, 0, 1, 0} },
	{ 'B', {1, 0, 1, 1} },

	{ 'C', {1, 1, 0, 0} },
	{ 'D', {1, 1, 0, 1} },
	{ 'E', {1, 1, 1, 0} },
	{ 'F', {1, 1, 1, 1} }
};

auto ConvertBunary = [](vector<int>& binary_num_INT, vector<int>& binary_num_FRACT, const auto convert_num)
{
	int integer_part = move(fabs(convert_num)); 
	auto fractional_part = move(fabs(convert_num) - integer_part);


	int i{ 0 };
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
	
	ConvertBunary(binary_num_INT_mantissa, binary_num_FRACT_mantissa, convert_num);

	int Pc = binary_num_INT_mantissa.size() - 1 + (pow(2, is_same_v<decltype(convert_num), const double> ? 10 : 7) - 1);
	vector<int> binary_num_INT;
	vector<int> binary_num_FRACT;

	string hex_num;
	ConvertBunary(binary_num_INT, binary_num_FRACT, Pc);

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

auto ConvertDec(string convert_num)
{
	vector<int> binary_num;
	for (int i = 0; i < convert_num.size(); i++)
	{
		vector<int> temp = Hex_Bin_Table[convert_num[i]];
		for (const auto& c : temp)
		{
			binary_num.push_back(c);
		}
	}


	int NUMBER_SYSTEM = move(convert_num.size() == 8 ? 7 : 10);

	int Pc{ 0 };
	int size_integer_mantissa;

	int i; int j;
	for (i = 0; i < NUMBER_SYSTEM + 1; i++)
	{
		Pc += pow(2, NUMBER_SYSTEM - i) * binary_num[i + 1];
	}
	i++;
	size_integer_mantissa = move(Pc - (pow(2, NUMBER_SYSTEM) - 1));

	vector<int> binary_num_INT_mantissa{ 1 };
	vector<int> binary_num_FRACT_mantissa;

	for (j = move(i); j < i + size_integer_mantissa; j++)
	{
		binary_num_INT_mantissa.push_back(binary_num[j]);
	}
	i = move(j);
	for (; i < binary_num.size(); i++)
	{
		binary_num_FRACT_mantissa.push_back(binary_num[i]);
	}

	int integer_part{ 0 };
	for (i = 0; i < binary_num_INT_mantissa.size(); i++)
	{
		integer_part += pow(2, binary_num_INT_mantissa.size() - i - 1) * binary_num_INT_mantissa[i];
	}
	long double fract_part{ 0 };
	for (i = 0; i < binary_num_FRACT_mantissa.size(); i++)
	{
		fract_part += pow(2, - i - 1) * binary_num_FRACT_mantissa[i];
	}
	return (binary_num[0] <= 0 ? 1 : -1)*(integer_part + fract_part);
	
	
}

int main()
{
	setlocale(LC_ALL, "RUS");
	{
		double num0 { -285.563 };
		double num{ 437.938 };
		float num1{ 22.5078 };
		float num2{ -86.0156 };
		cout << ConvertHex(num0) << endl;
		cout << ConvertHex(num) << endl;
		cout << ConvertHex(num1) << endl;
		cout << ConvertHex(num2) << endl;
	}
	{
		string num{ "42B80000" };
		string num1{ "C2D62000" };
		string num2{ "407229C000000000" };
		string num3{ "C068C0C000000000" };
		cout << ConvertDec(num) << endl;
		cout << ConvertDec(num1) << endl;
		cout << ConvertDec(num2) << endl;
		cout << ConvertDec(num3);
	}

}

