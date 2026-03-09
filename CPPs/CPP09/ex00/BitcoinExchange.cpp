/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 02:30:59 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/08 02:30:59 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string &dbFile)
{
	loadDatabase(dbFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _data(other._data) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_data = other._data;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string &dbFile)
{
	std::ifstream file(dbFile.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");
	
	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::string::size_type pos = line.find(',');
		if (pos == std::string::npos)
			continue;
		std::string date = line.substr(0, pos);
		float rate = static_cast<float>(std::strtod(line.substr(pos + 1).c_str(), NULL));
		_data[date] = rate;
	}
	file.close();
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);
	
	for (size_t i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return (false);
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1 || month < 1 || month > 12 || day < 1)
		return (false);
	
	int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		daysInMonth[1] = 29;

	return (day <= daysInMonth[month - 1]);
}

void BitcoinExchange::processInput(const std::string &inputFile) const
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::string::size_type pos = line.find(" | ");
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, pos);
		std::string valueStr = line.substr(pos + 3);

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad date input => " << date << std::endl;
			continue;
		}

		char *end;
		double value = std::strtod(valueStr.c_str(), &end);
		if (*end != '\0' && *end != '\n')
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		std::map<std::string, float>::const_iterator it = _data.lower_bound(date);
		if (it == _data.end() || it->first != date)
		{
			if (it == _data.begin())
			{
				std::cerr << "Error: date too early." << std::endl;
				continue;
			}
			--it;
		}
		std::cout << date << " => " << value << " = "
				  << (value * it->second) << std::endl;
	}
	file.close();
}


