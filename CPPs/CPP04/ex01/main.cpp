/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:45:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/14 17:12:31 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Cat.hpp"
#include "Animal.hpp"

void testBasicArray()
{
	std::cout << "\n========== TEST 1: Array of Animals ==========" << std::endl;
	const int SIZE = 4;
	Animal *animals[SIZE];
	
	for (int i = 0; i < SIZE / 2; i++)
		animals[i] = new Dog();
	
	for (int i = SIZE / 2; i < SIZE; i++)
		animals[i] = new Cat();
	
	std::cout << "\n--- Making sounds ---" << std::endl;
	for (int i = 0; i < SIZE; i++)
		animals[i]->makeSound();
	
	std::cout << "\n--- Deleting animals ---" << std::endl;
	for (int i = 0; i < SIZE; i++)
		delete animals[i];
}

void testDeepCopy()
{
	std::cout << "\n========== TEST 2: Deep Copy ==========" << std::endl;
	
	std::cout << "\n--- Original Dog ---" << std::endl;
	Dog basic;
	basic.setIdea(0, "I love bones");
	basic.setIdea(1, "Chase the cat");
	
	std::cout << "\n--- Copy constructor ---" << std::endl;
	Dog tmp = basic;
	
	std::cout << "\n--- Modifying copy ---" << std::endl;
	tmp.setIdea(0, "I love sleeping");
	tmp.setIdea(1, "Eat all day");
	
	std::cout << "\n--- Checking independence ---" << std::endl;
	std::cout << "Original idea[0]: " << basic.getIdea(0) << std::endl;
	std::cout << "Original idea[1]: " << basic.getIdea(1) << std::endl;
	std::cout << "Copy idea[0]: " << tmp.getIdea(0) << std::endl;
	std::cout << "Copy idea[1]: " << tmp.getIdea(1) << std::endl;
	
	if (basic.getIdea(0) != tmp.getIdea(0))
		std::cout << "✓ Deep copy works!" << std::endl;
	else
		std::cout << "✗ Shallow copy detected!" << std::endl;
	
	std::cout << "\n--- Assignment operator ---" << std::endl;
	Dog dog1;
	Dog dog2;
	dog1.setIdea(0, "First dog idea");
	dog2 = dog1;
	dog2.setIdea(0, "Second dog idea");
	
	std::cout << "Dog1: " << dog1.getIdea(0) << std::endl;
	std::cout << "Dog2: " << dog2.getIdea(0) << std::endl;
}

void testSubjectCode()
{
	std::cout << "\n========== TEST 3: Subject Code ==========" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	delete j;
	delete i;
}

void testCatBrain()
{
	std::cout << "\n========== TEST 4: Cat Brain ==========" << std::endl;
	
	Cat cat1;
	cat1.setIdea(0, "Hunt mice");
	cat1.setIdea(1, "Sleep 20 hours");
	
	Cat cat2 = cat1;
	cat2.setIdea(0, "Play with yarn");
	
	std::cout << "Cat1 idea[0]: " << cat1.getIdea(0) << std::endl;
	std::cout << "Cat2 idea[0]: " << cat2.getIdea(0) << std::endl;
}

int main()
{
	testBasicArray();
	testDeepCopy();
	testSubjectCode();
	testCatBrain();
	
	std::cout << "\n========== All tests completed ==========" << std::endl;
	
	return 0;
}
