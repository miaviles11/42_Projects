/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bot.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-14 12:42:17 by rmunoz-c          #+#    #+#             */
/*   Updated: 2026-01-14 12:42:17 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HelpBot.hpp"
#include <iostream>
#include <cstdlib>
#include <unistd.h>

int main(int argc, char** argv)
{
    // Validate arguments
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <ip> <port> <password>" << std::endl;
        std::cerr << "Example: " << argv[0] << " 127.0.0.1 6667 pass123" << std::endl;
        return 1;
    }
    
    // Parse arguments
    std::string ip = argv[1];
    int port = std::atoi(argv[2]);
    std::string password = argv[3];
    
    // Validate port
    if (port <= 0 || port > 65535)
    {
        std::cerr << "[ERROR] Invalid port number: " << port << std::endl;
        return 1;
    }
    
    // Initialize random seed for jokes
    std::srand(std::time(NULL));
    
    std::cout << "========================================" << std::endl;
    std::cout << "       IRC Help Bot v1.0" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Target server: " << ip << ":" << port << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Create bot instance
    HelpBot bot(ip, port, password);
    
    // Connect to server
    std::cout << "[INIT] Connecting to server..." << std::endl;
    if (!bot.connect())
    {
        std::cerr << "[ERROR] Failed to connect to server" << std::endl;
        return 1;
    }
    
    // Small delay to ensure connection is established
    sleep(1);
    
    // Authenticate
    std::cout << "[INIT] Authenticating..." << std::endl;
    if (!bot.authenticate())
    {
        std::cerr << "[ERROR] Failed to authenticate" << std::endl;
        return 1;
    }
    
    // Wait for server to process authentication
    sleep(2);
    
    // Join channels
    std::cout << "[INIT] Joining channels..." << std::endl;
    if (!bot.joinChannels())
    {
        std::cerr << "[ERROR] Failed to join channels" << std::endl;
        return 1;
    }
    
    // Small delay before starting main loop
    sleep(1);
    
    std::cout << "========================================" << std::endl;
    std::cout << "   Bot ready! Type CTRL+C to stop." << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Run bot (infinite loop until stopped)
    bot.run();
    
    std::cout << "[EXIT] Bot terminated." << std::endl;
    
    return 0;
}