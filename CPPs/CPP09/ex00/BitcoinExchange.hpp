/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 02:30:57 by miaviles          #+#    #+#             */
/*   Updated: 2026/03/08 02:30:57 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _data;
		bool isValidDate(const std::string &date) const;
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string &dbFile);
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		~BitcoinExchange();

		void loadDatabase(const std::string &dbFile);
		void processInput(const std::string &inputFile) const;
};

#endif