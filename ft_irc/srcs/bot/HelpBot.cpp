/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HelpBot.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-01-13 13:35:08 by rmunoz-c          #+#    #+#             */
/*   Updated: 2026-01-15 20:15:00 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HelpBot.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// ============================================================================
// CONSTRUCTOR & DESTRUCTOR
// ============================================================================

HelpBot::HelpBot(const std::string& ip, int port, const std::string& pass)
    : _sockfd(-1), _serverIP(ip), _serverPort(port), _password(pass),
      _nickname("HelpBot"), _username("helpbot"), _realname("IRC Help Bot"),
      _authenticated(false), _running(false), _startTime(0), _recvBuffer("")
{
    _channels.push_back("#general");
    _channels.push_back("#help");
}

HelpBot::~HelpBot()
{
    if (_sockfd != -1)
        close(_sockfd);
}

// ============================================================================
// CONNECTION & AUTHENTICATION
// ============================================================================

bool HelpBot::connect()
{
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0)
    {
        std::cerr << "[BOT] Error: Failed to create socket" << std::endl;
        return false;
    }

    struct sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_serverPort);
    
    if (inet_pton(AF_INET, _serverIP.c_str(), &serverAddr.sin_addr) <= 0)
    {
        std::cerr << "[BOT] Error: Invalid IP address" << std::endl;
        close(_sockfd);
        _sockfd = -1;
        return false;
    }

    if (::connect(_sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "[BOT] Error: Failed to connect to " << _serverIP 
                  << ":" << _serverPort << std::endl;
        close(_sockfd);
        _sockfd = -1;
        return false;
    }

    std::cout << "[BOT] Connected to " << _serverIP << ":" << _serverPort << std::endl;
    return true;
}

bool HelpBot::authenticate()
{
    sendRaw("PASS " + _password);
    sendRaw("NICK " + _nickname);
    sendRaw("USER " + _username + " 0 * :" + _realname);
    
    std::cout << "[BOT] Authentication sent" << std::endl;
    
    _authenticated = true;
    _startTime = std::time(NULL);
    
    return true;
}

bool HelpBot::joinChannels()
{
    for (size_t i = 0; i < _channels.size(); ++i)
    {
        sendRaw("JOIN " + _channels[i]);
        std::cout << "[BOT] Joining channel: " << _channels[i] << std::endl;
    }
    return true;
}

// ============================================================================
// MAIN LOOP
// ============================================================================

void HelpBot::run()
{
    _running = true;
    std::cout << "[BOT] Bot is now running. Listening for messages..." << std::endl;
    
    while (_running)
    {
        if (!recv())
        {
            std::cerr << "[BOT] Connection lost" << std::endl;
            break;
        }
        
        size_t pos;
        while ((pos = _recvBuffer.find("\r\n")) != std::string::npos)
        {
            std::string line = _recvBuffer.substr(0, pos);
            _recvBuffer.erase(0, pos + 2);
            
            if (!line.empty())
            {
                std::cout << "[BOT] <- " << line << std::endl;
                processMessage(line);
            }
        }
    }
    
    std::cout << "[BOT] Bot stopped." << std::endl;
}

void HelpBot::stop()
{
    _running = false;
    if (_sockfd != -1)
    {
        close(_sockfd);
        _sockfd = -1;
    }
}

// ============================================================================
// UTILITIES
// ============================================================================

bool HelpBot::recv()
{
    char buffer[512];
    std::memset(buffer, 0, sizeof(buffer));
    
    ssize_t bytes = ::recv(_sockfd, buffer, sizeof(buffer) - 1, 0);
    
    if (bytes <= 0)
        return false;
    
    _recvBuffer.append(buffer, bytes);
    return true;
}

void HelpBot::sendRaw(const std::string& raw)
{
    std::string msg = raw + "\r\n";
    ssize_t sent = send(_sockfd, msg.c_str(), msg.length(), 0);
    
    if (sent < 0)
        std::cerr << "[BOT] Error sending message" << std::endl;
    else
        std::cout << "[BOT] -> " << raw << std::endl;
}

std::string HelpBot::stripAnsiCodes(const std::string& str)
{
    std::string result;
    bool inEscape = false;
    
    for (size_t i = 0; i < str.length(); ++i)
    {
        if (str[i] == '\033')
        {
            inEscape = true;
            continue;
        }
        
        if (inEscape)
        {
            if (str[i] == 'm')
                inEscape = false;
            continue;
        }
        
        result += str[i];
    }
    
    return result;
}

void HelpBot::sendMessage(const std::string& target, const std::string& msg)
{
    sendRaw("PRIVMSG " + target + " :" + msg);
}

// ============================================================================
// MESSAGE PROCESSING
// ============================================================================

void HelpBot::processMessage(const std::string& line)
{
    // Clean ANSI codes from entire line
    std::string cleanLine = stripAnsiCodes(line);
    
    // Remove IRCv3 tags (@time=XX:XX:XX)
    if (!cleanLine.empty() && cleanLine[0] == '@')
    {
        size_t spacePos = cleanLine.find(' ');
        if (spacePos != std::string::npos)
            cleanLine = cleanLine.substr(spacePos + 1);
    }
    
    // Handle PING/PONG
    if (cleanLine.find("PING") != std::string::npos)
    {
        size_t pingPos = cleanLine.find("PING");
        std::string pongResponse = cleanLine.substr(pingPos);
        pongResponse.replace(0, 4, "PONG");
        sendRaw(pongResponse);
        return;
    }
    
    // Find PRIVMSG
    size_t privmsgPos = cleanLine.find("PRIVMSG");
    if (privmsgPos == std::string::npos)
        return;
    
    // Extract from "PRIVMSG" onwards
    std::string relevantPart = cleanLine.substr(privmsgPos);
    
    // Parse: "PRIVMSG target :message"
    std::istringstream iss(relevantPart);
    std::string cmd, target, message;
    
    if (!(iss >> cmd >> target))
        return;
    
    std::getline(iss, message);
    
    // Clean message
    if (!message.empty() && message[0] == ' ')
        message = message.substr(1);
    if (!message.empty() && message[0] == ':')
        message = message.substr(1);
    
    // Extract sender from prefix (before PRIVMSG)
    std::string sender = "";
    std::string prefix = cleanLine.substr(0, privmsgPos);
    
    size_t colonPos = prefix.find(':');
    if (colonPos != std::string::npos)
    {
        size_t exclamation = prefix.find('!', colonPos);
        if (exclamation != std::string::npos)
            sender = prefix.substr(colonPos + 1, exclamation - colonPos - 1);
    }
    
    // Process command if message starts with !
    if (!message.empty() && message[0] == '!')
        handleCommand(sender, target, message);
}

void HelpBot::handleCommand(const std::string& sender, 
                            const std::string& target, 
                            const std::string& message)
{
    // Determine response target
    std::string responseTarget = (target == _nickname) ? sender : target;
    
    // Extract command and arguments
    std::istringstream iss(message);
    std::string cmd;
    iss >> cmd;
    
    std::string args;
    std::getline(iss, args);
    if (!args.empty() && args[0] == ' ')
        args = args.substr(1);
    
    // Convert to lowercase for case-insensitive matching
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);
    
    // Execute commands
    if (cmd == "!help")
        cmdHelp(responseTarget);
    else if (cmd == "!time")
        cmdTime(responseTarget);
    else if (cmd == "!uptime")
        cmdUptime(responseTarget);
    else if (cmd == "!echo")
        cmdEcho(responseTarget, args);
    else if (cmd == "!joke")
        cmdJoke(responseTarget);
    else if (cmd == "!ping")
        cmdPing(responseTarget);
}

// ============================================================================
// PARSING HELPERS
// ============================================================================

std::string HelpBot::extractSender(const std::string& prefix)
{
    if (prefix.empty() || prefix[0] != ':')
        return "";
    
    size_t exclamation = prefix.find('!');
    if (exclamation != std::string::npos)
        return prefix.substr(1, exclamation - 1);
    
    size_t space = prefix.find(' ');
    if (space != std::string::npos)
        return prefix.substr(1, space - 1);
    
    return prefix.substr(1);
}

std::string HelpBot::extractCommand(const std::string& line)
{
    size_t start = 0;
    
    if (!line.empty() && line[0] == ':')
    {
        start = line.find(' ');
        if (start == std::string::npos)
            return "";
        start++;
    }
    
    size_t end = line.find(' ', start);
    if (end == std::string::npos)
        return line.substr(start);
    
    return line.substr(start, end - start);
}

std::vector<std::string> HelpBot::splitParams(const std::string& line)
{
    std::vector<std::string> params;
    std::string temp = line;
    
    if (!temp.empty() && temp[0] == ':')
    {
        size_t spacePos = temp.find(' ');
        if (spacePos == std::string::npos)
            return params;
        temp = temp.substr(spacePos + 1);
    }
    
    size_t spacePos = temp.find(' ');
    if (spacePos == std::string::npos)
        return params;
    temp = temp.substr(spacePos + 1);
    
    while (!temp.empty())
    {
        size_t start = 0;
        while (start < temp.length() && temp[start] == ' ')
            start++;
        
        if (start >= temp.length())
            break;
        
        temp = temp.substr(start);
        
        if (temp[0] == ':')
        {
            params.push_back(temp);
            break;
        }
        
        size_t nextSpace = temp.find(' ');
        if (nextSpace == std::string::npos)
        {
            params.push_back(temp);
            break;
        }
        
        params.push_back(temp.substr(0, nextSpace));
        temp = temp.substr(nextSpace + 1);
    }
    
    return params;
}

// ============================================================================
// BOT COMMANDS
// ============================================================================

void HelpBot::cmdHelp(const std::string& target)
{
    sendMessage(target, "Available commands: !help, !time, !uptime, !echo <msg>, !joke, !ping");
}

void HelpBot::cmdTime(const std::string& target)
{
    time_t now = std::time(NULL);
    char buffer[100];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    
    std::string response = "Current time: ";
    response += buffer;
    
    sendMessage(target, response);
}

void HelpBot::cmdUptime(const std::string& target)
{
    time_t now = std::time(NULL);
    long uptime = static_cast<long>(now - _startTime);
    
    long hours = uptime / 3600;
    long minutes = (uptime % 3600) / 60;
    long seconds = uptime % 60;
    
    std::ostringstream oss;
    oss << "Bot uptime: ";
    if (hours > 0)
        oss << hours << "h ";
    if (minutes > 0 || hours > 0)
        oss << minutes << "m ";
    oss << seconds << "s";
    
    sendMessage(target, oss.str());
}

void HelpBot::cmdEcho(const std::string& target, const std::string& msg)
{
    if (msg.empty())
        sendMessage(target, "Usage: !echo <message>");
    else
        sendMessage(target, msg);
}

void HelpBot::cmdJoke(const std::string& target)
{
    const char* jokes[] = {
        "Why do programmers prefer dark mode? Because light attracts bugs!",
        "Why did the programmer quit his job? Because he didn't get arrays!",
        "How many programmers does it take to change a light bulb? None, that's a hardware problem!",
        "Why do Java developers wear glasses? Because they don't C#!",
        "What's a programmer's favorite place to hang out? Foo Bar!",
        "Why did the developer go broke? Because he used up all his cache!",
        "What do you call 8 hobbits? A hobbyte!",
        "There are 10 types of people: those who understand binary and those who don't.",
        "Why was the JavaScript developer sad? Because he didn't Node how to Express himself!",
        "A SQL query walks into a bar, walks up to two tables and asks: 'Can I JOIN you?'"
    };
    
    const int numJokes = sizeof(jokes) / sizeof(jokes[0]);
    int randomIndex = std::rand() % numJokes;
    
    sendMessage(target, jokes[randomIndex]);
}

void HelpBot::cmdPing(const std::string& target)
{
    sendMessage(target, "Pong! 🏓");
}