/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-05 15:31:58 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-12-05 15:31:58 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include <algorithm>

User::User() : _nickname(""), _username(""), _realname(""), _hostname(""),
_isOperator(false), _isInvisible(false), _isAway(false), _awayMessage(""),
_connection(NULL)
{
}

User::User(const std::string& nickname): _nickname(nickname), _username(""),
_realname(""), _hostname(""), _isOperator(false), _isInvisible(false),
_isAway(false), _awayMessage(""), _connection(NULL)
{
}

User::~User()
{
	//? Don't delete _connection (managed by Server)
    //? Don't delete channels (managed by Server)
}

// ========================================================================
// 							  Identity Getters
// ========================================================================

const std::string& User::getNickname() const
{
	return _nickname;
}

const std::string& User::getUsername() const
{
	return _username;
}

const std::string& User::getRealname() const
{
	return _realname;
}

const std::string& User::getHostname() const
{
	return _hostname;
}

// ========================================================================
// 							  Identity Setters
// ========================================================================

void User::setNickname(const std::string& nick)
{
	_nickname = nick;
}

void User::setUsername(const std::string& user)
{
	_username = user;
}

void User::setRealname(const std::string& real)
{
	_realname = real;
}

void User::setHostname(const std::string& host)
{
	_hostname = host;
}

// ========================================================================
// 							  Prefix Generation
// ========================================================================

std::string User::getPrefix() const
{
	return _nickname + "!" + _username + "@" + _hostname;
}

// ========================================================================
// 							  User Modes Getters
// ========================================================================

bool User::isOperator() const
{
	return _isOperator;
}

bool User::isInvisible() const
{
	return _isInvisible;
}

bool User::isAway() const
{
	return _isAway;
}

const std::string& User::getAwayMessage() const
{
	return _awayMessage;
}

// ========================================================================
// 							  User Modes Setters
// ========================================================================

void User::setOperator(bool op)
{
	_isOperator = op;
}

void User::setInvisible(bool inv)
{
	_isInvisible = inv;
}

void User::setAway(bool away)
{
	_isAway = away;
}

void User::setAwayMessage(const std::string& msg)
{
	_awayMessage = msg;
}

// ========================================================================
// 						   Channel Membership
// ========================================================================

const std::vector<Channel*>& User::getChannels() const
{
	return _channels;
}

void User::joinChannel(Channel* channel)
{
	if (!isInChannel(channel))
		_channels.push_back(channel);
}

bool User::isInChannel(Channel* channel) const
{
	return std::find(_channels.begin(), _channels.end(), channel) != _channels.end();
}

void User::leaveChannel(Channel* channel)
{
	std::vector<Channel*>::iterator it = 
    	std::find(_channels.begin(), _channels.end(), channel);
	if (it != _channels.end())
		_channels.erase(it);
}

// ========================================================================
// 						  Connection Association
// ========================================================================

void User::setConnection(ClientConnection* conn)
{
	_connection = conn;
}

ClientConnection* User::getConnection() const
{
	return _connection;
}

bool User::isConnected() const
{
	return _connection != NULL;
}
