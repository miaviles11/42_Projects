/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientConnection.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-03 15:44:16 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-12-03 15:44:16 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CONNECTION_HPP
# define CLIENT_CONNECTION_HPP

#include <iostream>
#include <string>
#include <ctime>

class Server;
class User;

/** 
 * -R- Manages the TCP connection state, I/O buffers, and authentication status.
 * -R- Each ClientConnection is associated with one User once registered.
**/
class ClientConnection
{
    public:
        ClientConnection(int fd);
        ~ClientConnection();

        /* Connection state */
        bool	isRegistered() const;
        void	setRegistered(bool r);
        void	markPassReceived();
        bool	hasSentPass() const;
        
        /* Socket info */
        int		getFd() const;
        
        /* IO operations */
        void	appendRecvData(const std::string& data);
        bool	hasCompleteLine() const;
        std::string	popLine();
        
        void	queueSend(const std::string& data);
        bool	hasPendingSend() const;
        const std::string& getSendBuffer() const;
        void	clearSentData(size_t bytes);

        /* Activity tracking */
        void	updateActivity();
        time_t	getLastActivity() const;
        time_t  getConnectTime() const;

        /* Connection management */
        void	closeConnection();
        bool	isClosed() const;

        /* User association */
        void	setUser(User* user);
        User*	getUser() const;

    private:
        const int _fd;							//* TCP socket (const after construction)
        
        std::string	_recvBuffer;				//* Incoming data buffer
        std::string _sendBuffer;				//* Outgoing data buffer
        
        bool _registered;						//* True after PASS + NICK + USER sequence
        bool _hasSentPass;						//* True after valid PASS command
        bool _closed;							//* True if connection should be terminated
        
        time_t _lastActivity;					//* Timestamp of last received data
        time_t _connectTime;                    //* Timestamp of connection time
        
        User* _user;							//* Pointer to associated User (NULL until registered)

        ClientConnection(const ClientConnection&);
        ClientConnection& operator=(const ClientConnection&);
};

#endif
