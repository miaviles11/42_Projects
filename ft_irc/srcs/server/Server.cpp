/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:15:15 by miaviles          #+#    #+#             */
/*   Updated: 2025/12/17 19:05:27 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "../client/ClientConnection.hpp"
#include "../client/User.hpp"
#include "../channel/Channel.hpp"
#include "../net/SocketUtils.hpp"
#include "../irc/Parser.hpp"
#include "../utils/Colors.hpp"

#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <sys/socket.h>
#include <ctime>

//* ============================================================================
//* CONSTRUCTOR Y DESTRUCTOR
//* ============================================================================

Server::Server(int port, const std::string& password) : port_(port), 
	password_(password), server_fd_(-1), running_(false)
{
	initCommands();
    std::cout << CYAN << "[SERVER] Initializing on port " << port << RESET << std::endl;	
}

Server::~Server()
{
    std::cout << YELLOW << "[SERVER] Shutting down..." << RESET << std::endl;

	//* CLOSE SERVER SOCKET
	if (server_fd_ >= 0)
		close(server_fd_);

	//* CLEANUP CLIENTS
	for (size_t i = 0; i < clients_.size(); i++)
	{
		if (clients_[i])
		{
			User* user = clients_[i]->getUser();		//* Get associated User before deleting connection

			close(clients_[i]->getFd());
			delete clients_[i];							//* Delete ClientConnection
			
			if (user)								    //* Delete User if exists
				delete user;
		}
	}

	//* CLEANUP CHANNELS
	for (size_t i = 0; i < channels_.size(); ++i)
		delete channels_[i];
}

//* ============================================================================
//* SETUP - Uses SocketUtils for all socket operations
//* ============================================================================

bool Server::setupServerSocket()
{
	server_fd_ = SocketUtils::createServerSocket();               //* Create a non-blocking TCP socket for the server
	if (server_fd_ < 0)
		return (false);
	
	if (!SocketUtils::bindSocket(server_fd_, port_))              //* Bind socket to specified port (associates socket with network address)
	{
		close(server_fd_);
		server_fd_ = -1;
		return (false);
	}

	if (!SocketUtils::listenSocket(server_fd_, SOMAXCONN))        //* Mark socket as passive (ready to accept connections), SOMAXCONN = max queue size
	{
		close(server_fd_);
		server_fd_ = 1;
		return (false);
	}
	return (true);
}

bool Server::start()
{
	std::cout << CYAN << "[SERVER] Starting..." << RESET << std::endl;

	if (!setupServerSocket())
		return (false);
	
	//* ADD SERVER SOCKET TO POLL
	struct pollfd server_pfd;              //* POSIX structure to monitor file descriptors for I/O events
	server_pfd.fd = server_fd_;            //* Tell poll() which socket to monitor (server's listening socket)
	server_pfd.events = POLLIN;            //* Register interest in read events (POLLIN = data available to read = new connection ready)
	server_pfd.revents = 0;                //* Clear "returned events" field (poll() fills this with actual events that occurred)
	poll_fds_.push_back(server_pfd);       //* Add to vector so poll() can monitor server socket + all client sockets together (MULTIPLE USERS!)
	
	running_ = true;
	std::cout << GREEN << "[SERVER] ✓ Ready on port " << port_ << RESET << std::endl;
	return (true);
}

void Server::stop()
{
    running_ = false;
}

//* ============================================================================
//* MAIN LOOP - SINGLE poll() (required by 42)
//* ============================================================================

void Server::run()
{
    std::cout << CYAN << "[SERVER] Main loop started" << RESET << std::endl;

    while (running_)
    {
        // ------------------------------------------------------------------
        //  CRITICAL FIX - events weren't being notified correctly, so I made this little fix :D
        // ------------------------------------------------------------------
        // We check if any client has pending data to send.
        // If so, we tell poll() to notify us when we can write (POLLOUT).
        // If not, we only listen if they send us data (POLLIN).
        for (size_t i = 0; i < poll_fds_.size(); ++i)
        {
            // The server socket only listens for new connections (POLLIN)
            if (poll_fds_[i].fd == server_fd_) 
                continue;

            ClientConnection* client = findClientByFd(poll_fds_[i].fd);
            if (client)
            {
                if (client->hasPendingSend())
                {
                    // We want to read (if client writes) OR write (if there's pending buffer)
                    poll_fds_[i].events = POLLIN | POLLOUT;
                }
                else
                {
                    // We're only interested in reading
                    poll_fds_[i].events = POLLIN;
                }
            }
        }

        //* WAIT FOR ACTIVITY on any socket (server + all clients)
        //* poll() with "-1" blocks here until something happens
        int poll_count = poll(&poll_fds_[0], poll_fds_.size(), -1);
        
        //* HANDLE POLL ERRORS
        if (poll_count < 0)
        {
            if (errno == EINTR)              //* Interrupted by signal (e.g., Ctrl+C) - not fatal
                continue;                    //* Restart poll() loop
            std::cerr << "[ERROR] poll() failed" << std::endl; //* If it is other error...
            break;                           //* Fatal error - exit loop
        }
        
        //* CHECK EACH SOCKET for activity
        // We don't increment 'i' automatically in the for loop.
        // We only increment if we DON'T delete the current client.
        for (size_t i = 0; i < poll_fds_.size(); /* empty */)
        {
            // Case 1: Server Socket (New connections)
            if (poll_fds_[i].fd == server_fd_)
            {
                if (poll_fds_[i].revents & POLLIN)
                    acceptNewConnections();
                i++; // Server socket is never deleted here
            }
            // Case 2: Client Socket
            else
            {
                // If it returns false, the client was deleted and 'poll_fds_' was reduced.
                // We don't increment 'i' because the next client is now at 'i'.
                if (!handleClientEvent(i))
                    continue; 
                
                i++; // Client still alive, move to next
            }
        }
    }
    std::cout << YELLOW << "[SERVER] Main loop ended" << RESET << std::endl;
}

