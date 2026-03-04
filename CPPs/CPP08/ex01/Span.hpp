/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 19:15:20 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/04 20:04:47 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>


class Span {
	private:
		std::vector v;
		std::list l;
	public:
		Span();
		Span(unsigned int N);
		Span(const Span &other);
		Span operator=(const Span &other);
		~Span();

		void addNumber(int i);
		int shortestSpan();
		int longestSpan();

};

#endif