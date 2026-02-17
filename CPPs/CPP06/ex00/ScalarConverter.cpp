/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 16:57:35 by miaviles          #+#    #+#             */
/*   Updated: 2026/02/17 16:57:35 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

void ScalarConverter::convert(const std::string& literal) {
    switch (detectType(literal)) {
        case CHAR:    convertFromChar(literal[1]);
			break;
        case INT:     convertFromInt(std::atoi(literal.c_str()));
			break;
        case FLOAT:   convertFromFloat(std::atof(literal.c_str()));
			break;
        case DOUBLE:  convertFromDouble(std::strtod(literal.c_str(), nullptr));
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
        str == "-inf" || str == "-inff")
        return (SPECIAL);

	if (str.length() == 3 && str[0] == '\'' &&str[2] == '\'')
		return (CHAR);
	
	if (str[str.length() - 1] == 'f' && str.find('.') != std::string::npos)
		return (FLOAT);
	
	if (str.find('.') != std::string::npos && str[str.length() - 1] != 'f')
		return (DOUBLE);

	char* endptr;
	std::strtol(str.c_str(), &endptr, 10);
	if (*endptr == '\0')
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
	std::cout << "float: "  << static_cast<float>(c)  << "f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << std::endl;
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
	std::cout << "float: "  << std::fixed << std::setprecision(1) << static_cast<float>(i)  << "f" << std::endl;

void	ScalarConverter::convertFromDouble(double d)
{
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(i) << std::endl;
}

void	ScalarConverter::convertFromSpecial(const std::string& str)
{

}