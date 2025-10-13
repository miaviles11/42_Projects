/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:09:09 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/25 11:03:51 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

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

    std::cout << "\n=== End of tests ===" << std::endl;
    return (0);
}
