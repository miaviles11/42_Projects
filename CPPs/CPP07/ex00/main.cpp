/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 00:37:50 by miaviles          #+#    #+#             */
/*   Updated: 2026/02/25 00:37:50 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	#include "whatever.hpp"
	#include <iostream>
	#include <string>

	int main(void)
	{
		std::cout << "===== INT TEST =====" << std::endl;
		int a = 2;
		int b = 3;

		std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
		::swap(a, b);
		std::cout << "After swap:  a = " << a << ", b = " << b << std::endl;
		std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
		std::cout << "max(a, b) = " << ::max(a, b) << std::endl;


		std::cout << "\n===== EQUAL INT TEST =====" << std::endl;
		int x = 5;
		int y = 5;

		std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
		::swap(x, y);
		std::cout << "After swap:  x = " << x << ", y = " << y << std::endl;

		const int& minResult = ::min(x, y);
		const int& maxResult = ::max(x, y);

		std::cout << "Address of x: " << &x << std::endl;
		std::cout << "Address of y: " << &y << std::endl;
		std::cout << "Address returned by min: " << &minResult << std::endl;
		std::cout << "Address returned by max: " << &maxResult << std::endl;


		std::cout << "\n===== DOUBLE TEST =====" << std::endl;
		double d1 = 3.14;
		double d2 = 2.71;

		std::cout << "Before swap: d1 = " << d1 << ", d2 = " << d2 << std::endl;
		::swap(d1, d2);
		std::cout << "After swap:  d1 = " << d1 << ", d2 = " << d2 << std::endl;
		std::cout << "min(d1, d2) = " << ::min(d1, d2) << std::endl;
		std::cout << "max(d1, d2) = " << ::max(d1, d2) << std::endl;


		std::cout << "\n===== CHAR TEST =====" << std::endl;
		char c1 = 'a';
		char c2 = 'z';

		std::cout << "Before swap: c1 = " << c1 << ", c2 = " << c2 << std::endl;
		::swap(c1, c2);
		std::cout << "After swap:  c1 = " << c1 << ", c2 = " << c2 << std::endl;
		std::cout << "min(c1, c2) = " << ::min(c1, c2) << std::endl;
		std::cout << "max(c1, c2) = " << ::max(c1, c2) << std::endl;


		std::cout << "\n===== STRING TEST =====" << std::endl;
		std::string s1 = "chaine1";
		std::string s2 = "chaine2";

		std::cout << "Before swap: s1 = " << s1 << ", s2 = " << s2 << std::endl;
		::swap(s1, s2);
		std::cout << "After swap:  s1 = " << s1 << ", s2 = " << s2 << std::endl;
		std::cout << "min(s1, s2) = " << ::min(s1, s2) << std::endl;
		std::cout << "max(s1, s2) = " << ::max(s1, s2) << std::endl;


		std::cout << "\n===== CONST INT TEST =====" << std::endl;
		const int k1 = 10;
		const int k2 = 20;

		std::cout << "k1 = " << k1 << ", k2 = " << k2 << std::endl;
		std::cout << "min(k1, k2) = " << ::min(k1, k2) << std::endl;
		std::cout << "max(k1, k2) = " << ::max(k1, k2) << std::endl;

		return (0);
	}