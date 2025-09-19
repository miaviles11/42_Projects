/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 18:50:12 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/28 19:06:30 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANB_HPP
# define HUMANB_HPP

#include "Weapon.hpp"

class HumanB {
	private:
		std::string name;
		Weapon* weapon;

	public:
		HumanB(const std::string& name);
		void	setWeapon(Weapon& weapon);
		void	attack() const;
};

#endif