//* ============================================================================
//* GETTERS
//* ============================================================================

const std::string& Server::getPassword() const
{
	return (password_);
}

int Server::getClientCount() const
{
	return (clients_.size());
}

//* ============================================================================
//* ACCEPT - Uses SocketUtils
//* ============================================================================

//* ACCEPT NEW CONNECTIONS
//* Core function that handles incoming client connections to the IRC server.
//* Creates ClientConnection and User objects, links them together, and adds
//* the new client to both the clients_ vector and poll monitoring system.
//* Uses non-blocking socket operations to accept multiple pending connections.

void Server::acceptNewConnections()
{
	//* ACCEPT ALL PENDING CONNECTIONS in a loop (non-blocking)
	while (true)
	{
		std::string client_ip;                                             //* Will store client's IP address
		int client_fd = SocketUtils::acceptClient(server_fd_, client_ip);  //* Accept one connection, get client socket fd and IP

		//* BREAK if no more connections pending (non-blocking would return -1)
		if (client_fd < 0)
			break;

		//* CREATE CLIENT CONNECTION OBJECT (manages socket I/O and buffers)
		ClientConnection* connection = new ClientConnection(client_fd);

		//* CREATE USER OBJECT (stores IRC user data: nick, username, channels, etc.)
		User* user = new User();
		user->setHostname(client_ip);                                       //* Store client's IP address in user profile
		user->setConnection(connection);                                    //* Link User -> ClientConnection (bidirectional relationship)
		connection->setUser(user);                                          //* Link ClientConnection -> User

		//* REGISTER CLIENT in server's client list
		clients_.push_back(connection);                                     //* Add to vector for tracking all connected clients
		addClientToPoll(connection);                                        //* Add client's fd to poll_fds_ for I/O monitoring

		//* SEND WELCOME MESSAGE with authentication instructions
		std::string welcome = 
			":ft_irc NOTICE * :" + std::string(BRIGHT_GREEN) + "*** Welcome to ft_irc!" + RESET + "\r\n"
			":ft_irc NOTICE * :" + std::string(CYAN) + "*** To get started, please authenticate:" + RESET + "\r\n"
			":ft_irc NOTICE * :" + std::string(CYAN) + "***   1. PASS <password>" + RESET + "\r\n"
			":ft_irc NOTICE * :" + std::string(CYAN) + "***   2. NICK <your_nickname>" + RESET + "\r\n"
			":ft_irc NOTICE * :" + std::string(CYAN) + "***   3. USER <username> 0 * :<realname>" + RESET + "\r\n";
		connection->queueSend(welcome);

		std::cout << GREEN << "[SERVER] ✓ New client from " << client_ip 
				  << " (fd=" << client_fd << ", total=" << clients_.size() << ")" << RESET << std::endl;
	}
}

