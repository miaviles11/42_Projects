/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:42:34 by miaviles          #+#    #+#             */
/*   Updated: 2026/02/04 14:01:36 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern &other)
{
	(void)other;
}

Intern &Intern::operator=(const Intern &other)
{
	(void)other;
	return (*this);
}

Intern::~Intern()
{
}

static AForm* createShrubberyForm(const std::string &target)
{
	return new ShrubberyCreationForm(target);
}

static AForm* createRobotomyForm(const std::string &target)
{
	return new RobotomyRequestForm(target);
}

static AForm* createPresidentialForm(const std::string &target)
{
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(std::string formName, std::string target)
{
	std::string formTypes[3] = {
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	AForm* (*formCreators[3])(const std::string &) = {
		&createShrubberyForm,
		&createRobotomyForm,
		&createPresidentialForm
	};

	for (int i = 0; i < 3; i++)
	{
		if (formName == formTypes[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			return formCreators[i](target);
		}
	}

	std::cout << "Error: Intern cannot create form '" << formName 
			<< "' because it doesn't exist" << std::endl;
	return (NULL);
}


