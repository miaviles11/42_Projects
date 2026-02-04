/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HelpBot.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-13 13:35:47 by rmunoz-c          #+#    #+#             */
/*   Updated: 2026-01-13 13:35:47 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPBOT_HPP
# define HELPBOT_HPP

#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <sstream>

/** 
 * -R- IRC Help Bot - Automated client that connects to the IRC server,
 * -R- authenticates, joins channels, and responds to user commands (!help, !time, etc.)
 */

class HelpBot
{
private:
    // Connection
    int _sockfd;
    std::string _serverIP;
    int _serverPort;
    std::string _password;
    
    // Identity
    std::string _nickname;
    std::string _username;
    std::string _realname;
    
    // State
    bool _authenticated;
    bool _running;
    time_t _startTime;
    
    // Buffer & channels
    std::string _recvBuffer;
    std::vector<std::string> _channels;
    std::string stripAnsiCodes(const std::string& str);

public:
    // Constructor & Destructor
    HelpBot(const std::string& ip, int port, const std::string& pass);
    ~HelpBot();
    
    // Connection & Authentication
    bool connect();
    bool authenticate();
    bool joinChannels();
    
    // Main loop
    void run();
    void stop();
    
    // Message processing
    void processMessage(const std::string& line);
    void handleCommand(const std::string& sender, const std::string& target, const std::string& message);
    
    // Bot commands
    void cmdHelp(const std::string& target);
    void cmdTime(const std::string& target);
    void cmdUptime(const std::string& target);
    void cmdEcho(const std::string& target, const std::string& msg);
    void cmdJoke(const std::string& target);
    void cmdPing(const std::string& target);
    
    // Utilities
    void sendMessage(const std::string& target, const std::string& msg);
    void sendRaw(const std::string& raw);
    bool recv();
    
    // Parsing helpers
    std::string extractSender(const std::string& prefix);
    std::string extractCommand(const std::string& line);
    std::vector<std::string> splitParams(const std::string& line);
};

#endif