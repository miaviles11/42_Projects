/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:51:34 by miaviles          #+#    #+#             */
/*   Updated: 2026/02/24 16:51:45 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	std::srand(std::time(NULL));

	std::cout << "=== Testing identify with pointers ===" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		Base* ptr = generate();
		std::cout << "Generated type: ";
		identify(ptr);
		delete ptr;
	}

	std::cout << "\n=== Testing identify with references ===" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		Base* ptr = generate();
		std::cout << "Generated type: ";
		identify(*ptr);
		delete ptr;
	}

	return 0;
}