/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:42:34 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/19 15:06:42 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main()
{
    std::cout.setf(std::ios::fixed);
    std::cout.precision(2);

    Fixed a(5.5f);
    Fixed b(2);
    Fixed c(a);
    Fixed d;

    d = b;

    std::cout << "=== Valores iniciales ===" << std::endl;
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c (copy de a): " << c << std::endl;
    std::cout << "d (asignado de b): " << d << std::endl;

    std::cout << "\n=== Comparadores ===" << std::endl;
    std::cout << "a < b: " << (a < b) << std::endl;
    std::cout << "a > b: " << (a > b) << std::endl;
    std::cout << "a == c: " << (a == c) << std::endl;
    std::cout << "a != b: " << (a != b) << std::endl;

    std::cout << "\n=== Aritméticos ===" << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;

    std::cout << "\n=== Incremento / Decremento ===" << std::endl;
    Fixed x(3);
    std::cout << "x: " << x << std::endl;
    std::cout << "++x: " << ++x << std::endl;
    std::cout << "x++: " << x++ << " (después x = " << x << ")" << std::endl;
    std::cout << "--x: " << --x << std::endl;
    std::cout << "x--: " << x-- << " (después x = " << x << ")" << std::endl;

    std::cout << "\n=== Min / Max ===" << std::endl;
    Fixed e(10);
    Fixed f(42.42f);
    std::cout << "min(e, f): " << Fixed::min(e, f) << std::endl;
    std::cout << "max(e, f): " << Fixed::max(e, f) << std::endl;

    return (0);
}
