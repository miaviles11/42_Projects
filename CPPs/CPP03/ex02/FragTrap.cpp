/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:22:53 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/25 12:18:21 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(const std::string& name) : ClapTrap(name)
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap constructor called for " << this->name << std::endl;
}

FragTrap::FragTrap() : ClapTrap()
{
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
	std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other)
{
	std::cout << "FragTrap copy assignment operator called" << std::endl;
	if (this != &other)
		ClapTrap::operator=(other);
	return *this;
}

FragTrap::~FragTrap()
{
	if (this->name.empty())
		std::cout << "FragTrap destructor called (unnamed)" << std::endl;
	else
		std::cout << "FragTrap destructor called for " << this->name << std::endl;
}

void FragTrap::attack(const std::string& target)
{
	if (this->hitPoints > 0 && this->energyPoints > 0)
	{
		this->energyPoints--;
		std::cout << "FragTrap " << this->name
				  << " attacks " << target
				  << ", causing " << this->attackDamage
				  << " points of damage!" << std::endl;
	}
	else
	{
		if (this->hitPoints <= 0)
			std::cout << "FragTrap " << this->name
					  << " cannot attack because it has no hit points left!"
					  << std::endl;
		else
			std::cout << "FragTrap " << this->name
					  << " cannot attack because it has no energy left!"
					  << std::endl;
	}
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->name << " requests a high five!" << std::endl;
}
