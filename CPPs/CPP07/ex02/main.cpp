/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:58:45 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/03 14:13:16 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"
#include <iostream>
#include <string>

/* Utility function to print Array */
template <typename T>
void printArray(const Array<T>& arr, const std::string& name)
{
	std::cout << name << " (size = " << arr.size() << "): ";
	for (size_t i = 0; i < arr.size(); i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

int main()
{
	std::cout << "========== DEFAULT CONSTRUCTOR ==========" << std::endl;
	Array<int> empty;
	std::cout << "Empty size: " << empty.size() << std::endl;


	std::cout << "\n========== CONSTRUCTOR WITH SIZE ==========" << std::endl;
	Array<int> numbers(5);
	for (size_t i = 0; i < numbers.size(); i++)
		numbers[i] = i * 10;
	printArray(numbers, "numbers");


	std::cout << "\n========== OPERATOR[] MODIFICATION ==========" << std::endl;
	numbers[2] = 999;
	printArray(numbers, "numbers after modification");


	std::cout << "\n========== COPY CONSTRUCTOR ==========" << std::endl;
	Array<int> copy(numbers);
	printArray(copy, "copy");

	std::cout << "Modifying copy..." << std::endl;
	copy[0] = 1111;

	printArray(copy, "copy");
	printArray(numbers, "original numbers (should be unchanged)");


	std::cout << "\n========== ASSIGNMENT OPERATOR ==========" << std::endl;
	Array<int> assigned;
	assigned = numbers;
	printArray(assigned, "assigned");

	std::cout << "Modifying assigned..." << std::endl;
	assigned[1] = 2222;

	printArray(assigned, "assigned");
	printArray(numbers, "original numbers (should be unchanged)");

	std::cout << "\n========== CONST ACCESS ==========" << std::endl;
	const Array<int> constArray(numbers);
	printArray(constArray, "constArray");


	std::cout << "\n========== OUT OF RANGE TEST ==========" << std::endl;
	try
	{
		std::cout << numbers[42] << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}


	std::cout << "\n========== STRING ARRAY TEST ==========" << std::endl;
	Array<std::string> words(3);
	words[0] = "Hello";
	words[1] = "Templates";
	words[2] = "42";
	printArray(words, "words");


	std::cout << "\n========== DOUBLE ARRAY TEST ==========" << std::endl;
	Array<double> doubles(4);
	for (size_t i = 0; i < doubles.size(); i++)
		doubles[i] = i + 0.5;
	printArray(doubles, "doubles");


	std::cout << "\n========== ZERO SIZE CONSTRUCTION ==========" << std::endl;
	Array<int> zero(0);
	std::cout << "Zero size array size: " << zero.size() << std::endl;


	std::cout << "\n========== DESTRUCTION TEST ==========" << std::endl;
	{
		Array<int> temp(3);
		temp[0] = 7;
		temp[1] = 8;
		temp[2] = 9;
		printArray(temp, "temp");
	}
	std::cout << "Temp destroyed successfully (no leaks if valgrind clean)" << std::endl;

	return 0;
}
