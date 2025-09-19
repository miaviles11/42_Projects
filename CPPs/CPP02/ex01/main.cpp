/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:23:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/19 15:06:06 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main(void)
{
    Fixed a;
    Fixed b(10);
    Fixed c(42.42f);
    Fixed d(b);
	Fixed e(-3.75f);
	Fixed f(123.78f);

    a = c;

    std::cout << "=== Operator<< ===" << std::endl;
    std::cout << "a is " << a << std::endl;
    std::cout << "b is " << b << std::endl;
    std::cout << "c is " << c << std::endl;
    std::cout << "d is " << d << std::endl;

    std::cout << "\n=== toFloat() ===" << std::endl;
    std::cout << "a.toFloat(): " << a.toFloat() << std::endl;
    std::cout << "b.toFloat(): " << b.toFloat() << std::endl;
    std::cout << "c.toFloat(): " << c.toFloat() << std::endl;
    std::cout << "d.toFloat(): " << d.toFloat() << std::endl;

    std::cout << "\n=== toInt() ===" << std::endl;
    std::cout << "a.toInt(): " << a.toInt() << std::endl;
    std::cout << "b.toInt(): " << b.toInt() << std::endl;
    std::cout << "c.toInt(): " << c.toInt() << std::endl;
    std::cout << "d.toInt(): " << d.toInt() << std::endl;

	std::cout << "e.toFloat(): " << e.toFloat() << " | e.toInt(): " << e.toInt() << std::endl;
	std::cout << "f.toFloat(): " << f.toFloat() << " | f.toInt(): " << f.toInt() << std::endl;

    return (0);
}

