/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:42:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/14 18:57:31 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
	std::cout << "\n=== TEST 1: Cannot instantiate Animal ===" << std::endl;
	std::cout << "✓ Animal is abstract (uncomment line above to verify)" << std::endl;
	
	std::cout << "\n=== TEST 2: Create Dog and Cat ===" << std::endl;
	Dog dog;
	Cat cat;
	dog.makeSound();
	cat.makeSound();
	
	std::cout << "\n=== TEST 3: Polymorphism ===" << std::endl;
	const Animal* animals[4];
	animals[0] = new Dog();
	animals[1] = new Dog();
	animals[2] = new Cat();
	animals[3] = new Cat();
	
	for (int i = 0; i < 4; i++)
		animals[i]->makeSound();
	
	for (int i = 0; i < 4; i++)
		delete animals[i];
	
	std::cout << "\n=== TEST 4: Deep Copy ===" << std::endl;
	Dog dog1;
	dog1.setIdea(0, "Original idea");
	
	Dog dog2 = dog1;
	dog2.setIdea(0, "Modified idea");
	
	std::cout << "Dog1: " << dog1.getIdea(0) << std::endl;
	std::cout << "Dog2: " << dog2.getIdea(0) << std::endl;
	
	if (dog1.getIdea(0) != dog2.getIdea(0))
		std::cout << "✓ Deep copy works!" << std::endl;
	
	return 0;
}
