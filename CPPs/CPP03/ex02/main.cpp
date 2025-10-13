/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:09:09 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/25 12:03:31 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
	std::cout << "=== ClapTrap tests ===" << std::endl;
	ClapTrap c1("Clappy");
	ClapTrap c2("Trappy");
	ClapTrap c3;
	ClapTrap c4(c1);
	c3 = c2;

	c1.attack("Trappy");
	c2.takeDamage(5);
	c2.beRepaired(3);

	for (int i = 0; i < 11; i++)
		c1.attack("Trappy");

	c2.takeDamage(20);
	c2.attack("Clappy");
	c2.beRepaired(5);

	std::cout << "\n=== ScavTrap tests ===" << std::endl;
	ScavTrap s1("Scavyd");
	ScavTrap s2("Guardyd");
	ScavTrap s3;
	ScavTrap s4(s1);
	s3 = s2;

	s1.attack("Guardyd");
	s2.takeDamage(30);
	s2.beRepaired(20);

	for (int i = 0; i < 55; i++)
		s1.attack("Guardyd");

	s2.takeDamage(200);
	s2.attack("Scavyd");
	s2.beRepaired(50);

	s1.guardGate();
	s2.guardGate();
	s3.guardGate();

	std::cout << "\n=== FragTrap tests ===" << std::endl;
	FragTrap f1("Fraggy");
	FragTrap f2("Boomy");
	FragTrap f3;
	FragTrap f4(f1);
	f3 = f2;

	f1.attack("Boomy");
	f2.takeDamage(40);
	f2.beRepaired(25);

	for (int i = 0; i < 105; i++)
		f1.attack("Boomy");

	f2.takeDamage(200);
	f2.attack("Fraggy");
	f2.beRepaired(60);

	f1.highFivesGuys();
	f2.highFivesGuys();
	f3.highFivesGuys();

	std::cout << "\n=== End of tests ===" << std::endl;
	return (0);
}
