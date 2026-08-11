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
#include <cctype> // needed for std::isdigit (portable C++98 include)

/*
 * BitcoinExchange loads a CSV database (date,exchange_rate) into a std::map,
 * then reads an input file ("date | value") and, for each line, prints
 * value * exchange_rate using the rate of that date (or the closest EARLIER
 * date if the exact date is not in the database).
 *
 * std::map is the required container here: it keeps the dates sorted, which
 * makes "find the closest earlier date" a simple lower_bound call.
 */

// Default constructor: empty database.
BitcoinExchange::BitcoinExchange() {}

// Convenience constructor: build the object and load the database at once.
BitcoinExchange::BitcoinExchange(const std::string &dbFile)
{
	loadDatabase(dbFile);
}

// Copy constructor: duplicate the internal map.
BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _data(other._data) {}

// Copy assignment operator (Orthodox Canonical Form).
BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_data = other._data;
	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

// Read the CSV database file "date,rate" and store every entry in the map.
void BitcoinExchange::loadDatabase(const std::string &dbFile)
{
	std::ifstream file(dbFile.c_str());
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database file.");

	std::string line;
	std::getline(file, line); // skip the CSV header line ("date,exchange_rate")

	while (std::getline(file, line))
	{
		// Each valid line is "date,rate"; split on the comma.
		std::string::size_type pos = line.find(',');
		if (pos == std::string::npos)
			continue; // ignore malformed lines
		std::string date = line.substr(0, pos);
		// Convert the text after the comma into a float rate.
		float rate = static_cast<float>(std::strtod(line.substr(pos + 1).c_str(), NULL));
		_data[date] = rate;
	}
	file.close();
}

// Check that a string is a real calendar date in the format "YYYY-MM-DD".
bool BitcoinExchange::isValidDate(const std::string &date) const
{
	// The length and the two dashes must be exactly where we expect them.
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return (false);

	// Every other character must be a digit.
	for (size_t i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue; // skip the dash positions
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return (false);
	}

	// Extract the numeric year / month / day.
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	// Basic range checks.
	if (year < 1 || month < 1 || month > 12 || day < 1)
		return (false);

	// Days per month; February is adjusted below for leap years.
	int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

	// Leap year rule: divisible by 4, except centuries not divisible by 400.
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		daysInMonth[1] = 29;

	return (day <= daysInMonth[month - 1]);
}

// Read the input file, validate each line and print the converted value.
void BitcoinExchange::processInput(const std::string &inputFile) const
{
	std::ifstream file(inputFile.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line); // skip the header line ("date | value")

	while (std::getline(file, line))
	{
		// Lines must use the exact separator " | " (space-pipe-space).
		std::string::size_type pos = line.find(" | ");
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, pos);
		std::string valueStr = line.substr(pos + 3);

		// Validate the date part.
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		// Parse the value; 'end' must reach the end of the string, otherwise
		// there were leftover/invalid characters (e.g. "1.2abc").
		char *end;
		double value = std::strtod(valueStr.c_str(), &end);
		if (*end != '\0' && *end != '\n')
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		// The subject restricts the value to the range [0, 1000].
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

		// lower_bound returns the first date >= the requested one.
		std::map<std::string, float>::const_iterator it = _data.lower_bound(date);
		// If it is not an exact match, step back to the closest EARLIER date.
		if (it == _data.end() || it->first != date)
		{
			if (it == _data.begin())
			{
				// The date is earlier than anything in the database.
				std::cerr << "Error: date too early." << std::endl;
				continue;
			}
			--it;
		}
		// Print "date => value = value * rate".
		std::cout << date << " => " << value << " = "
				  << (value * it->second) << std::endl;
	}
	file.close();
}
