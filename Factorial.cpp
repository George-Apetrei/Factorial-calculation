#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>


std::vector<int> carry_over(std::vector<int> to_carry) {
	int size = to_carry.size();
	for (int i = 0; i < size; ++i) {
		while (to_carry[i] > 9) {
			to_carry[i] -= 10;
			if (i < to_carry.size() - 1) {
				 to_carry[i + 1] += 1;
			}
			else {
				to_carry.push_back(1);
			}
		}
	}
	return to_carry;
}

std::vector<int>vector_multiplication(std::vector<int> result, std::vector<int> factorial) {
	std::vector<std::vector<int>> array_of_multiplications;
	std::vector<int> holder;

		for (int j = 0; j < factorial.size(); ++j) {			//Goes through each digit of the multiplier and multiplies each of them with one of the digits of the result
			if (j+1 > 1) {												//If there are more than 1 digits to multiply
				for (int n = 0; n < j; ++n) {						//Shifts the result of multiplication vector 1 digit to the right so the multiplication is done correctly
					holder.push_back(0);
				}
			}
			for (int m = 0; m < result.size(); ++m) {				//Goes through each of the digits to be multiplied
				holder.push_back(result.at(m)*factorial.at(j));		//Pushes back the result in the holding array
			}
			array_of_multiplications.push_back(holder);				//Pushes the result into a vector of vectors
			holder.clear();											//Clears holding vector for next operations
		}
		result.clear();												//Clears container to ensure no errors with previous numbers
		int sum=0;
		if (array_of_multiplications.size() > 1){					//If there's more than 1 array to sum up

			for (int k = 0; k < array_of_multiplications[array_of_multiplications.size()-1].size(); ++k) {		//Goes through all the digits of the last vector of numbers. This vector has the most digits because of the 0s added at the beginning of it
				for (int o = 0; o < array_of_multiplications.size(); ++o) {										//Loop to sum the values of all digits at a certain index
					if (array_of_multiplications[o].size()-1 < k) {
						sum += 0;
					}
					else {
						sum += array_of_multiplications[o][k];														//save result of sum to variable
					}
				}
				result.push_back(sum);																			//Push back value into result array
				sum = 0;																						//Reset sum variable
			}
		}
		else {
			for (int p = 0; p < array_of_multiplications[0].size(); ++p) {
				result.push_back(array_of_multiplications[0][p]);
			}
		}
		array_of_multiplications.clear();
		result = carry_over(result);

	return result;
}

std::vector<int> calculate_factorial(int input) {
	std::vector<int> to_multiply;
	std::vector<int> multiplier;
	to_multiply.push_back(1);
	multiplier.push_back(2);
	for (int i = 0; i < input - 1; ++i) {
		to_multiply = vector_multiplication(to_multiply, multiplier);
		multiplier[0]++;
		multiplier = carry_over(multiplier);
	}
	return to_multiply;
}

void output_to_console(std::vector<int> factorial) {
	for (int i = 0; i < factorial.size(); ++i) {
		std::cout << factorial[factorial.size() - 1 - i];
	}
	std::cout << std::endl;
}

void output_to_file(std::vector<int> factorial) {
	std::ofstream out;
	out.open("data.txt");
	for (int i = 0; i < factorial.size(); ++i) {
		out << factorial[factorial.size() - 1 - i];
	}
	out << std::endl;
	out.close();
}

int main()
{

	int input;
	std::cout << "Input the factorial to be calculated:\n";
	std::cin >> input;
	std::cout << std::endl;
	std::vector<int> factorial = calculate_factorial(input);
	output_to_console(factorial);
	output_to_file(factorial);
	std::cout << std::endl;
	std::cout << "Input anything to exit:\n";
	std::cin >> input;
    return 0;
}
