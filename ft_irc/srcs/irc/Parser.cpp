/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:57:10 by carlsanc          #+#    #+#             */
/*   Updated: 2025/12/10 19:57:10 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <iostream>
#include <algorithm> // for transform

std::string Parser::trim(const std::string& str) {
    std::string result = str;
    // Remove \r and \n from the end (common in IRC)
    size_t end = result.find_last_not_of("\r\n");
    if (end != std::string::npos)
        result = result.substr(0, end + 1);
    else
        return ""; // Empty string or only line breaks
    return result;
}

std::string Parser::toUpper(const std::string& str) {
    std::string upper = str;
    for (size_t i = 0; i < upper.length(); ++i)
        upper[i] = std::toupper(upper[i]);
    return upper;
}

Message Parser::parse(const std::string& rawLine) {
    Message msg;
    
    // 1. Basic cleanup
    std::string line = trim(rawLine);
    if (line.empty()) return msg;

    size_t pos = 0;
    size_t len = line.length();

    // 2. Parse Prefix (Optional)
    // The prefix starts with ':' but only if it's the FIRST character of the line
    if (pos < len && line[pos] == ':') {
        size_t spacePos = line.find(' ', pos);
        if (spacePos != std::string::npos) {
            msg.prefix = line.substr(pos + 1, spacePos - pos - 1); // +1 to skip the ':'
            pos = line.find_first_not_of(' ', spacePos); // Skip spaces
        } else {
            // Rare case: Line only contains ":something" (invalid but shouldn't crash)
            return msg; 
        }
    }

    // If we reach the end with only prefix, return
    if (pos == std::string::npos || pos >= len) return msg;

    // 3. Parse Command
    size_t spacePos = line.find(' ', pos);
    if (spacePos != std::string::npos) {
        msg.command = toUpper(line.substr(pos, spacePos - pos));
        pos = line.find_first_not_of(' ', spacePos);
    } else {
        // Case: Command without parameters (e.g.: "QUIT")
        msg.command = toUpper(line.substr(pos));
        return msg;
    }

    // 4. Parse Parameters
    while (pos != std::string::npos && pos < len) {
        // Check Trailing Parameter (starts with ':')
        if (line[pos] == ':') {
            // Take ALL the rest of the line as is (without the ':')
            msg.params.push_back(line.substr(pos + 1));
            break; // No more parameters after the trailing
        }
        
        // Normal parameter (separated by space)
        spacePos = line.find(' ', pos);
        if (spacePos != std::string::npos) {
            msg.params.push_back(line.substr(pos, spacePos - pos));
            pos = line.find_first_not_of(' ', spacePos);
        } else {
            // Last parameter (without previous ':')
            msg.params.push_back(line.substr(pos));
            break;
        }
    }

    return msg;
}
