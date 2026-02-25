/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:49:27 by miaviles          #+#    #+#             */
/*   Updated: 2026/02/25 01:49:27 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <iostream>
#include <string>

/* ===========================
   Utility functions
=========================== */

template <typename T>
void printElement(const T &elem)
{
	std::cout << elem << " ";
}

void increment(int &n)
{
	n += 1;
}

void toUpper(char &c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
}

void printLine(const std::string &s)
{
	std::cout << s << std::endl;
}

void doubleValue(double &n)
{
	n *= 2;
}

/* ===========================
   MAIN TESTS
=========================== */

int main(void)
{
	/* ---------- TEST 1 ---------- */
	std::cout << "===== TEST 1: Integer array (print only) =====" << std::endl;
	int numbers[] = {1, 2, 3, 4, 5};
	size_t size = sizeof(numbers) / sizeof(numbers[0]);

	iter(numbers, size, printElement<int>);
	std::cout << "\n" << std::endl;


	/* ---------- TEST 2 ---------- */
	std::cout << "===== TEST 2: Integer array (modify values) =====" << std::endl;

	std::cout << "Before increment: ";
	iter(numbers, size, printElement<int>);
	std::cout << std::endl;

	iter(numbers, size, increment);

	std::cout << "After increment:  ";
	iter(numbers, size, printElement<int>);
	std::cout << "\n" << std::endl;


	/* ---------- TEST 3 ---------- */
	std::cout << "===== TEST 3: Double array =====" << std::endl;
	double doubles[] = {1.1, 2.2, 3.3};
	size_t dsize = sizeof(doubles) / sizeof(doubles[0]);

	iter(doubles, dsize, printElement<double>);
	std::cout << "\n" << std::endl;


	/* ---------- TEST 4 ---------- */
	std::cout << "===== TEST 4: Char array (modify to uppercase) =====" << std::endl;
	char letters[] = {'a', 'b', 'c', 'd'};
	size_t lsize = sizeof(letters) / sizeof(letters[0]);

	std::cout << "Before toUpper: ";
	iter(letters, lsize, printElement<char>);
	std::cout << std::endl;

	iter(letters, lsize, toUpper);

	std::cout << "After toUpper:  ";
	iter(letters, lsize, printElement<char>);
	std::cout << "\n" << std::endl;


	/* ---------- TEST 5 ---------- */
	std::cout << "===== TEST 5: String array =====" << std::endl;
	std::string words[] = {"hello", "42", "templates"};
	size_t wsize = sizeof(words) / sizeof(words[0]);

	iter(words, wsize, printLine);
	std::cout << std::endl;


	/* ---------- TEST 6 ---------- */
	std::cout << "===== TEST 6: Const array =====" << std::endl;
	const int constNumbers[] = {10, 20, 30};
	size_t csize = sizeof(constNumbers) / sizeof(constNumbers[0]);

	iter(constNumbers, csize, printElement<int>);
	std::cout << "\n" << std::endl;


	/* ---------- TEST 7 ---------- */
	std::cout << "===== TEST 7: Empty array (portable) =====" << std::endl;
	int *emptyArray = NULL;
	iter(emptyArray, 0, printElement<int>);
	std::cout << "No crash on empty array ✔" << std::endl << std::endl;


	/* ---------- TEST 8 ---------- */
	std::cout << "===== TEST 8: Modify double array =====" << std::endl;
	double toDouble[] = {1.5, 2.5, 3.5};
	size_t dtsize = sizeof(toDouble) / sizeof(toDouble[0]);

	std::cout << "Before doubleValue: ";
	iter(toDouble, dtsize, printElement<double>);
	std::cout << std::endl;

	iter(toDouble, dtsize, doubleValue);

	std::cout << "After doubleValue:  ";
	iter(toDouble, dtsize, printElement<double>);
	std::cout << "\n" << std::endl;


	/* ---------- TEST 9 ---------- */
	std::cout << "===== TEST 9: Single element array =====" << std::endl;
	int single[] = {42};
	iter(single, 1, printElement<int>);
	std::cout << "\n" << std::endl;

	return (0);
}