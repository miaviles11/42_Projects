/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:40:52 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/17 12:18:18 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

int main( void ) 
{
	Fixed a;
	Fixed b( a );
	Fixed c;

	c = b;

	std::cout << a.getRawBits() << std::endl;
	std::cout << b.getRawBits() << std::endl;
	std::cout << c.getRawBits() << std::endl;

    Fixed d;
    d.setRawBits(42);
    std::cout << "d = " << d.getRawBits() << std::endl;

    Fixed e(d);
    std::cout << "e = " << e.getRawBits() << std::endl;

    Fixed f;
    f = d;
    std::cout << "f = " << f.getRawBits() << std::endl;
	
	return (0);
}