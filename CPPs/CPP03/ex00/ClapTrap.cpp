/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:09:15 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/25 12:01:21 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : hitPoints(10), energyPoints(10), attackDamage(0)
{
    std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
	: name(name), hitPoints(10), energyPoints(10), attackDamage(0)
{
	std::cout << "ClapTrap constructor called for " << this->name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other) 
	: name(other.name), hitPoints(other.hitPoints),
	  energyPoints(other.energyPoints), attackDamage(other.attackDamage)
{
	std::cout << "ClapTrap copy constructor called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
	if (this != &other)
	{
		name = other.name;
		hitPoints = other.hitPoints;
		energyPoints = other.energyPoints;
		attackDamage = other.attackDamage;
	}
	return *this;
}

ClapTrap::~ClapTrap()
{
	if (this->name.empty())
		std::cout << "ClapTrap destructor called (unnamed)" << std::endl;
	else
		std::cout << "ClapTrap destructor called for " << this->name << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
	if (this->hitPoints > 0 && this->energyPoints > 0)
	{
		this->energyPoints--;
		std::cout << "ClapTrap " << this->name
				  << " attacks " << target
				  << ", causing " << this->attackDamage
				  << " points of damage!" << std::endl;
	}
	else
	{
		if (this->hitPoints <= 0)
			std::cout << "ClapTrap " << this->name
					  << " cannot attack because it has no hit points left!"
					  << std::endl;
		else
			std::cout << "ClapTrap " << this->name
					  << " cannot attack because it has no energy left!"
					  << std::endl;
	}
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (this->hitPoints <= 0)
	{
		std::cout << "ClapTrap " << this->name
				  << " is already destroyed and cannot take more damage!"
				  << std::endl;
		return;
	}
	this->hitPoints -= static_cast<int>(amount);
	if (this->hitPoints < 0)
		this->hitPoints = 0;
	std::cout << "ClapTrap " << this->name
			  << " takes " << amount
			  << " points of damage! Remaining HP: "
			  << this->hitPoints << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->hitPoints <= 0)
	{
		std::cout << "ClapTrap " << this->name
                  << " cannot be repaired because it has no hit points left!"
                  << std::endl;
		return;
	}
	if (this->energyPoints <= 0)
	{
		std::cout << "ClapTrap " << this->name
				  << " cannot be repaired because it has no energy left!"
				  << std::endl;
		return;
	}
	this->energyPoints--;
	this->hitPoints += amount;
	std::cout << "ClapTrap " << this->name
			  << " repairs itself for " << amount
			  << " points! Current HP: "
			  << this->hitPoints  << std::endl;
}