/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:09:27 by miaviles          #+#    #+#             */
/*   Updated: 2025/12/09 14:30:21 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SocketUtils.hpp"
#include "../utils/Colors.hpp"
#include <iostream>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

//* ========================================
//* SOCKET CONFIGURATION
//* ========================================

//* Makes the socket non-blocking: calls won't block waiting for data and will return immediately if nothing is available.
bool	SocketUtils::setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0); 					//* "fcntl is used to manipulated FDs, in this case in F_GETFL mode is to see the status of FDs"
	if (flags == -1)
	{
		std::cerr << BRIGHT_RED << "[SOCKET] fcntl(F_GETFL) failed: " << strerror(errno) << RESET << std::endl;
		return (false);
	}
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) 	//* "fcntl is used to manipulated FDs, in this case in F_SETFL mode is too set the status of FDs"
	{
		std::cerr << BRIGHT_RED << "[SOCKET] fcntl(F_SETFL, O_NONBLOCK) failed: " << strerror(errno) << RESET << std::endl;
		return (false);
	}
	return (true);
}

//* ========================================
//* SO_REUSEADDR: Bypass TIME_WAIT State
//* ========================================
//* Problem: When a server closes, the OS keeps the port in TIME_WAIT state for ~60 seconds
//*      This prevents immediate restart: "Address already in use" error
//* Solution: SO_REUSEADDR tells the OS "allow me to reuse this port immediately"
//* 
//* Example WITHOUT this option:
//*   1. Start server on port 6667 → Works ✓
//*   2. Ctrl+C to close → Server stops ✓
//*   3. Restart immediately → ERROR ✗ (must wait 60 seconds)
//*
//* Example WITH this option:
//*   1. Start server on port 6667 → Works ✓
//*   2. Ctrl+C to close → Server stops ✓
//*   3. Restart immediately → Works ✓ (no waiting!)
//*
//* Parameters:
//*   - fd: Socket file descriptor to configure
//*   - SOL_SOCKET: Apply option at socket level (not TCP/IP level)
//*   - SO_REUSEADDR: Specific option to enable address reuse
//*   - opt = 1: Enable the option (0 would disable it)
//* ========================================
bool	SocketUtils::setReuseAddr(int fd)
{
	int opt = 1;                                      //* 1 = enable, 0 = disable

	if (setsockopt(fd, SOL_SOCKET,  SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		std::cerr << BRIGHT_RED << "[SOCKET] setsockopt(SO_REUSEADDR) failed: " << strerror(errno) << RESET << std::endl;
        return (false);
	}
	return (true);
}

//* ========================================
//* SERVER SOCKET CREATION
//* ========================================

int		SocketUtils::createServerSocket()
{
	//* CREATE A SOCKET -->
	//* AF_INET = IPv4 (DOMAIN)
    //* SOCK_STREAM = TCP (TYPE)
    //* 0 = protocol by default (TCP for SOCK_STREAM)
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1)
	{
		std::cerr << BRIGHT_RED << "[SOCKET] socket() failed: " << strerror(errno) << RESET << std::endl;
		return (-1);	
	}
	std::cout << CYAN << "[SOCKET] Socket created (fd=" << fd << ")" << RESET << std::endl;
    if (!setReuseAddr(fd)) //* Configure SO_REUSEADDR
	{
        close(fd);
        return (-1);
    }
    if (!setNonBlocking(fd)) //* Configure non-blocking
	{
        close(fd);
        return (-1);
    }
    std::cout << GREEN << "[SOCKET] ✓ Socket configured (non-blocking + SO_REUSEADDR)" << RESET << std::endl;
    return (fd);
}

//* ========================================
//* BIND: Attach socket to a specific port
//* Purpose: Associates the socket with a port number so clients know where to connect
//* Think of it like: "This socket will listen on port 6667"
//* ========================================
bool	SocketUtils::bindSocket(int fd, int port)
{
	//* Prepare address structure for IPv4
	struct sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));               //* Zero out the structure (good practice)

	addr.sin_family = AF_INET;                         //* Address family: IPv4
	addr.sin_addr.s_addr = INADDR_ANY;                 //* Bind to all network interfaces (0.0.0.0)
	addr.sin_port = htons(port);                       //* Convert port to network byte order (big-endian)

	//* Attach the socket to the port
	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		std::cerr << BRIGHT_RED << "[SOCKET] bind() failed on port " << port 
				<< ": " << strerror(errno) << RESET << std::endl;
		return (false);
	}
	std::cout << GREEN << "[SOCKET] ✓ Bound to 0.0.0.0:" << port << RESET << std::endl;
	return (true);
}

//* Prepare to accept conections on socket fd (LISTEN MODE)
bool	SocketUtils::listenSocket(int fd, int backlog)
{
	if (listen(fd, backlog) == -1)						//* BACKLOG: is the max size of the queue of pending conections
	{
		std::cerr << BRIGHT_RED << "[SOCKET] listen() failed: " << strerror(errno) << RESET << std::endl;
		return (false);
	}
	std::cout << GREEN << "[SOCKET] ✓ Listening (backlog=" << backlog << ")" << RESET << std::endl;
	return (true);
}

//* ========================================
//* CLIENT CONNECTION HANDLING
//* ========================================

//* ========================================
//* Accepts a new client connection on the server socket and configures it as non-blocking.
//* Returns: Client file descriptor on success, -1 on failure
//* ========================================
int		SocketUtils::acceptClient(int server_fd, std::string& client_ip)
{
	struct sockaddr_in cli_addr;                                      //* Structure to store client address information (IPv4)
	socklen_t cli_len = sizeof(cli_addr);                             //* Size of the client address structure

	int client_fd = accept(server_fd, (struct sockaddr*)&cli_addr, &cli_len); //* Accept incoming connection and get a new fd, the client socket FD exactly
	if (client_fd == -1) 
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)                  //* Non-blocking socket: no pending connections (not an error)
			return (-1);
		std::cerr << BRIGHT_RED << "[SOCKET] accept() failed: " << strerror(errno) << RESET << std::endl; //* Actual real error occurred
		return (-1);
	}
	
	char ip_str[INET_ADDRSTRLEN];                                     //* Buffer to hold IP address in string format
	inet_ntop(AF_INET, &cli_addr.sin_addr, ip_str, sizeof(ip_str));   //* Convert binary IP to dotted-decimal notation (e.g., "192.168.1.1")
	client_ip = ip_str;                                               //* Store the IP address in output parameter
	
	if (!setNonBlocking(client_fd))                                   //* Configure client socket to non-blocking mode
	{
		std::cerr << BRIGHT_RED << "[SOCKET] Failed to set client socket non-blocking" << RESET << std::endl;
		close(client_fd);                                             //* Close socket to prevent resource leak
		return (-1);
	}
	
	std::cout << GREEN << "[SOCKET] ✓ Accepted connection from " << client_ip  //* Log successful connection
			<< " (fd=" << client_fd << ")" << RESET << std::endl;
	
	return (client_fd);                                               //* Return valid client socket file descriptor
}

//* ========================================
//* I/O OPERATIONS
//* ========================================

//* RECEIVE DATA FROM CLIENT
//* Reads data from a socket in non-blocking mode
//* Returns:
//*   > 0: Number of bytes successfully read
//*   = 0: Connection closed cleanly by peer
//*   -1: No data available (EAGAIN/EWOULDBLOCK) or real error
//* Parameters:
//*   - fd: Socket file descriptor to read from
//*   - buffer: Destination buffer to store received data
//*   - size: Maximum number of bytes to read
//* ========================================
ssize_t	SocketUtils::receiveData(int fd, char* buffer, size_t size)
{
	ssize_t bytes = recv(fd, buffer, size, 0); 				//* Attempt to receive data from socket
	
	if (bytes == -1) 										//* recv() failed or no data available
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK) 		//* No data available right now (normal in non-blocking mode)
			return (-1); 									//* Not an error, just try again later

		std::cerr << BRIGHT_RED << "[SOCKET] recv() failed on fd=" << fd  //* Real error occurred
				<< ": " << strerror(errno) << RESET << std::endl;
		return (-1);
	}
	if (bytes == 0) 										//* Connection closed cleanly by peer
		std::cout << YELLOW << "[SOCKET] Connection closed by peer (fd=" << fd << ")" << RESET << std::endl;
	
	return (bytes); 										//* Return number of bytes received
}

//* ========================================
//* SEND DATA TO CLIENT
//* Sends data to a socket in non-blocking mode
//* Returns:
//*   > 0: Number of bytes successfully sent (may be less than 'size')
//*   -1: Send buffer full (EAGAIN/EWOULDBLOCK) or real error
//* Parameters:
//*   - fd: Socket file descriptor to send to
//*   - data: Pointer to data buffer to send
//*   - size: Number of bytes to send
//* ========================================
ssize_t	SocketUtils::sendData(int fd, const char* data, size_t size)
{
	ssize_t bytes = send(fd, data, size, 0);                //* Attempt to send data to socket
	
	if (bytes == -1)                                        //* send() failed or buffer full
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)        //* Send buffer full (normal in non-blocking mode)
			return (-1);                                    //* Not an error, retry later with POLLOUT
		
		std::cerr << BRIGHT_RED << "[SOCKET] send() failed on fd=" << fd  //* Real error occurred
				<< ": " << strerror(errno) << RESET << std::endl;
		return (-1);
	}
	
	return (bytes);                                         //* Return number of bytes sent
}
	
//* ========================================
//* ERROR HANDLING
//* ========================================

//* In non-blocking I/O, EAGAIN and EWOULDBLOCK indicate that
//* the operation should be retried later (not a real error)
bool	SocketUtils::isWouldBlock()
{
	return (errno == EAGAIN || errno == EWOULDBLOCK); //*  EWOULDBLOCK IS AN ALIAS OF EGAIN
}

std::string	SocketUtils::getLastError()
{
	return (std::string(strerror(errno)));     //* Return a string describing the meaning of errno

}
