/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:36:03 by miaviles          #+#    #+#             */
/*   Updated: 2026/01/29 19:17:25 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

void testShrubbery()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 1: ShrubberyCreationForm\n";
	std::cout << "========================================\n";
	
	try {
		Bureaucrat bob("Bob", 140);
		ShrubberyCreationForm form("home");
		
		std::cout << bob << std::endl;
		std::cout << form << std::endl;
		
		std::cout << "\n--- Trying to execute unsigned form ---\n";
		bob.executeForm(form);
		
		std::cout << "\n--- Signing the form ---\n";
		bob.signForm(form);
		
		std::cout << "\n--- Executing signed form ---\n";
		bob.executeForm(form);
		
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void testShrubberyFail()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 2: ShrubberyCreationForm - Insufficient Grade\n";
	std::cout << "========================================\n";
	
	try {
		Bureaucrat intern("Intern", 150);
		ShrubberyCreationForm form("garden");
		
		std::cout << intern << std::endl;
		std::cout << form << std::endl;
		
		std::cout << "\n--- Trying to sign (should fail) ---\n";
		intern.signForm(form);
		
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void testRobotomy()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 3: RobotomyRequestForm\n";
	std::cout << "========================================\n";
	
	try {
		Bureaucrat alice("Alice", 40);
		RobotomyRequestForm form("Bender");
		
		std::cout << alice << std::endl;
		std::cout << form << std::endl;
		
		std::cout << "\n--- Signing the form ---\n";
		alice.signForm(form);
		
		std::cout << "\n--- Executing (attempt 1) ---\n";
		alice.executeForm(form);
		
		std::cout << "\n--- Executing (attempt 2) ---\n";
		alice.executeForm(form);
		
		std::cout << "\n--- Executing (attempt 3) ---\n";
		alice.executeForm(form);
		
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void testRobotomyFail()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 4: RobotomyRequestForm - Insufficient Exec Grade\n";
	std::cout << "========================================\n";
	
	try {
		Bureaucrat charlie("Charlie", 50);
		RobotomyRequestForm form("Target");
		
		std::cout << charlie << std::endl;
		std::cout << form << std::endl;
		
		std::cout << "\n--- Signing the form ---\n";
		charlie.signForm(form);
		
		std::cout << "\n--- Trying to execute (should fail) ---\n";
		charlie.executeForm(form);
		
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void testPresidential()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 5: PresidentialPardonForm\n";
	std::cout << "========================================\n";
	
	try {
		Bureaucrat president("President", 1);
		PresidentialPardonForm form("Arthur Dent");
		
		std::cout << president << std::endl;
		std::cout << form << std::endl;
		
		std::cout << "\n--- Signing the form ---\n";
		president.signForm(form);
		
		std::cout << "\n--- Executing the form ---\n";
		president.executeForm(form);
		
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void testPresidentialFail()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 6: PresidentialPardonForm - Can Sign but Cannot Execute\n";
	std::cout << "========================================\n";
	
	try {
		Bureaucrat manager("Manager", 10);
		PresidentialPardonForm form("Criminal");
		
		std::cout << manager << std::endl;
		std::cout << form << std::endl;
		
		std::cout << "\n--- Signing the form (should succeed) ---\n";
		manager.signForm(form);
		
		std::cout << "\n--- Trying to execute (should fail - need grade 5) ---\n";
		manager.executeForm(form);
		
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void testMultipleForms()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 7: One Bureaucrat, Multiple Forms\n";
	std::cout << "========================================\n";
	
	try {
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm shrub("office");
		RobotomyRequestForm robot("Employee");
		PresidentialPardonForm pardon("Convict");
		
		std::cout << boss << "\n" << std::endl;
		
		std::cout << "--- Processing Shrubbery ---\n";
		boss.signForm(shrub);
		boss.executeForm(shrub);
		
		std::cout << "\n--- Processing Robotomy ---\n";
		boss.signForm(robot);
		boss.executeForm(robot);
		
		std::cout << "\n--- Processing Pardon ---\n";
		boss.signForm(pardon);
		boss.executeForm(pardon);
		
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void testPolymorphism()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 8: Polymorphism with AForm pointers\n";
	std::cout << "========================================\n";
	
	try {
		Bureaucrat ceo("CEO", 1);
		
		AForm *forms[3];
		forms[0] = new ShrubberyCreationForm("park");
		forms[1] = new RobotomyRequestForm("Android");
		forms[2] = new PresidentialPardonForm("Prisoner");
		
		for (int i = 0; i < 3; i++)
		{
			std::cout << "\n--- Form " << i + 1 << " ---\n";
			std::cout << *forms[i] << std::endl;
			ceo.signForm(*forms[i]);
			ceo.executeForm(*forms[i]);
		}
		
		for (int i = 0; i < 3; i++)
			delete forms[i];
		
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void testEdgeCases()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 9: Edge Cases\n";
	std::cout << "========================================\n";
	
	try {
		Bureaucrat exact("Exact", 145);
		ShrubberyCreationForm form("test");
		
		std::cout << exact << std::endl;
		std::cout << form << std::endl;
		
		std::cout << "\n--- Signing with exact grade (145) ---\n";
		exact.signForm(form);
		
		std::cout << "\n--- Trying to execute with grade 145 (need 137) ---\n";
		exact.executeForm(form);
		
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

void testCopyConstructor()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 10: Copy Constructor\n";
	std::cout << "========================================\n";
	
	try {
		ShrubberyCreationForm original("original");
		Bureaucrat signer("Signer", 100);
		
		signer.signForm(original);
		
		ShrubberyCreationForm copy(original);
		
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy:     " << copy << std::endl;
		
		std::cout << "\n--- Executing copy ---\n";
		signer.executeForm(copy);
		
	} catch (std::exception &e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

int main()
{
	testShrubbery();
	testShrubberyFail();
	testRobotomy();
	testRobotomyFail();
	testPresidential();
	testPresidentialFail();
	testMultipleForms();
	testPolymorphism();
	testEdgeCases();
	testCopyConstructor();
	
	std::cout << "\n========================================\n";
	std::cout << "All tests completed!\n";
	std::cout << "========================================\n";
	
	return 0;
}