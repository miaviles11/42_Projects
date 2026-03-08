/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:16:14 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/08 01:30:35 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

void testSubjectExample()
{
	std::cout << "\n===== SUBJECT TEST =====" << std::endl;

	Span sp(5);

	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span : " << sp.longestSpan() << std::endl;
}

void testOverflow()
{
	std::cout << "\n===== TEST OVERFLOW =====" << std::endl;

	Span sp(3);

	sp.addNumber(1);
	sp.addNumber(2);
	sp.addNumber(3);

	try
	{
		sp.addNumber(4);
	}
	catch (std::exception &e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
}

void testTooFew()
{
	std::cout << "\n===== TEST TOO FEW NUMBERS =====" << std::endl;

	Span sp(5);

	try
	{
		std::cout << sp.shortestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "ShortestSpan exception: " << e.what() << std::endl;
	}

	sp.addNumber(42);

	try
	{
		std::cout << sp.longestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "LongestSpan exception: " << e.what() << std::endl;
	}

	sp.addNumber(2);

	try
	{
		std::cout << sp.longestSpan() << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "LongestSpan exception: " << e.what() << std::endl;
	}
}

void testRandomNumbers()
{
	std::cout << "\n===== TEST RANDOM NUMBERS =====" << std::endl;

	Span sp(10);

	sp.addNumber(100);
	sp.addNumber(3);
	sp.addNumber(50);
	sp.addNumber(25);
	sp.addNumber(90);
	sp.addNumber(1);
	sp.addNumber(60);

	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span : " << sp.longestSpan() << std::endl;
}

void testAddRange()
{
	std::cout << "\n===== TEST ADD RANGE (10000 numbers) =====" << std::endl;

	Span sp(10000);

	std::vector<int> big;

	for (int i = 0; i < 10000; i++)
		big.push_back(i);

	sp.addRange(big.begin(), big.end());

	std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
	std::cout << "Longest span : " << sp.longestSpan() << std::endl;
}

int main()
{
	testSubjectExample();
	testOverflow();
	testTooFew();
	testRandomNumbers();
	testAddRange();

	return (0);
}