/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 13:43:43 by miaviles          #+#    #+#             */
/*   Updated: 2026/02/04 14:02:26 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "AForm.hpp"
#include <iostream>

void testBasicCreation()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 1: Basic Form Creation\n";
	std::cout << "========================================\n";
	
	Intern someRandomIntern;
	AForm* rrf;
	
	rrf = someRandomIntern.makeForm("robotomy request", "Bender");
	
	if (rrf)
	{
		std::cout << *rrf << std::endl;
		delete rrf;
	}
}

void testAllForms()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 2: Create All Form Types\n";
	std::cout << "========================================\n";
	
	Intern intern;
	AForm* forms[3];
	
	forms[0] = intern.makeForm("shrubbery creation", "home");
	forms[1] = intern.makeForm("robotomy request", "target");
	forms[2] = intern.makeForm("presidential pardon", "criminal");
	
	std::cout << "\n--- Created forms ---\n";
	for (int i = 0; i < 3; i++)
	{
		if (forms[i])
		{
			std::cout << *forms[i] << std::endl;
			delete forms[i];
		}
	}
}

void testInvalidForm()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 3: Invalid Form Name\n";
	std::cout << "========================================\n";
	
	Intern intern;
	AForm* form;
	
	form = intern.makeForm("coffee making", "office");
	
	if (form)
	{
		std::cout << *form << std::endl;
		delete form;
	}
	else
	{
		std::cout << "Form creation returned NULL (as expected)" << std::endl;
	}
}

void testCompleteWorkflow()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 4: Complete Workflow with Intern\n";
	std::cout << "========================================\n";
	
	Intern intern;
	Bureaucrat boss("Boss", 1);
	AForm* form;
	
	std::cout << "\n--- Creating form ---\n";
	form = intern.makeForm("presidential pardon", "Arthur Dent");
	
	if (form)
	{
		std::cout << "\n--- Bureaucrat processing ---\n";
		std::cout << boss << std::endl;
		std::cout << *form << std::endl;
		
		boss.signForm(*form);
		boss.executeForm(*form);
		
		delete form;
	}
}

void testMultipleInterns()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 5: Multiple Interns\n";
	std::cout << "========================================\n";
	
	Intern intern1;
	Intern intern2;
	Intern intern3;
	
	AForm* f1 = intern1.makeForm("shrubbery creation", "garden");
	AForm* f2 = intern2.makeForm("robotomy request", "android");
	AForm* f3 = intern3.makeForm("presidential pardon", "prisoner");
	
	std::cout << "\nAll forms created successfully!" << std::endl;
	
	delete f1;
	delete f2;
	delete f3;
}

void testCaseSensitivity()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 6: Case Sensitivity\n";
	std::cout << "========================================\n";
	
	Intern intern;
	AForm* form;
	
	std::cout << "--- Trying 'Robotomy Request' (capital R) ---\n";
	form = intern.makeForm("Robotomy Request", "target");
	if (form) delete form;
	
	std::cout << "\n--- Trying 'robotomy request' (lowercase) ---\n";
	form = intern.makeForm("robotomy request", "target");
	if (form)
	{
		std::cout << "Success!\n";
		delete form;
	}
}

void testSubjectExample()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 7: Subject Example\n";
	std::cout << "========================================\n";
	
	{
		Intern someRandomIntern;
		AForm* rrf;
		
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		
		if (rrf)
			delete rrf;
	}
}

int main()
{
	testBasicCreation();
	testAllForms();
	testInvalidForm();
	testCompleteWorkflow();
	testMultipleInterns();
	testCaseSensitivity();
	testSubjectExample();
	
	std::cout << "\n========================================\n";
	std::cout << "All tests completed!\n";
	std::cout << "========================================\n";
	
	return (0);
}
