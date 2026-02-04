/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_msg.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:32:52 by carlsanc          #+#    #+#             */
/*   Updated: 2026-01-15 20:15:00 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../server/Server.hpp"
#include "../client/ClientConnection.hpp"
#include "../client/User.hpp"
#include "../channel/Channel.hpp"
#include "CommandHelpers.hpp"
#include "../irc/NumericReplies.hpp"
#include "../utils/Colors.hpp"

void Server::cmdPrivMsg(ClientConnection* client, const Message& msg)
{
    if (!client->isRegistered()) {
        sendError(client, ERR_NOTREGISTERED, "");
        return;
    }

    if (msg.params.size() < 2) {
        return sendError(client, ERR_NEEDMOREPARAMS, "PRIVMSG");
    }

    User* sender = client->getUser();
    std::string target = msg.params[0];
    std::string text = msg.params[1];

    // Get timestamp
    std::string timestamp = getCurrentTimestamp();
    
    // Build message with colors
    std::string fullMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                          BRIGHT_CYAN + ":" + sender->getPrefix() + RESET +
                          " " + BRIGHT_YELLOW + "PRIVMSG" + RESET + " " +
                          CYAN + target + RESET + " :" + text + "\r\n";

    // CASE 1: Message to channel
    if (target[0] == '#')
    {
        Channel* channel = getChannel(target);
        
        if (!channel)
            return sendError(client, ERR_NOSUCHCHANNEL, target);
        
        if (!channel->isMember(sender))
            return sendError(client, ERR_CANNOTSENDTOCHAN, target);
        
        // Broadcast to all members except sender
        channel->broadcast(fullMsg, sender);
        
        // Force immediate send for all recipients
        const std::vector<User*>& members = channel->getMembers();
        for (std::vector<User*>::const_iterator it = members.begin(); it != members.end(); ++it)
        {
            User* member = *it;
            if (member == sender)
                continue;
            
            ClientConnection* conn = member->getConnection();
            if (conn && conn->hasPendingSend())
                sendPendingData(conn);
        }
    }
    // CASE 2: Private message
    else
    {
        // Find user by nickname
        User* recipient = NULL;
        for (size_t i = 0; i < clients_.size(); ++i)
        {
            if (clients_[i]->isRegistered() && 
                clients_[i]->getUser()->getNickname() == target)
            {
                recipient = clients_[i]->getUser();
                break;
            }
        }
        
        if (!recipient)
            return sendError(client, ERR_NOSUCHNICK, target);
        
        ClientConnection* recipientConn = recipient->getConnection();
        if (recipientConn)
        {
            recipientConn->queueSend(fullMsg);
            sendPendingData(recipientConn);
        }
    }
}

void Server::cmdNotice(ClientConnection* client, const Message& msg)
{
    // NOTICE should not send error responses per RFC
    if (!client->isRegistered() || msg.params.size() < 2)
        return;

    std::string target = msg.params[0];
    std::string text = msg.params[1];
    std::string timestamp = getCurrentTimestamp();

    // CASE 1: NOTICE to channel
    if (target[0] == '#')
    {
        Channel* channel = getChannel(target);
        if (channel && channel->isMember(client->getUser()))
        {
            std::string fullMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                                  BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                                  " " + BRIGHT_YELLOW + "NOTICE" + RESET + " " +
                                  CYAN + target + RESET + " :" + text + "\r\n";
            channel->broadcast(fullMsg, client->getUser());
        }
    }
    // CASE 2: Private NOTICE
    else
    {
        for (size_t i = 0; i < clients_.size(); ++i)
        {
            if (clients_[i]->isRegistered() && clients_[i]->getUser()->getNickname() == target)
            {
                std::string fullMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                                      BRIGHT_CYAN + ":" + client->getUser()->getPrefix() + RESET +
                                      " " + BRIGHT_YELLOW + "NOTICE" + RESET + " " +
                                      CYAN + target + RESET + " :" + text + "\r\n";
                clients_[i]->queueSend(fullMsg);
                break;
            }
        }
    }
}
