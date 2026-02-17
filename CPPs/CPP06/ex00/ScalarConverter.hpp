/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:58:11 by miaviles          #+#    #+#             */
/*   Updated: 2026/02/17 16:58:11 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <limits>

class ScalarConverter {
	private:
		ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter &operator=(const ScalarConverter &other);
		~ScalarConverter();

		enum LiteralType {
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			SPECIAL,
			INVALID
		};

		static LiteralType  detectType(const std::string& str);
		static void         convertFromChar(char c);
		static void         convertFromInt(int i);
		static void         convertFromFloat(float f);
		static void         convertFromDouble(double d);
		static void         convertFromSpecial(const std::string& str);

	public:
		static void convert(const std::string& literal);
};

#endif