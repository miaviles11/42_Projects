/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:57:23 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/14 20:18:49 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(const std::string& name) : name(name) {}

Zombie::~Zombie() {
	std::cout << this->name << " is destroyed" << std::endl;
}

void	Zombie::announce(void){
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
