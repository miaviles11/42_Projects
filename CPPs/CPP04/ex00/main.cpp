/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:09:50 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/14 15:56:00 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

static void banner(const std::string& title) {
	std::cout << "\n==== " << title << " ====\n";
}

int main() {
	banner("BASIC: polimorfismo por puntero a base");
	const Animal* meta = new Animal();
	const Animal* dog  = new Dog();
	const Animal* cat  = new Cat();

	std::cout << "Types -> dog: " << dog->getType()
			<< " | cat: " << cat->getType() << std::endl;

	std::cout << "[cat->makeSound()] "; cat->makeSound();
	std::cout << "[dog->makeSound()] "; dog->makeSound();
	std::cout << "[meta->makeSound()] "; meta->makeSound();

	std::cout << "Deleting meta...\n";
	delete meta;
	std::cout << "Deleting dog...\n";
	delete dog;
	std::cout << "Deleting cat...\n";
	delete cat;

	banner("REFERENCIAS: polimorfismo por referencia");
	Dog d; Cat c;
	Animal& a1 = d;
	Animal& a2 = c;
	std::cout << "[Animal& a1(d).makeSound()] "; a1.makeSound();
	std::cout << "[Animal& a2(c).makeSound()] "; a2.makeSound();

	banner("COPIA/ASIGNACION: forma canonica rapida");
	Dog d1;
	Dog d2(d1);
	Dog d3;
	d3 = d2;
	std::cout << "d2.type=" << d2.getType()
			<< " | d3.type=" << d3.getType() << std::endl;

	banner("WRONG*: sin virtual (anti-ejemplo)");
	const WrongAnimal* wa = new WrongAnimal();
	const WrongAnimal* wc = new WrongCat();

	std::cout << "wc->getType(): " << wc->getType() << std::endl;
	std::cout << "[wa->makeSound()] "; wa->makeSound();
	std::cout << "[wc->makeSound()] "; wc->makeSound();

	std::cout << "Deleting wc...\n";
	delete wc;
	std::cout << "Deleting wa...\n";
	delete wa;

	banner("FIN");
	return 0;
}
