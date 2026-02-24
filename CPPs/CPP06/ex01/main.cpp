/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:50:26 by miaviles          #+#    #+#             */
/*   Updated: 2026/02/24 16:22:23 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int main()
{
	Data original;
	original.id = 42;
	original.name = "Test";
	original.value = 3.14;

	std::cout << "Original address: " << &original << std::endl;
	std::cout << "Original data: id=" << original.id 
			<< ", name=" << original.name 
			<< ", value=" << original.value << std::endl;

	uintptr_t serialized = Serializer::serialize(&original);
	std::cout << "\nSerialized: " << serialized << std::endl;

	Data* deserialized = Serializer::deserialize(serialized);
	std::cout << "\nDeserialized address: " << deserialized << std::endl;
	std::cout << "Deserialized data: id=" << deserialized->id 
			<< ", name=" << deserialized->name 
			<< ", value=" << deserialized->value << std::endl;

	if (deserialized == &original)
		std::cout << "\n✅ Success: Pointers match!" << std::endl;
	else
		std::cout << "\n❌ Error: Pointers don't match!" << std::endl;

	return 0;
}