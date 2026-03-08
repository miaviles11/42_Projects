/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:15:20 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/08 01:21:53 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

class Span {
	private:
		std::vector<int> _numbers;
		unsigned int _max;
	public:
		Span();
		Span(unsigned int N);
		Span(const Span &other);
		Span &operator=(const Span &other);
		~Span();

		void addNumber(int i);
		int shortestSpan();
		int longestSpan();

		template <typename Iterator>
		void addRange(Iterator begin, Iterator end)
		{
			if (_numbers.size() + (size_t)std::distance(begin, end) > _max)
				throw std::runtime_error("Maximum number achieved");
			_numbers.insert(_numbers.end(), begin, end);
		}
};

#endif