/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 17:36:03 by miaviles          #+#    #+#             */
/*   Updated: 2026/01/28 20:05:33 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
	std::cout << "\n========================================\n";
	std::cout << "TEST 1: Creating valid forms\n";
	std::cout << "========================================\n";
	try {
		Form taxForm("Tax Form", 50, 25);
		Form buildingPermit("Building Permit", 100, 75);
		
		std::cout << taxForm << std::endl;
		std::cout << buildingPermit << std::endl;
	} catch (std::exception &e) {
		std::cout << "❌ Error: " << e.what() << std::endl;
	}

	std::cout << "\n========================================\n";
	std::cout << "TEST 2: Invalid form grades\n";
	std::cout << "========================================\n";
	try {
		Form invalid1("Invalid High", 0, 50);
	} catch (std::exception &e) {
		std::cout << "✓ Exception caught: " << e.what() << std::endl;
	}

	try {
		Form invalid2("Invalid Low", 50, 151);
	} catch (std::exception &e) {
		std::cout << "✓ Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n========================================\n";
	std::cout << "TEST 3: Successful signing\n";
	std::cout << "========================================\n";
	try {
		Bureaucrat john("John", 30);
		Form contract("Employment Contract", 50, 25);
		
		std::cout << "Before signing: " << contract << std::endl;
		john.signForm(contract);
		std::cout << "After signing:  " << contract << std::endl;
	} catch (std::exception &e) {
		std::cout << "❌ Error: " << e.what() << std::endl;
	}

	std::cout << "\n========================================\n";
	std::cout << "TEST 4: Failed signing (grade too low)\n";
	std::cout << "========================================\n";
	try {
		Bureaucrat intern("Intern", 100);
		Form topSecret("Top Secret", 20, 10);
		
		std::cout << intern << std::endl;
		std::cout << topSecret << std::endl;
		intern.signForm(topSecret);
	} catch (std::exception &e) {
		std::cout << "❌ Error: " << e.what() << std::endl;
	}

	std::cout << "\n========================================\n";
	std::cout << "TEST 5: Edge case - exact grade\n";
	std::cout << "========================================\n";
	try {
		Bureaucrat alice("Alice", 50);
		Form report("Quarterly Report", 50, 30);
		
		alice.signForm(report);
		std::cout << report << std::endl;
	} catch (std::exception &e) {
		std::cout << "❌ Error: " << e.what() << std::endl;
	}

	std::cout << "\n========================================\n";
	std::cout << "TEST 6: Multiple signing attempts\n";
	std::cout << "========================================\n";
	try {
		Form memo("Important Memo", 75, 50);
		Bureaucrat boss("Boss", 50);
		Bureaucrat worker("Worker", 100);
		
		boss.signForm(memo);
		worker.signForm(memo);
		
		std::cout << memo << std::endl;
	} catch (std::exception &e) {
		std::cout << "❌ Error: " << e.what() << std::endl;
	}

	std::cout << "\n========================================\n";
	std::cout << "TEST 7: Copy constructor and assignment\n";
	std::cout << "========================================\n";
	try {
		Form original("Original", 50, 30);
		Bureaucrat signer("Signer", 40);
		
		signer.signForm(original);
		
		Form copy1(original);
		Form copy2("Temporary", 100, 80);
		copy2 = original;
		
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy1:    " << copy1 << std::endl;
		std::cout << "Copy2:    " << copy2 << std::endl;
	} catch (std::exception &e) {
		std::cout << "❌ Error: " << e.what() << std::endl;
	}

	std::cout << "\n========================================\n";
	std::cout << "All tests completed!\n";
	std::cout << "========================================\n";

	return (0);
}