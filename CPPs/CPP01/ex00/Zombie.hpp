/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:57:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/23 17:10:12 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <string>
#include <iostream>

class Zombie 
{
	private:
		std::string	name;

	public:
		Zombie(const std::string& name);
		~Zombie();

		void announce(void);
};

Zombie* newZombie(std::string name);
void    randomChump(std::string name);

#endif
