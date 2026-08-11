/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 02:31:02 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/08 02:31:02 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	// The program expects exactly one argument: the input file to evaluate.
	if (argc != 2)
	{
		std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	try
	{
		// Load the price database, then process the user's input file.
		BitcoinExchange btc("data.csv");
		btc.processInput(argv[1]);
	}
	catch (const std::exception &e)
	{
		// Thrown if the database file cannot be opened.
		std::cerr << e.what() << std::endl;
		return (1);
	}
	return (0);
}
