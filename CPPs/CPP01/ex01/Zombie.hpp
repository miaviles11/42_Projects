/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:50:34 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/28 16:56:55 by miaviles         ###   ########.fr       */
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
		Zombie (void);
		~Zombie();

		void setName(const std::string& name);
		void announce(void);
};

Zombie* zombieHorde(int N, std::string name);

#endif