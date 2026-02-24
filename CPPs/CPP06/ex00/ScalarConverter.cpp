/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:57:35 by miaviles          #+#    #+#             */
/*   Updated: 2026/02/24 14:29:27 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

void ScalarConverter::convert(const std::string& literal) {
	switch (detectType(literal)) {
		case CHAR:    
			if (literal.length() == 3) 
				convertFromChar(literal[1]);
			else
				convertFromChar(literal[0]);
			break;
		case INT:     convertFromInt(std::atoi(literal.c_str()));
			break;
		case FLOAT:   convertFromFloat(std::atof(literal.c_str()));
			break;
		case DOUBLE:  convertFromDouble(std::strtod(literal.c_str(), NULL));
			break;
		case SPECIAL: convertFromSpecial(literal);
			break;
		case INVALID: std::cout << "Error: invalid input\n";
			break;
	}
}

ScalarConverter::LiteralType  ScalarConverter::detectType(const std::string& str)
{
	if (str == "nan" || str == "nanf" ||
		str == "+inf" || str == "+inff" ||
		str == "-inf" || str == "-inff" ||
		str == "inf" || str == "inff")
		return (SPECIAL);

	if (str.length() == 3 && str[0] == '\'' &&str[2] == '\'')
		return (CHAR);
	
	if (str.length() == 1 && !std::isdigit(static_cast<unsigned char>(str[0])))
		return (CHAR);

	if (str[str.length() - 1] == 'f' && str.find('.') != std::string::npos)
		return (FLOAT);
	
	if (str.find('.') != std::string::npos && str[str.length() - 1] != 'f')
		return (DOUBLE);

	char* endptr;
	std::strtol(str.c_str(), &endptr, 10);
	if (*endptr == '\0' && str.length() > 0)
		return (INT);

	return (INVALID);
}

void ScalarConverter::convertFromChar(char c)
{
	if (std::isprint(c))
		std::cout << "char: '" << c << "'" << std::endl;
	else
		std::cout << "char: Non displayable" << std::endl;

	std::cout << "int: "    << static_cast<int>(c)    << std::endl;
	std::cout << "float: "  << std::fixed << std::setprecision(1) << static_cast<float>(c)  << "f" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << std::endl;
}

void	ScalarConverter::convertFromInt(int i)
{
	if (i < 0 || i > 127)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(i))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(i) << "'" << std::endl;

	std::cout << "int: " << i << std::endl;
	std::cout << "float: "  << std::fixed << std::setprecision(1) << static_cast<float>(i)  << "f" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(i) << std::endl;
}

void	ScalarConverter::convertFromFloat(float f)
{
	if (f < 0 || f > 127 || std::isnan(f) || std::isinf(f))
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<char>(f)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(f) << "'" << std::endl;
	
	if (f < std::numeric_limits<int>::min() ||
		f > std::numeric_limits<int>::max() ||
		std::isnan(f) || std::isinf(f))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(f) << std::endl;
	
	std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(f) << std::endl;
}

void	ScalarConverter::convertFromDouble(double d)
{
	if (d < 0 || d > 127 || std::isnan(d) || std::isinf(d))
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<char>(d)))
		std::cout << "char: Non displayable" << std::endl;
	else
		std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
	
	if (d < std::numeric_limits<int>::min() ||
		d > std::numeric_limits<int>::max() ||
		std::isnan(d) || std::isinf(d))
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << static_cast<int>(d) << std::endl;
	
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(d) << "f" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(d) << std::endl;}

void	ScalarConverter::convertFromSpecial(const std::string& str)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (str == "nanf" || str == "+inff" || str == "-inff" || str == "inff")
	{
		std::cout << "float: " << str << std::endl;
		std::string doubleVersion = str.substr(0, str.length() - 1);
		std::cout << "double: " << doubleVersion << std::endl;
	}
	else
	{
		std::cout << "float: " << str << "f" << std::endl;
		std::cout << "double: " << str << std::endl;
	}
}