/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:20:33 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/14 19:43:07 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include "PhoneBook.hpp"

int	main()
{
	PhoneBook p;

	while (1) {
		std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
		std::string input;
		std::getline(std::cin, input);
		if (!std::cin) {
			std::cout << "\nGoodbye!" << std::endl;
			break;
		}
		else if (input == "ADD")
			p.add_contact();
		else if (input == "SEARCH")
			p.search_contact();
		else if (input == "EXIT")
			break ;
		else if (input.empty())
			continue ;
		else
			std::cout << "Invalid command" << std::endl;
	}
	return (0);
}