//* ============================================================================
//* HANDLE CLIENT EVENTS
//* ============================================================================

//* HANDLE CLIENT EVENT
//* Core event handler that processes all socket activity for connected clients.
//* Called by main loop when poll() detects activity on a client socket.
//* Handles three main scenarios:
//* 1. Socket errors/disconnections (POLLERR, POLLHUP, POLLNVAL)
//* 2. Incoming data ready to read (POLLIN)
//* 3. Socket ready for writing (POLLOUT)
//* Manages the complete client I/O lifecycle: receive -> buffer -> parse -> respond

bool Server::handleClientEvent(size_t poll_index)
{
    int fd = poll_fds_[poll_index].fd;
    short revents = poll_fds_[poll_index].revents;
    ClientConnection* client = findClientByFd(fd);

    // Safety check: if client doesn't exist, clean up orphan fd
    if (!client)
    {
        poll_fds_.erase(poll_fds_.begin() + poll_index);
        close(fd);
        return false;
    }

    // 1. ERRORS / DISCONNECTION (POLLERR, POLLHUP, POLLNVAL)
    if (revents & (POLLERR | POLLHUP | POLLNVAL))
    {
        std::cout << YELLOW << "[SERVER] Client fd=" << fd
                  << " disconnected (poll error)" << RESET << std::endl;
        processClientCommands(client); // Process remaining commands (optional)
        disconnectClient(poll_index);
        return false; // Return false because we deleted the client
    }

    // 2. READ (POLLIN)
    if (revents & POLLIN)
    {
        char buffer[4096];
        ssize_t bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);

        if (bytes > 0)
        {
            buffer[bytes] = '\0';
            client->appendRecvData(std::string(buffer, bytes));
            client->updateActivity();

            // Process commands (this executes NICK, JOIN, QUIT, etc.)
            processClientCommands(client);

            // CRITICAL: Check if client requested disconnection (QUIT)
            if (client->isClosed())
            {
                disconnectClient(poll_index);
                return false; // Client deleted, exit
            }

            // Try to send immediately to reduce latency
            if (client->hasPendingSend())
            {
                sendPendingData(client);
            }
        }
        else if (bytes == 0) // Connection closed by client (EOF)
        {
            std::cout << YELLOW << "[SERVER] Client fd=" << fd
                      << " closed connection" << RESET << std::endl;
            processClientCommands(client);
            disconnectClient(poll_index);
            return false;
        }
        else // Error in recv
        {
            if (errno != EAGAIN && errno != EWOULDBLOCK)
            {
                std::cerr << BRIGHT_RED << "[SERVER] recv() error on fd=" << fd
                          << ": " << strerror(errno) << RESET << std::endl;
                disconnectClient(poll_index);
                return false;
            }
        }
    }

    // 3. WRITE (POLLOUT)
    // If socket is ready to receive data and we have something to send
    if (revents & POLLOUT)
    {
        if (client->hasPendingSend())
        {
            sendPendingData(client);
        }
    }

    // FINAL FIX: Update events for next poll() call
    // If there's still something to send, request POLLOUT. If not, just listen (POLLIN).
    if (client->hasPendingSend())
    {
        poll_fds_[poll_index].events = POLLIN | POLLOUT;
    }
    else
    {
        poll_fds_[poll_index].events = POLLIN;
    }
    
    // Clearing revents is good practice, although poll() overwrites it
    poll_fds_[poll_index].revents = 0;

    return true; // Client still alive
}

