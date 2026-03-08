/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:15:23 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/08 01:15:01 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span() : _max(0) {}

Span::Span(unsigned int N) : _max(N) {}

Span::Span(const Span &other) {
	_max = other._max;
	_numbers = other._numbers;
}

Span &Span::operator=(const Span &other) {
	if (this != &other)
	{
		_max = other._max;
		_numbers = other._numbers;
	}
	return (*this);
}

Span::~Span() {}

void Span::addNumber(int i)
{
	if (_numbers.size() >= _max)
		throw std::runtime_error("Maximum number reached");
	else
		_numbers.push_back(i);
}

int Span::shortestSpan()
{
	int min;
	int diff;

	if (_numbers.size() < 2)
		throw std::runtime_error("Two or more numbers needed");
	std::sort(_numbers.begin(), _numbers.end());

	min = _numbers[1] - _numbers[0];
	for (size_t i = 1; i < _numbers.size() - 1; i++)
	{
		diff = _numbers[i + 1] - _numbers[i];
		if (diff < min)
			min = diff;
	}
	return (min);
}

int Span::longestSpan()
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Two or more numbers needed");
	return (*std::max_element(_numbers.begin(), _numbers.end())
			- *std::min_element(_numbers.begin(), _numbers.end()));
}