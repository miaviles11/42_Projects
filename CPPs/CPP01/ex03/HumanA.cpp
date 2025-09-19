/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:49:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/28 19:30:26 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(const std::string& name, Weapon& weapon)
	: name(name), weapon(weapon) {}

void	HumanA::attack() const {
	std::cout << this->name << " attacks with their " 
		<< this->weapon.getType() << std::endl;
}