//* ============================================================================
//* DISCONNECT CLIENT
//* ============================================================================


void Server::disconnectClient(size_t poll_index)
{
    // 1. Get basic information before deleting anything
    int fd = poll_fds_[poll_index].fd;
    ClientConnection* client = findClientByFd(fd);

    std::cout << YELLOW << "[SERVER] Disconnecting client fd=" << fd << RESET << std::endl;

    // 2. If client exists, clean up IRC logic and objects
    if (client)
    {
        User* user = client->getUser();
        if (user)
        {
            // A. CHANNEL CLEANUP
            // Make a COPY of the channels vector because we're going to modify it
            std::vector<Channel*> userChannels = user->getChannels();

            for (std::vector<Channel*>::iterator it = userChannels.begin(); it != userChannels.end(); ++it)
            {
                Channel* channel = *it;

                // 1. Notify others (QUIT message)
                std::string timestamp = getCurrentTimestamp();
                std::string quitMsg = std::string(BRIGHT_MAGENTA) + "@time=" + timestamp + RESET + " " +
                                        BRIGHT_CYAN + ":" + user->getPrefix() + RESET +
                                        " " + RED + "QUIT" + RESET + " :Connection closed\r\n";
                channel->broadcast(quitMsg, user);

                // 2. Remove user from channel
                channel->removeMember(user);

                // 3. Manage empty channels (Avoid memory leaks in channels)
                if (channel->getUserCount() == 0)
                {
                    // Find and delete the channel from the server's global list
                    for (std::vector<Channel*>::iterator chanIt = channels_.begin(); chanIt != channels_.end(); ++chanIt)
                    {
                        if (*chanIt == channel)
                        {
                            delete *chanIt;
                            channels_.erase(chanIt);
                            break; 
                        }
                    }
                }
            }
        }

        // B. REMOVE FROM SERVER'S CLIENT LIST
        // (Use manual loop to find and delete the pointer in the vector)
        for (std::vector<ClientConnection*>::iterator it = clients_.begin(); it != clients_.end(); ++it)
        {
            if (*it == client)
            {
                clients_.erase(it);
                break;
            }
        }

        // C. CLOSE SOCKET AND FREE MEMORY
        close(fd);
        if (user)
            delete user; // User must be manually deleted
        delete client;   // Delete the connection
    }
    else
    {
        // If we don't find the client object, close the fd for safety
        close(fd);
    }

    // 3. UPDATE POLL_FDS
    // Remove the fd from the monitoring vector.
    if (poll_index < poll_fds_.size())
        poll_fds_.erase(poll_fds_.begin() + poll_index);
}

//* ============================================================================
//* COMMAND PROCESSING
//* ============================================================================

void Server::processClientCommands(ClientConnection* client)
{
    client->updateActivity();
    
    // Process ALL complete lines in the buffer
    // (Important in case several commands arrived together)
    while (client->hasCompleteLine())
    {
        std::string rawLine = client->popLine();
        
        // Optional debug
        // std::cout << "[DEBUG] < " << rawLine << std::endl;

        // 1. Parse the line
        Message msg = Parser::parse(rawLine);

        // 2. If command is empty (blank line or only spaces), ignore
        if (msg.command.empty())
            continue;

        // 3. Search for command in the map
        std::map<std::string, CommandHandler>::iterator it = _commandMap.find(msg.command);

        if (it != _commandMap.end())
        {
            // Found = Execute the associated function
            (this->*(it->second))(client, msg);
        }
        else
        {
            // COMMAND NOT FOUND
            // Should send ERR_UNKNOWNCOMMAND (421)
            // For now, a simple log:
            std::cerr << "[SERVER] Unknown command: " << msg.command << std::endl;
        }
    }
}

