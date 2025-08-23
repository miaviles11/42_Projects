/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:50:01 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/14 19:01:16 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() {
	this->total_contacts = 0;
	this->contact_index = 0;
}

int	convert_to_int(const std::string& input)
{
	if (input.empty())
		return (-1);
	for (size_t i = 0; i < input.length(); i++)
		if (!std::isdigit(input[i]))
			return (-1);
	std::istringstream iss(input);
	int n;
	iss >> n;
	if (iss.fail())
		return (-1);
	return (n);
}

void	PhoneBook::search_contact()
{
	if (this->total_contacts == 0)
	{
		std::cout << "PhoneBook is empty" << std::endl;
		return ;
	}
	std::cout << "|" << std::setw(10) << "Index"
        << "|" << std::setw(10) << "First Name"
        << "|" << std::setw(10) << "Last Name"
        << "|" << std::setw(10) << "Nickname"
        << "|" << std::endl;
	for (int i = 0; i < this->total_contacts; i++)
		contacts[i].display_contact_summary(i);
	std::cout << "Enter index (1-" << this->total_contacts << "): ";
	std::string input;
	std::getline(std::cin, input);
	if (!std::cin) {
		std::cerr << "\nGoodbye!" << std::endl;
		exit (1);
	}
	int index = convert_to_int(input) - 1;
	if (index < 0 || index >= this->total_contacts)
		std::cout << "Invalid index" << std::endl;
	else
		contacts[index].display_contact_full();
}

void	PhoneBook::add_contact()
{
	int index = this->contact_index % 8;
	this->contacts[index].set_contact();
	++contact_index;
	if (total_contacts < 8)
		total_contacts++;
}
