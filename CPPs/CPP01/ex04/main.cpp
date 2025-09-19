/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 16:20:44 by miaviles          #+#    #+#             */
/*   Updated: 2025/09/01 19:23:09 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

std::string replaceAll(const std::string& line, const std::string& s1, const std::string& s2)
{
	std::string result;
	size_t pos = 0;
	size_t found;

	while ((found = line.find(s1, pos)) != std::string::npos)
	{
		result += line.substr(pos, found - pos);
		result += s2;
		pos = found + s1.length();
	}
	result += line.substr(pos);
	return (result);
}

bool processFile(const std::string& filename, const std::string& s1, const std::string& s2)
{
    std::ifstream inputFile(filename.c_str());
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Cannot open file '" << filename << "'" << std::endl;
        return (false);
    }

    std::string outputFilename = filename + ".replace";
    std::ofstream outputFile(outputFilename.c_str());
    if (!outputFile.is_open())
    {
        std::cerr << "Error: Cannot create output file" << std::endl;
        inputFile.close();
        return (false);
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        outputFile << replaceAll(line, s1, s2);
        if (!inputFile.eof())
            outputFile << std::endl;
    }
    
    inputFile.close();
    outputFile.close();
    return (true);
}

bool	validateArguments(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: ./replace <filename> <s1> <s2>" << std::endl;
		return (false); 
	}
	std::string s1 = argv[2];
	if (s1.empty())
	{
		std::cerr << "Error: s1 cannot be empty" << std::endl;
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv)
{
 	if (!validateArguments(argc, argv))
		return (1);

	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];

	if (!processFile(filename, s1, s2))
		return (1);

	std::cout << "Successfully created " << filename << ".replace" << std::endl;
    return (0);
}