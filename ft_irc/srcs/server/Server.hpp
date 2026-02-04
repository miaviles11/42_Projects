/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:55:08 by miaviles          #+#    #+#             */
/*   Updated: 2025/12/10 19:46:01 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <poll.h>
#include <map>
#include "../irc/Message.hpp"

class ClientConnection;
class Channel;
class User;

/**
 * Server: IRC Server main coordinator
 * * Responsibilities:
 * - Main poll() loop (SINGLE poll as required by 42)
 * - ClientConnection lifecycle management
 * - Event routing to appropriate handlers
 * - Channel management
 * - Command execution coordination
 * * Uses:
 * - SocketUtils for low-level socket operations
 * - ClientConnection for connection + User state
 */

class Server {
	public:
		Server(int port, const std::string& password);
		~Server();

		//* MAIN CONTROLLERS
		bool start(); 								//* Create Socket, bind, listen
		void run(); 								//* Loop poll()/select()
		void stop();
	
		//* GETTERS
		const std::string& getPassword() const;
		int getClientCount() const;
		
	private:
		//* CONFIGURATION
		int port_;
		std::string password_;
		int server_fd_; 							//* FD OF THE SERVER'S SOCKET
		bool running_;

		//* COLLECTIONS
		std::vector<ClientConnection*> clients_; 	//* STORAGE THE LIST OF CLIENTS
		std::vector<Channel*> channels_; 			//* STORAGE THE LIST OF CHANNELS
		std::vector<struct pollfd> poll_fds_; 		//* POOLS FUCTION

		//* INITIALIZATION
		bool setupServerSocket();

		//* CONECTION MANAGEMENT
		void acceptNewConnections();
    	bool handleClientEvent(size_t poll_index);
   		void disconnectClient(size_t poll_index);

		//* COMMAND PROCESSING (for later)
		void processClientCommands(ClientConnection* client);
		void sendPendingData(ClientConnection* client);
		
		//* UTILITIES
		void addClientToPoll(ClientConnection* client);
		void updatePollEvents(int fd, short events);
		ClientConnection* findClientByFd(int fd);

		//* TIMESTAMP HELPER
		std::string getCurrentTimestamp() const;

        //* CHANNEL MANAGEMENT HELPER FUNCTIONS (CRÍTICO: FALTABAN ESTOS)
        Channel* getChannel(const std::string& name);
        Channel* createChannel(const std::string& name);

		/*--------------------------------------------------------------------*/
        /* NEW: COMMAND SYSTEM                                                */
        /*--------------------------------------------------------------------*/
        
        // 1. Function type definition for commands
        //    (Receives the client who sent the message and the parsed message)
        typedef void (Server::*CommandHandler)(ClientConnection*, const Message&);

        // 2. Map to associate strings ("JOIN") with functions (&Server::cmdJoin)
        std::map<std::string, CommandHandler> _commandMap;

        // 3. Function to fill the map at startup
        void initCommands();

		/*--------------------------------------------------------------------*/
        /* NEW: COMMAND PROTOTYPES (Implement in Commands.cpp)               */
        /*--------------------------------------------------------------------*/
        
        // Authentication
        void cmdPass(ClientConnection* client, const Message& msg);
        void cmdNick(ClientConnection* client, const Message& msg);
        void cmdUser(ClientConnection* client, const Message& msg);
        void cmdPing(ClientConnection* client, const Message& msg);
        void cmdPong(ClientConnection* client, const Message& msg);
        void cmdQuit(ClientConnection* client, const Message& msg);

        // Channels and Communication
        void cmdJoin(ClientConnection* client, const Message& msg);
        void cmdPart(ClientConnection* client, const Message& msg);
        void cmdPrivMsg(ClientConnection* client, const Message& msg);
        void cmdNotice(ClientConnection* client, const Message& msg);
		void cmdNames(ClientConnection* client, const Message& msg);
		void cmdWho(ClientConnection* client, const Message& msg);
		void cmdWhois(ClientConnection* client, const Message& msg);
		// Auxiliary function for WHOIS
		std::string getChannelsForUser(User* user) const;

        // Operators
        void cmdKick(ClientConnection* client, const Message& msg);
        void cmdInvite(ClientConnection* client, const Message& msg);
        void cmdTopic(ClientConnection* client, const Message& msg);
        void cmdMode(ClientConnection* client, const Message& msg);
	
		//* NON-COPYABLE
		Server(const Server&);
		Server& operator=(const Server&);
};

#endif
