/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_op.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:32:35 by carlsanc          #+#    #+#             */
/*   Updated: 2025/12/10 20:32:35 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/Server.hpp"
#include "../client/ClientConnection.hpp"
#include "../client/User.hpp"
#include "../channel/Channel.hpp"
#include "CommandHelpers.hpp"
#include "../irc/NumericReplies.hpp"
#include "../utils/Colors.hpp"
#include <cstdlib>
#include <cstdio>
#include <cctype>

void Server::cmdKick(ClientConnection* client, const Message& msg)
{
    if (!client->isRegistered()) {
        sendError(client, ERR_NOTREGISTERED, "");
        return;
    }
    if (msg.params.size() < 2) return sendError(client, ERR_NEEDMOREPARAMS, "KICK");
    
    std::string chanName = msg.params[0];
    std::string targetNick = msg.params[1];
    std::string comment = (msg.params.size() > 2) ? msg.params[2] : "Kicked";

    Channel* channel = getChannel(chanName);
    if (!channel) return sendError(client, ERR_NOSUCHCHANNEL, chanName);

    // Check privileges
    if (!channel->isOperator(client->getUser()))
        return sendError(client, ERR_CHANOPRIVSNEEDED, chanName);

    // Check if target user is in channel
    User* targetUser = channel->getMember(targetNick);
    if (!targetUser) 
        return sendError(client, ERR_USERNOTINCHANNEL, targetNick + " " + chanName);

    // Get timestamp
    std::string timestamp = getCurrentTimestamp();

    // KICK message
    std::string kickMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                            BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                            " " + BRIGHT_YELLOW + "KICK" + RESET + " " +
                            CYAN + chanName + RESET + " " +
                            targetNick + " :" + RED + comment + RESET + "\r\n";

    channel->broadcast(kickMsg, NULL);

    // Actually remove
    channel->removeMember(targetUser);
    targetUser->leaveChannel(channel);
}

void Server::cmdInvite(ClientConnection* client, const Message& msg)
{
    if (!client->isRegistered()) {
        sendError(client, ERR_NOTREGISTERED, "");
        return;
    }
    if (msg.params.size() < 2) return sendError(client, ERR_NEEDMOREPARAMS, "INVITE");

    std::string targetNick = msg.params[0];
    std::string chanName = msg.params[1];

    Channel* channel = getChannel(chanName);
    if (channel)
    {
        if (!channel->isMember(client->getUser()))
             return sendError(client, ERR_NOTONCHANNEL, chanName);
        
        if (channel->hasMode('i') && !channel->isOperator(client->getUser()))
             return sendError(client, ERR_CHANOPRIVSNEEDED, chanName);
        
        if (channel->getMember(targetNick))
             return sendError(client, ERR_USERONCHANNEL, targetNick + " " + chanName);
        
        channel->addInvite(targetNick);
    }

    // Search target user globally on server
    User* dest = NULL;
    for (size_t i = 0; i < clients_.size(); ++i) {
        if (clients_[i]->isRegistered() && clients_[i]->getUser()->getNickname() == targetNick) {
            dest = clients_[i]->getUser();
            break;
        }
    }
    if (!dest) return sendError(client, ERR_NOSUCHNICK, targetNick);

    // Get timestamp
    std::string timestamp = getCurrentTimestamp();

    // INVITE message
    std::string invMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                            BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                            " " + BRIGHT_YELLOW + "INVITE" + RESET + " " +
                            targetNick + " " + CYAN + chanName + RESET + "\r\n";

    dest->getConnection()->queueSend(invMsg);
    sendReply(client, RPL_INVITING, targetNick + " " + chanName);
}

void Server::cmdMode(ClientConnection* client, const Message& msg)
{
    if (!client->isRegistered()) {
        sendError(client, ERR_NOTREGISTERED, "");
        return;
    }
    if (msg.params.size() < 1) return sendError(client, ERR_NEEDMOREPARAMS, "MODE");

    std::string target = msg.params[0];
    
    // --- USER MODE (Only +i) ---
    if (target[0] != '#')
    {
        if (target != client->getUser()->getNickname())
        {
            sendError(client, ERR_USERSDONTMATCH, "");
            return;
        }
        
        // Query modes
        if (msg.params.size() == 1)
        {
            std::string modes = "+";
            if (client->getUser()->isInvisible()) modes += "i";
            sendReply(client, RPL_UMODEIS, modes);
            return;
        }

        // Change modes
        std::string modeString = msg.params[1];
        char action = '+';
        std::string appliedModes = "";
        
        for (size_t i = 0; i < modeString.length(); ++i)
        {
            if (modeString[i] == '+' || modeString[i] == '-') {
                action = modeString[i];
                continue;
            }
            if (modeString[i] == 'i') {
                bool newC = (action == '+');
                if (client->getUser()->isInvisible() != newC) {
                    client->getUser()->setInvisible(newC);
                    if (appliedModes.find(action) == std::string::npos) // Avoid duplicating sign
                        appliedModes += action;
                    appliedModes += 'i';
                }
            }
        }
        if (!appliedModes.empty()) {
            // Get timestamp
            std::string timestamp = getCurrentTimestamp();

            // MODE message
            std::string modeMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                                    BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                                    " " + BRIGHT_YELLOW + "MODE" + RESET + " " +
                                    target + " :" + BRIGHT_GREEN + appliedModes + RESET + "\r\n";
            client->queueSend(modeMsg);
        }
        return;
    }

    // --- CHANNEL MODE ---
    Channel* channel = getChannel(target);
    if (!channel) return sendError(client, ERR_NOSUCHCHANNEL, target);

    if (msg.params.size() == 1) {
         sendReply(client, RPL_CHANNELMODEIS, target + " " + channel->getModes());
         return;
    }

    if (!channel->isOperator(client->getUser()))
        return sendError(client, ERR_CHANOPRIVSNEEDED, target);

    std::string modeString = msg.params[1];
    size_t paramIdx = 2; // Index for extra arguments (keys, users, limits)
    char action = '+';

    for (size_t i = 0; i < modeString.length(); ++i)
    {
        char mode = modeString[i];
        
        if (mode == '+' || mode == '-') {
            action = mode;
            continue;
        }

        // o: Operator
        if (mode == 'o') {
            if (paramIdx >= msg.params.size()) continue;
            std::string targetNick = msg.params[paramIdx++];
            User* targetUser = channel->getMember(targetNick);
            
            // If user doesn't exist in channel, ignore silently or could send error
            if (targetUser) {
                if (action == '+') channel->addOperator(targetUser);
                else channel->removeOperator(targetUser);
                
                // Get timestamp
                std::string timestamp = getCurrentTimestamp();

                // MODE +o/-o message
                std::string modeMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                                        BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                                        " " + BRIGHT_YELLOW + "MODE" + RESET + " " +
                                        CYAN + target + RESET + " " +
                                        BRIGHT_GREEN + std::string(1, action) + "o" + RESET + " " +
                                        targetNick + "\r\n";
                channel->broadcast(modeMsg, NULL);
            } else {
                 sendError(client, ERR_USERNOTINCHANNEL, targetNick + " " + target);
            }
        }
        // k: Key
        else if (mode == 'k') {
            if (action == '+') {
                if (paramIdx >= msg.params.size()) continue;
                std::string key = msg.params[paramIdx++];
                
                // [FIX] Validate that key has no spaces (RFC)
                if (key.find(' ') != std::string::npos) continue;

                channel->setKey(key);
                // Get timestamp
                std::string timestamp = getCurrentTimestamp();

                // MODE +k message
                std::string modeMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                                        BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                                        " " + BRIGHT_YELLOW + "MODE" + RESET + " " +
                                        CYAN + target + RESET + " " +
                                        BRIGHT_GREEN + std::string(1, action) + "k" + RESET + " " +
                                        key + "\r\n";
                channel->broadcast(modeMsg, NULL);
            } else {
                // [FIX RFC] Permissive mode: allows -k without parameter for OPs
                std::string keyParam = "";
                if (paramIdx < msg.params.size())
                    keyParam = msg.params[paramIdx++];
                
                // Only verify if key was provided
                if (!keyParam.empty() && channel->getKey() != keyParam) {
                    sendError(client, ERR_BADCHANNELKEY, channel->getName());
                    continue;
                }
                
                channel->setKey("");
                // Get timestamp
                std::string timestamp = getCurrentTimestamp();

                // MODE -k message
                std::string modeMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                                        BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                                        " " + BRIGHT_YELLOW + "MODE" + RESET + " " +
                                        CYAN + target + RESET + " " +
                                        BRIGHT_GREEN + "-k" + RESET + " *\r\n";
                channel->broadcast(modeMsg, NULL);
            }
        }
        // l: Limit
        else if (mode == 'l') {
            if (action == '+') {
                if (paramIdx >= msg.params.size()) continue;
                std::string limitStr = msg.params[paramIdx++];
                
                // [FIX SECURITY] Validate it's numeric before atoi
                bool isNumeric = true;
                size_t start = 0;
                if (!limitStr.empty() && (limitStr[0] == '-' || limitStr[0] == '+')) start = 1;
                
                for (size_t j = start; j < limitStr.length(); ++j) {
                    if (!std::isdigit(limitStr[j])) {
                        isNumeric = false;
                        break;
                    }
                }
                
                // If not a number or negative, ignore
                if (!isNumeric || limitStr.empty()) continue;

                int limit = std::atoi(limitStr.c_str());
                // A limit of 0 or negative makes no sense in this context
                if (limit <= 0) continue; 

                channel->setLimit(limit);
                char buff[20];
                std::sprintf(buff, "%d", limit);
                // Get timestamp
                std::string timestamp = getCurrentTimestamp();

                // MODE +l message
                std::string modeMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                                        BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                                        " " + BRIGHT_YELLOW + "MODE" + RESET + " " +
                                        CYAN + target + RESET + " " +
                                        BRIGHT_GREEN + std::string(1, action) + "l" + RESET + " " +
                                        std::string(buff) + "\r\n";
                channel->broadcast(modeMsg, NULL);
            } else {
                channel->setLimit(0); // 0 means no limit
                // Get timestamp
                std::string timestamp = getCurrentTimestamp();

                // MODE -l message
                std::string modeMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                                        BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                                        " " + BRIGHT_YELLOW + "MODE" + RESET + " " +
                                        CYAN + target + RESET + " " +
                                        BRIGHT_GREEN + std::string(1, action) + "l" + RESET + "\r\n";
                channel->broadcast(modeMsg, NULL);
            }
        }
        // i: Invite Only | t: Topic Restricted
        else if (mode == 'i' || mode == 't') {
            channel->setMode(mode, (action == '+'));
            // Get timestamp
            std::string timestamp = getCurrentTimestamp();
            std::string mStr(1, mode);

            // MODE +i/+t message
            std::string modeMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                                    BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                                    " " + BRIGHT_YELLOW + "MODE" + RESET + " " +
                                    CYAN + target + RESET + " " +
                                    BRIGHT_GREEN + std::string(1, action) + mStr + RESET + "\r\n";
            channel->broadcast(modeMsg, NULL);
            
        }
    }
}
