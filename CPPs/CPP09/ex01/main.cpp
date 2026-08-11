/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 17:39:34 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/09 17:39:34 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	// The program expects exactly one argument: the RPN expression string.
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	// Evaluate the expression; calculate() prints the result or an error.
	RPN rpn;
	rpn.calculate(argv[1]);
	return (0);
}
