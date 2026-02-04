/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 15:52:03 by miaviles          #+#    #+#             */
/*   Updated: 2025/12/10 19:51:36 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server/Server.hpp"
#include <iostream>
#include <cstdlib>
#include <csignal>

// Global pointer to access server from signal handler.
// Used ONLY to call stop(), not to delete memory.
Server* g_server = NULL;

// Safe signal handler (Async-Signal-Safe)
// Must not contain 'delete', 'cout', 'malloc', etc.
void signalHandler(int signum)
{
    (void)signum; // Silence unused variable warning
    if (g_server) 
    {
        // Only tell the server to stop its main loop.
        // Memory will be freed in main() after run() returns.
        g_server->stop();
    }
}

bool isValidPort(int port)
{
    return (port > 1024 && port < 65536);
}

int main(int argc, char **argv)
{
    //* ARGUMENT VALIDATION
    if (argc != 3) 
    {
        std::cerr << "Usage: " << argv[0] << " <port> <password>\n";
        std::cerr << "  port: 1025-65535\n";
        std::cerr << "  password: connection password\n";
        return (1);
    }
    
    int port = std::atoi(argv[1]);
    if (!isValidPort(port)) {
        std::cerr << "[ERROR] Invalid port. Use 1025-65535\n";
        return (1);
    }
    
    std::string password = argv[2];
    if (password.empty()) {
        std::cerr << "[ERROR] Password cannot be empty\n";
        return (1);
    }
    
    //* CONFIGURE SIGNALS
    // SIGINT (Ctrl+C) and SIGTERM are standard termination signals
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    // SIGPIPE is crucial in network servers. If a client closes the connection
    // while we try to write to it, the OS sends SIGPIPE which crashes the program
    // by default. SIG_IGN makes send() return error (EPIPE) instead.
    signal(SIGPIPE, SIG_IGN);
    
    //* CREATE AND START SERVER
    g_server = new Server(port, password);
    
    if (!g_server->start()) {
        std::cerr << "[FATAL] Could not start server\n";
        delete g_server; // Early cleanup if startup fails
        return (1);
    }
    
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════╗\n";
    std::cout << "║   IRC SERVER STARTED                 ║\n";
    std::cout << "║   Port: " << port << "               ║\n";
    std::cout << "║   Press Ctrl+C to exit               ║\n";
    std::cout << "╚══════════════════════════════════════╝\n\n";
    
    // Program will block here inside the while(running_) loop
    g_server->run(); 
    
    //* CLEANUP
    // When g_server->stop() is called (by signal), run() terminates and we reach here.
    // It's safe to do delete and cout here because we're in the main thread,
    // not inside the signal interrupt.
    std::cout << "\n[MAIN] Stopping server..." << std::endl;
    delete g_server;
    g_server = NULL;
    
    std::cout << "[MAIN] Server stopped cleanly." << std::endl;
    return (0);
}