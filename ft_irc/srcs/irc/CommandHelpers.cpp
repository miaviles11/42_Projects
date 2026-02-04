/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHelpers.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:33:01 by carlsanc          #+#    #+#             */
/*   Updated: 2025/12/17 19:07:30 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CommandHelpers.hpp"
#include "../client/User.hpp"
#include "../irc/NumericReplies.hpp"
#include "../utils/Colors.hpp"
#include <iostream>
#include <sstream>

void sendReply(ClientConnection* client, std::string num, std::string msg)
{
    if (!client || !client->getUser()) return;
    std::string finalMsg = ":ft_irc " + num + " " + client->getUser()->getNickname() + " " + msg + "\r\n";
    client->queueSend(finalMsg);
}

void sendError(ClientConnection* client, std::string num, std::string arg)
{
    if (!client) return;
    std::string msg;

    if (num == ERR_NEEDMOREPARAMS) msg = arg + " :Not enough parameters";
    else if (num == ERR_ALREADYREGISTRED) msg = ":Unauthorized command (already registered)";
    else if (num == ERR_PASSWDMISMATCH) msg = ":Password incorrect";
    else if (num == ERR_NONICKNAMEGIVEN) msg = ":No nickname given";
    else if (num == ERR_ERRONEUSNICKNAME) msg = arg + " :Erroneous nickname";
    else if (num == ERR_NICKNAMEINUSE) msg = arg + " :Nickname is already in use";
    else if (num == ERR_NOSUCHNICK) msg = arg + " :No such nick/channel";
    else if (num == ERR_NOSUCHCHANNEL) msg = arg + " :No such channel";
    else if (num == ERR_CANNOTSENDTOCHAN) msg = arg + " :Cannot send to channel";
    
    else if (num == ERR_NOTONCHANNEL) msg = arg + " :You're not on that channel";
    else if (num == ERR_USERONCHANNEL) msg = arg + " :is already on channel";
    else if (num == ERR_CHANOPRIVSNEEDED) msg = arg + " :You're not channel operator";
    else if (num == ERR_USERSDONTMATCH) msg = ":Cannot change mode for other users";
    else if (num == ERR_UMODEUNKNOWNFLAG) msg = ":Unknown MODE flag";
    else if (num == ERR_INVITEONLYCHAN) msg = arg + " :Cannot join channel (+i)";
    else if (num == ERR_BADCHANNELKEY) msg = arg + " :Cannot join channel (+k)";
    else if (num == ERR_CHANNELISFULL) msg = arg + " :Cannot join channel (+l)";
    else if (num == ERR_USERNOTINCHANNEL) msg = arg + " :They aren't on that channel";
    else if (num == ERR_NOTREGISTERED) msg = ":You have not registered";
    else if (num == ERR_BADCHANMASK) msg = arg + " :Bad Channel Mask";
    else msg = arg + " :Unknown Error";

    sendReply(client, num, msg);
}

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        if (!token.empty()) // Avoid empty tokens
            tokens.push_back(token);
    }
    return tokens;
}

void checkRegistration(ClientConnection* client)
{
    if (client->isRegistered()) return;
    
    User* user = client->getUser();
    // Requirement: Must have sent PASS, have Nick and have User
    if (client->hasSentPass() && !user->getNickname().empty() && !user->getUsername().empty())
    {
        client->setRegistered(true);
        // Standard welcome messages with colors
        sendReply(client, RPL_WELCOME, std::string(":") + BRIGHT_GREEN + "Welcome to the FT_IRC Network " + MAGENTA + user->getPrefix() + RESET);
        sendReply(client, RPL_YOURHOST, std::string(":") + CYAN + "Your host is ft_irc, running version 1.0" + RESET);
        sendReply(client, RPL_CREATED, std::string(":") + CYAN + "This server was created today" + RESET);
        sendReply(client, RPL_MYINFO, std::string(CYAN) + "ft_irc 1.0 io tkl" + RESET); // Supported modes
        
        std::cout << BRIGHT_GREEN << "[SERVER] User registered: " << MAGENTA << user->getNickname() << RESET << std::endl;
    }
}
