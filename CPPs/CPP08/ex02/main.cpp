/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:32:37 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/08 01:32:37 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <list>

void testSubjectExample()
{
	std::cout << "\n===== SUBJECT TEST =====" << std::endl;

	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);

	std::cout << "Top: " << mstack.top() << std::endl;

	mstack.pop();

	std::cout << "Size after pop: " << mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	std::cout << "Iterating stack:" << std::endl;

	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
}

void testCopyConstructor()
{
	std::cout << "\n===== COPY CONSTRUCTOR TEST =====" << std::endl;

	MutantStack<int> original;

	original.push(1);
	original.push(2);
	original.push(3);

	MutantStack<int> copy(original);

	std::cout << "Original:" << std::endl;

	for (MutantStack<int>::iterator it = original.begin(); it != original.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << "Copy:" << std::endl;

	for (MutantStack<int>::iterator it = copy.begin(); it != copy.end(); ++it)
		std::cout << *it << std::endl;
}

void testIteratorModification()
{
	std::cout << "\n===== ITERATOR MODIFICATION TEST =====" << std::endl;

	MutantStack<int> stack;

	stack.push(10);
	stack.push(20);
	stack.push(30);

	for (MutantStack<int>::iterator it = stack.begin(); it != stack.end(); ++it)
		*it += 1;

	std::cout << "Modified values:" << std::endl;

	for (MutantStack<int>::iterator it = stack.begin(); it != stack.end(); ++it)
		std::cout << *it << std::endl;
}

void testConstIterator()
{
	std::cout << "\n===== CONST ITERATOR TEST =====" << std::endl;

	MutantStack<int> stack;

	stack.push(7);
	stack.push(14);
	stack.push(21);

	const MutantStack<int> constStack(stack);

	for (MutantStack<int>::const_iterator it = constStack.begin(); it != constStack.end(); ++it)
		std::cout << *it << std::endl;
}

void testComparisonWithList()
{
	std::cout << "\n===== COMPARISON WITH LIST =====" << std::endl;

	MutantStack<int> mstack;
	std::list<int> list;

	for (int i = 0; i < 5; i++)
	{
		mstack.push(i);
		list.push_back(i);
	}

	std::cout << "MutantStack:" << std::endl;

	for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << "List:" << std::endl;

	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
		std::cout << *it << std::endl;
}

int main()
{
	testSubjectExample();
	testCopyConstructor();
	testIteratorModification();
	testConstIterator();
	testComparisonWithList();

	return 0;
}