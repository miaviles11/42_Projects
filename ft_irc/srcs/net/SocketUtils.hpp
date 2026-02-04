/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketUtils.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaviles <miaviles@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 18:53:10 by miaviles          #+#    #+#             */
/*   Updated: 2025/12/08 17:10:36 by miaviles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_UTILS_HPP
#define SOCKET_UTILS_HPP

#include <string>
#include <sys/types.h>

/**
 * SocketUtils: Low-level socket operations utility class
 * 
 * All functions are static - no instances needed.
 * Provides complete socket creation, configuration, and I/O operations
 * for the IRC server.
 * 
 * Responsibilities:
 * - Server socket creation and configuration
 * - Client connection acceptance
 * - Non-blocking I/O operations
 * - Error handling and reporting
 */

class SocketUtils
{
public:
	//* ========================================
	//* SOCKET CONFIGURATION
	//* ========================================
	
	/**
	 * Set socket to non-blocking mode
	 * 
	 * @param fd File descriptor to configure
	 * @return true on success, false on error
	 */
	static bool setNonBlocking(int fd);
	
	/**
	 * Enable SO_REUSEADDR socket option
	 * Allows immediate server restart without "Address already in use" error
	 * 
	 * @param fd File descriptor to configure
	 * @return true on success, false on error
	 */
	static bool setReuseAddr(int fd);
	
	//* ========================================
	//* SERVER SOCKET CREATION
	//* ========================================
	
	/**
	 * Create a TCP server socket
	 * Automatically configures:
	 * - SO_REUSEADDR option
	 * - Non-blocking mode
	 * 
	 * @return socket fd on success, -1 on error
	 */
	static int createServerSocket();
	
	/**
	 * Bind server socket to a specific port
	 * Binds to all interfaces (0.0.0.0)
	 * 
	 * @param fd Socket file descriptor
	 * @param port Port number (recommended: 1024-65535)
	 * @return true on success, false on error
	 */
	static bool bindSocket(int fd, int port);
	
	/**
	 * Put socket in listening mode
	 * 
	 * @param fd Socket file descriptor
	 * @param backlog Maximum pending connections queue size (use SOMAXCONN)
	 * @return true on success, false on error
	 */
	static bool listenSocket(int fd, int backlog);
	
	//* ========================================
	//* CLIENT CONNECTION HANDLING
	//* ========================================
	
	/**
	 * Accept a new client connection (non-blocking)
	 * Automatically sets client socket to non-blocking mode
	 * 
	 * @param server_fd Server socket file descriptor
	 * @param client_ip [OUT] Client IP address as string (e.g., "192.168.1.100")
	 * @return client fd on success, -1 if no connection available or error
	 */
	static int acceptClient(int server_fd, std::string& client_ip);
	
	//* ========================================
	//* I/O OPERATIONS
	//* ========================================
	
	/**
	 * Receive data from socket (non-blocking)
	 * 
	 * @param fd Socket file descriptor
	 * @param buffer Buffer to store received data
	 * @param size Buffer size
	 * @return Number of bytes received (> 0)
	 *         0 if connection closed by peer
	 *         -1 on error (check errno for EAGAIN/EWOULDBLOCK)
	 * 
	 * Note: In non-blocking mode, returns -1 with errno=EAGAIN if no data available
	 */
	static ssize_t receiveData(int fd, char* buffer, size_t size);
	
	/**
	 * Send data to socket (non-blocking)
	 * 
	 * @param fd Socket file descriptor
	 * @param data Data to send
	 * @param size Data size in bytes
	 * @return Number of bytes sent (may be less than size)
	 *         -1 on error (check errno for EAGAIN/EWOULDBLOCK)
	 * 
	 * Note: In non-blocking mode, may send partial data or return -1 with errno=EAGAIN
	 */
	static ssize_t sendData(int fd, const char* data, size_t size);
	
	//* ========================================
	//* ERROR HANDLING
	//* ========================================
	
	/**
	 * Check if last error is "would block"
	 * Used to distinguish between real errors and "try again later" in non-blocking I/O
	 * 
	 * @return true if errno is EAGAIN or EWOULDBLOCK
	 */
	static bool isWouldBlock();
	
	/**
	 * Get last socket error as human-readable string
	 * 
	 * @return Error message from errno
	 */
	static std::string getLastError();

private:
	/**
	 * Private constructor - utility class, no instances allowed
	 */
	SocketUtils();
};

#endif