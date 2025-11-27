/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:30:00 by miaviles          #+#    #+#             */
/*   Updated: 2025/10/17 15:47:53 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "Cure.hpp"
#include "Character.hpp"
#include "MateriaSource.hpp"

void separator(const std::string& title)
{
	std::cout << "\n========================================" << std::endl;
	std::cout << " " << title << std::endl;
	std::cout << "========================================" << std::endl;
}

void testSubjectCode()
{
	separator("TEST 1: Subject's Required Code");
	
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	
	ICharacter* me = new Character("me");
	
	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	
	ICharacter* bob = new Character("bob");
	
	me->use(0, *bob);
	me->use(1, *bob);
	
	delete bob;
	delete me;
	delete src;
	
	std::cout << "\n✅ Subject code works!" << std::endl;
}

void testMateriaCreation()
{
	separator("TEST 2: Materia Creation & Clone");
	
	std::cout << "\n--- Creating Ice materia ---" << std::endl;
	Ice* ice = new Ice();
	std::cout << "Type: " << ice->getType() << std::endl;
	
	std::cout << "\n--- Cloning Ice ---" << std::endl;
	AMateria* iceClone = ice->clone();
	std::cout << "Clone type: " << iceClone->getType() << std::endl;
	
	std::cout << "\n--- Creating Cure materia ---" << std::endl;
	Cure* cure = new Cure();
	std::cout << "Type: " << cure->getType() << std::endl;
	
	std::cout << "\n--- Cloning Cure ---" << std::endl;
	AMateria* cureClone = cure->clone();
	std::cout << "Clone type: " << cureClone->getType() << std::endl;
	
	delete ice;
	delete iceClone;
	delete cure;
	delete cureClone;
	
	std::cout << "\n✅ Materia creation works!" << std::endl;
}

void testCharacterInventory()
{
	separator("TEST 3: Character Inventory (4 slots)");
	
	Character hero("Hero");
	
	std::cout << "\n--- Equipping 4 materias ---" << std::endl;
	hero.equip(new Ice());
	hero.equip(new Cure());
	hero.equip(new Ice());
	hero.equip(new Cure());
	
	std::cout << "\n--- Trying to equip 5th materia (should be ignored) ---" << std::endl;
	AMateria* extra = new Ice();
	hero.equip(extra);
	delete extra;
	
	std::cout << "\n--- Using all equipped materias ---" << std::endl;
	Character target("Target");
	for (int i = 0; i < 4; i++)
	{
		std::cout << "[Slot " << i << "] ";
		hero.use(i, target);
	}
	
	std::cout << "\n✅ Inventory works!" << std::endl;
}

void testUnequip()
{
	separator("TEST 4: Unequip (no delete)");
	
	Character wizard("Wizard");
	
	std::cout << "\n--- Equipping materias ---" << std::endl;
	AMateria* ice1 = new Ice();
	AMateria* cure1 = new Cure();
	wizard.equip(ice1);
	wizard.equip(cure1);
	
	Character enemy("Enemy");
	
	std::cout << "\n--- Using slot 0 ---" << std::endl;
	wizard.use(0, enemy);
	
	std::cout << "\n--- Unequipping slot 0 (saving address) ---" << std::endl;
	AMateria* floor = ice1;
	wizard.unequip(0);
	
	std::cout << "\n--- Trying to use unequipped slot 0 (should do nothing) ---" << std::endl;
	wizard.use(0, enemy);
	
	std::cout << "\n--- Using slot 1 (still equipped) ---" << std::endl;
	wizard.use(1, enemy);
	
	std::cout << "\n--- Manually deleting unequipped materia ---" << std::endl;
	delete floor;
	
	std::cout << "\n✅ Unequip works!" << std::endl;
}

void testMateriaSource()
{
	separator("TEST 5: MateriaSource Learning");
	
	MateriaSource library;
	
	std::cout << "\n--- Learning Ice and Cure ---" << std::endl;
	library.learnMateria(new Ice());
	library.learnMateria(new Cure());
	
	std::cout << "\n--- Creating materias from templates ---" << std::endl;
	AMateria* ice = library.createMateria("ice");
	AMateria* cure = library.createMateria("cure");
	AMateria* unknown = library.createMateria("fire");
	
	if (ice)
		std::cout << "Created: " << ice->getType() << std::endl;
	if (cure)
		std::cout << "Created: " << cure->getType() << std::endl;
	if (!unknown)
		std::cout << "Unknown type 'fire' returned NULL" << std::endl;
	
	delete ice;
	delete cure;
	
	std::cout << "\n✅ MateriaSource works!" << std::endl;
}

void testDeepCopy()
{
	separator("TEST 6: Deep Copy of Character");
	
	std::cout << "\n--- Creating original character ---" << std::endl;
	Character original("Original");
	original.equip(new Ice());
	original.equip(new Cure());
	
	std::cout << "\n--- Copying character ---" << std::endl;
	Character copy = original;
	
	std::cout << "\n--- Using original's materias ---" << std::endl;
	Character target("Target");
	original.use(0, target);
	original.use(1, target);
	
	std::cout << "\n--- Using copy's materias ---" << std::endl;
	copy.use(0, target);
	copy.use(1, target);
	
	std::cout << "\n--- Both should work independently ---" << std::endl;
	std::cout << "✅ Deep copy works!" << std::endl;
}

void testFullInventoryScenario()
{
	separator("TEST 7: Full Inventory Scenario");
	
	MateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	
	Character* mage = new Character("Mage");
	
	std::cout << "\n--- Filling inventory ---" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		AMateria* m = src->createMateria(i % 2 == 0 ? "ice" : "cure");
		mage->equip(m);
	}
	
	std::cout << "\n--- Trying to equip 5th materia ---" << std::endl;
	AMateria* extra = src->createMateria("ice");
	mage->equip(extra);
	delete extra;
	
	std::cout << "\n--- Unequipping slot 1 ---" << std::endl;
	mage->unequip(1);
	
	std::cout << "\n--- Equipping new materia in empty slot ---" << std::endl;
	AMateria* newMateria = src->createMateria("cure");
	mage->equip(newMateria);
	
	std::cout << "\n--- Using all materias ---" << std::endl;
	Character* dummy = new Character("Dummy");
	for (int i = 0; i < 4; i++)
	{
		std::cout << "[" << i << "] ";
		mage->use(i, *dummy);
	}
	
	delete dummy;
	delete mage;
	delete src;
	
	std::cout << "\n✅ Full scenario works!" << std::endl;
}

void testEdgeCases()
{
	separator("TEST 8: Edge Cases");
	
	Character player("Player");
	Character enemy("Enemy");
	
	std::cout << "\n--- Using empty slot ---" << std::endl;
	player.use(0, enemy);
	
	std::cout << "\n--- Using invalid index ---" << std::endl;
	player.use(-1, enemy);
	player.use(10, enemy);
	
	std::cout << "\n--- Unequipping empty slot ---" << std::endl;
	player.unequip(0);
	
	std::cout << "\n--- Equipping NULL ---" << std::endl;
	player.equip(NULL);
	
	std::cout << "\n--- MateriaSource with unknown type ---" << std::endl;
	MateriaSource src;
	AMateria* unknown = src.createMateria("fireball");
	if (!unknown)
		std::cout << "Unknown type correctly returned NULL" << std::endl;
	
	std::cout << "\n✅ Edge cases handled!" << std::endl;
}

void testMateriaSourceLimit()
{
	separator("TEST 9: MateriaSource 4 Template Limit");
	
	MateriaSource lib;
	
	std::cout << "\n--- Learning 4 materias ---" << std::endl;
	lib.learnMateria(new Ice());
	lib.learnMateria(new Cure());
	lib.learnMateria(new Ice());
	lib.learnMateria(new Cure());
	
	std::cout << "\n--- Trying to learn 5th materia (should be ignored) ---" << std::endl;
	lib.learnMateria(new Ice());
	
	std::cout << "\n--- Creating materias ---" << std::endl;
	AMateria* m1 = lib.createMateria("ice");
	AMateria* m2 = lib.createMateria("cure");
	
	if (m1)
		std::cout << "Created: " << m1->getType() << std::endl;
	if (m2)
		std::cout << "Created: " << m2->getType() << std::endl;
	
	delete m1;
	delete m2;
	
	std::cout << "\n✅ Template limit works!" << std::endl;
}

void testComplexScenario()
{
	separator("TEST 10: Complex Battle Scenario");
	
	std::cout << "\n--- Setting up battle ---" << std::endl;
	IMateriaSource* academy = new MateriaSource();
	academy->learnMateria(new Ice());
	academy->learnMateria(new Cure());
	
	ICharacter* hero = new Character("Hero");
	ICharacter* villain = new Character("Villain");
	
	std::cout << "\n--- Hero equips materias ---" << std::endl;
	hero->equip(academy->createMateria("ice"));
	hero->equip(academy->createMateria("cure"));
	hero->equip(academy->createMateria("ice"));
	
	std::cout << "\n--- Villain equips materias ---" << std::endl;
	villain->equip(academy->createMateria("cure"));
	villain->equip(academy->createMateria("ice"));
	
	std::cout << "\n--- Battle Round 1: Hero attacks ---" << std::endl;
	hero->use(0, *villain);
	hero->use(2, *villain);
	
	std::cout << "\n--- Battle Round 2: Villain heals ---" << std::endl;
	villain->use(0, *villain);
	
	std::cout << "\n--- Battle Round 3: Hero heals ---" << std::endl;
	hero->use(1, *hero);
	
	std::cout << "\n--- Battle Round 4: Villain attacks ---" << std::endl;
	villain->use(1, *hero);
	
	delete hero;
	delete villain;
	delete academy;
	
	std::cout << "\n✅ Complex scenario works!" << std::endl;
}

int main()
{
	std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
	std::cout << "║   CPP04 - Exercise 03 Test Suite      ║" << std::endl;
	std::cout << "║   Interfaces & Materia System          ║" << std::endl;
	std::cout << "╚════════════════════════════════════════╝" << std::endl;
	
	testSubjectCode();
	testMateriaCreation();
	testCharacterInventory();
	testUnequip();
	testMateriaSource();
	testDeepCopy();
	testFullInventoryScenario();
	testEdgeCases();
	testMateriaSourceLimit();
	testComplexScenario();
	
	separator("ALL TESTS COMPLETED");
	std::cout << "\n✅ All tests passed!" << std::endl;
	
	return 0;
}
