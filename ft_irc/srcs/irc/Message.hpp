/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:33:08 by carlsanc          #+#    #+#             */
/*   Updated: 2025/12/10 20:33:08 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>
#include <vector>

struct Message {
    std::string prefix;      // Optional (e.g.: :nick!user@host)
    std::string command;     // The command (e.g.: PRIVMSG, JOIN)
    std::vector<std::string> params; // Arguments (e.g.: #channel)

    // Helper for debugging
    bool isValid() const { return !command.empty(); }
};

#endif
