/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:51:59 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/14 18:48:58 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact() {}

std::string	get_input(const std::string& prompt) {
	std::string	input;

	do {
		std::cout << prompt;
		std::getline(std::cin, input);
		if (!std::cin) {
			std::cerr << "\nGoodbye!" << std::endl;
			exit (1);
		}
		if (input.empty())
			std::cout << "This field cannot be empty!" << std::endl;
	} while (input.empty());
	return (input);
}

void	Contact::set_contact() 
{
	this->first_name = get_input("Enter first name: ");
	this->last_name = get_input("Enter last name: ");
	this->nickname = get_input("Enter nickname: ");
	this->phone_number = get_input("Enter phone number: ");
	this->darkest_secret = get_input("Enter darkest secret: ");
}

std::string	truncate(std::string str) {
	if (str.length() > 10)
		return (str.substr(0, 9) + ".");
	return (str);
}

void	Contact::display_contact_summary(int index)
{
	std::cout << "|" << std::setw(10) << std::right << (index + 1) << "|";
	std::cout << std::setw(10) << truncate(this->first_name) << "|";
	std::cout << std::setw(10) << truncate(this->last_name) << "|";
	std::cout << std::setw(10) << truncate(this->nickname) << "|" << std::endl;
}

void	Contact::display_contact_full()
{
	std::cout << "First name: " << this->first_name << std::endl;
	std::cout << "Last name: " << this->last_name << std::endl;
	std::cout << "Nickname: " << this->nickname << std::endl;
	std::cout << "Phone number: " << this->phone_number << std::endl;
	std::cout << "Darkest secret: " << this->darkest_secret << std::endl;
}