void Server::sendPendingData(ClientConnection* client)
{
    if (!client->hasPendingSend())
        return;

    const std::string& data = client->getSendBuffer();
    
    // Non-blocking send with MSG_DONTWAIT
    ssize_t bytesSent = send(client->getFd(), data.c_str(), data.length(), MSG_DONTWAIT);

    if (bytesSent > 0)
    {
        // Only clear the bytes that were sent
        client->clearSentData(bytesSent);
        
        std::cout << "[DEBUG] Sent " << bytesSent << "/" << data.length() 
                  << " bytes to fd=" << client->getFd() << std::endl;
    }
    else if (bytesSent < 0)
    {
        // Normal errors in non-blocking
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            // Socket full, we'll try again on next POLLOUT
            return;
        }
        
        // Fatal error
        std::cerr << "[ERROR] send() failed: " << strerror(errno) << std::endl;
        client->closeConnection();
    }
}
//* ============================================================================
//* UTILITIES
//* ============================================================================

void Server::addClientToPoll(ClientConnection* client)
{
	struct pollfd pfd;
	pfd.fd = client->getFd();       //* File descriptor of the client socket to monitor
	pfd.events = POLLIN;            //* Register interest in read events (incoming data)
	pfd.revents = 0;                //* Clear returned events field (will be filled by poll())
	poll_fds_.push_back(pfd);       //* Add to poll array for monitoring
}

void Server::updatePollEvents(int fd, short events)
{
	for (size_t i = 0; i < poll_fds_.size(); ++i)
	{
		if (poll_fds_[i].fd == fd)
		{
			poll_fds_[i].events = events; // Found and updated
			break;
		}
	}
}

ClientConnection* Server::findClientByFd(int fd)
{
	for (size_t i = 0; i < clients_.size(); ++i) //* Just looking in the vector<ClientConnection*> if there is that client.
	{
		if (clients_[i] && clients_[i]->getFd() == fd) 
			return (clients_[i]);
	}
	return (NULL);
}

void Server::initCommands()
{
    // Map the command string to the corresponding member function
    _commandMap["PASS"] = &Server::cmdPass;
    _commandMap["NICK"] = &Server::cmdNick;
    _commandMap["USER"] = &Server::cmdUser;
    _commandMap["PING"] = &Server::cmdPing;
    _commandMap["PONG"] = &Server::cmdPong;
    _commandMap["QUIT"] = &Server::cmdQuit;
    _commandMap["JOIN"] = &Server::cmdJoin;
    _commandMap["PART"] = &Server::cmdPart;
    _commandMap["PRIVMSG"] = &Server::cmdPrivMsg;
    _commandMap["NOTICE"] = &Server::cmdNotice;
    _commandMap["NAMES"] = &Server::cmdNames;
    _commandMap["WHO"] = &Server::cmdWho;
    _commandMap["WHOIS"] = &Server::cmdWhois;
    _commandMap["KICK"] = &Server::cmdKick;
    _commandMap["INVITE"] = &Server::cmdInvite;
    _commandMap["TOPIC"] = &Server::cmdTopic;
    _commandMap["MODE"] = &Server::cmdMode;
    
    // Parser already handles converting command to uppercase
}

//* ============================================================================
//* HELPERS - TIMESTAMP
//* ============================================================================

std::string Server::getCurrentTimestamp() const
{
    time_t now = std::time(NULL);
    struct tm* timeinfo = std::localtime(&now);
    
    char buffer[9]; // HH:MM:SS\0
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    
    return std::string(buffer);
}