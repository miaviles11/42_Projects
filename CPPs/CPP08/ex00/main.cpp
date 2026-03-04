/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:00:30 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/04 19:00:55 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

void testVector()
{
	std::cout << "\n===== TEST VECTOR =====" << std::endl;

	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(42);

	try
	{
		std::vector<int>::iterator it = easyfind(v, 42);
		std::cout << "Found in vector: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Vector error: " << e.what() << std::endl;
	}

	try
	{
		easyfind(v, 99);
	}
	catch (std::exception &e)
	{
		std::cout << "Vector not found: " << e.what() << std::endl;
	}
}

void testList()
{
	std::cout << "\n===== TEST LIST =====" << std::endl;

	std::list<int> l;
	l.push_back(5);
	l.push_back(15);
	l.push_back(25);
	l.push_back(35);

	try
	{
		std::list<int>::iterator it = easyfind(l, 5);
		std::cout << "Found in list: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "List error: " << e.what() << std::endl;
	}

	try
	{
		easyfind(l, 100);
	}
	catch (std::exception &e)
	{
		std::cout << "List not found: " << e.what() << std::endl;
	}
}

void testDeque()
{
	std::cout << "\n===== TEST DEQUE =====" << std::endl;

	std::deque<int> d;
	d.push_back(1);
	d.push_back(2);
	d.push_back(3);
	d.push_back(4);

	try
	{
		std::deque<int>::iterator it = easyfind(d, 3);
		std::cout << "Found in deque: " << *it << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << "Deque error: " << e.what() << std::endl;
	}

	try
	{
		easyfind(d, -1);
	}
	catch (std::exception &e)
	{
		std::cout << "Deque not found: " << e.what() << std::endl;
	}
}

int main()
{
	testVector();
	testList();
	testDeque();

	return (0);
}