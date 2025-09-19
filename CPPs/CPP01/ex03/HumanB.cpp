/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:50:08 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/28 19:31:13 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(const std::string& name) : name(name), weapon(NULL) {}

void	HumanB::setWeapon(Weapon& weapon) {
	this->weapon = &weapon;
}

void	HumanB::attack() const {
	if (this->weapon)
		std::cout << this->name << " attacks with their " 
			      << this->weapon->getType() << std::endl;
	else
		std::cout << this->name << " has no weapon!" << std::endl;
}