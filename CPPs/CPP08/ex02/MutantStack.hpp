/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:32:52 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/08 01:32:52 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <iostream>

template <typename T>
class MutantStack : public std::stack<T>
{
	public:
		typedef typename std::stack<T>::container_type::iterator iterator;
		typedef typename std::stack<T>::container_type::const_iterator const_iterator;

		MutantStack();
		MutantStack(const MutantStack &other);
		MutantStack &operator=(const MutantStack &other);
		~MutantStack();

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
};

#include "MutantStack.tpp"

#endif