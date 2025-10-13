/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:06:34 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/25 12:21:20 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) 
{
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	std::cout << "ScavTrap constructor called for " << this->name << std::endl;
}

ScavTrap::ScavTrap() : ClapTrap()
{
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
	std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other)
{
	std::cout << "ScavTrap copy assignment operator called" << std::endl;
	if (this != &other)
		ClapTrap::operator=(other);
	return *this;
}

ScavTrap::~ScavTrap()
{
	if (this->name.empty())
		std::cout << "ScavTrap destructor called (unnamed)" << std::endl;
	else
		std::cout << "ScavTrap destructor called for " << this->name << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
	if (this->hitPoints > 0 && this->energyPoints > 0)
	{
		this->energyPoints--;
		std::cout << "ScavTrap " << this->name
				  << " attacks " << target
				  << ", causing " << this->attackDamage
				  << " points of damage!" << std::endl;
	}
	else
	{
		if (this->hitPoints <= 0)
			std::cout << "ScavTrap " << this->name
					  << " cannot attack because it has no hit points left!"
					  << std::endl;
		else
			std::cout << "ScavTrap " << this->name
					  << " cannot attack because it has no energy left!"
					  << std::endl;
	}
}

void	ScavTrap::guardGate(void)
{
	std::cout << "ScavTrap " << this->name << " is now in Gate keeper mode" << std::endl;
}
