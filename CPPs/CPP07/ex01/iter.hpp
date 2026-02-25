/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 01:20:52 by miaviles          #+#    #+#             */
/*   Updated: 2026/02/25 01:20:52 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>
#include <cstddef>

template <typename T, typename F>
void iter(T *array, const size_t len, F func)
{
	for (size_t i = 0; i < len; i++)
		func(array[i]);
}

template <typename T, typename F>
void iter(const T *array, const size_t len, F func)
{
	for (size_t i = 0; i < len; i++)
		func(array[i]);
}

#endif