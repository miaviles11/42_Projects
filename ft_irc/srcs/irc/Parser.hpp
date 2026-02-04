/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:33:26 by carlsanc          #+#    #+#             */
/*   Updated: 2025/12/10 20:33:26 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "Message.hpp"
#include <string>

class Parser {
    public:
        // Static method: receives raw string, returns clean structure
        static Message parse(const std::string& rawLine);
    private:
        Parser(); // Not instantiable
        static std::string trim(const std::string& str);
        static std::string toUpper(const std::string& str);
};

#endif
