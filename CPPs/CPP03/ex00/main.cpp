/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:09:09 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/23 18:29:16 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
	ClapTrap a("Alpha");
	ClapTrap b("Beta");
	ClapTrap c;
	ClapTrap d(a);

	d = b;

	a.attack("Beta");
	b.takeDamage(5);
	b.beRepaired(3);

	for (int i = 0; i < 12; i++)
		a.attack("Beta");

	b.takeDamage(20);
	b.attack("Alpha");
	b.beRepaired(5);

	ClapTrap e("Epsilon");
	for (int i = 0; i < 10; i++)
		e.beRepaired(1);
	e.attack("Alpha");

	ClapTrap f("Fragile");
	f.takeDamage(15);
	f.beRepaired(10);
	f.attack("Alpha");

	return 0;
}
