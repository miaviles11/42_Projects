/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:56:51 by miaviles          #+#    #+#             */
/*   Updated: 2025/08/23 17:11:54 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	Zombie* zombie_ptr = newZombie("HeapZed");
	zombie_ptr->announce();
	delete zombie_ptr;
	randomChump("StackZed");
	return (0);
}
