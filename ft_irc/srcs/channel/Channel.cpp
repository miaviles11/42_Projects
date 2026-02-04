#include "Channel.hpp"
#include "../client/User.hpp"
#include "../client/ClientConnection.hpp"
#include "../utils/Colors.hpp"
#include <algorithm>
#include <iostream>
#include <cstdio>

// ============================================================================
// CONSTRUCTOR / DESTRUCTOR
// ============================================================================

Channel::Channel(const std::string& name) : 
    _name(name), _topic(""), _key(""), _limit(0),
    _inviteOnly(false), _topicOpOnly(false), _hasKey(false), _hasLimit(false)
{
}

Channel::~Channel()
{
    // Don't delete users (User*), they belong to the Server.
    // Just clear the lists.
    _members.clear();
    _operators.clear();
    _invites.clear();
}

// ============================================================================
// BASIC GETTERS
// ============================================================================

const std::string& Channel::getName() const { return _name; }
const std::string& Channel::getTopic() const { return _topic; }
const std::string& Channel::getKey() const { return _key; }
size_t Channel::getUserCount() const { return _members.size(); }
int Channel::getLimit() const { return _limit; }

// ============================================================================
// MODES
// ============================================================================

std::string Channel::getModes() const
{
    std::string modes = "+";
    if (_inviteOnly) modes += "i";
    if (_topicOpOnly) modes += "t";
    if (_hasKey) modes += "k";
    if (_hasLimit) modes += "l";
    
    // Add mode arguments (key and limit)
    if (_hasKey) modes += " " + _key;
    if (_hasLimit) {
        char buff[20];
        sprintf(buff, "%d", _limit);
        modes += " " + std::string(buff);
    }
    return modes;
}

bool Channel::hasMode(char mode) const
{
    if (mode == 'i') return _inviteOnly;
    if (mode == 't') return _topicOpOnly;
    if (mode == 'k') return _hasKey;
    if (mode == 'l') return _hasLimit;
    return false;
}

void Channel::setMode(char mode, bool active)
{
    if (mode == 'i') _inviteOnly = active;
    else if (mode == 't') _topicOpOnly = active;
    // k and l are managed with setKey and setLimit specifically
}

void Channel::setKey(const std::string& key)
{
    if (key.empty()) {
        _hasKey = false;
        _key = "";
    } else {
        _hasKey = true;
        _key = key;
    }
}

void Channel::setLimit(int limit)
{
    if (limit <= 0) {
        _hasLimit = false;
        _limit = 0;
    } else {
        _hasLimit = true;
        _limit = limit;
    }
}

void Channel::setTopic(const std::string& topic)
{
    _topic = topic;
}

// ============================================================================
// MEMBER MANAGEMENT
// ============================================================================

void Channel::addMember(User* user)
{
    if (!isMember(user))
        _members.push_back(user);
    
    // If user was invited, remove from pending invites
    if (_invites.count(user->getNickname()))
        _invites.erase(user->getNickname());
}

void Channel::removeMember(User* user)
{
    std::vector<User*>::iterator it = std::find(_members.begin(), _members.end(), user);
    if (it != _members.end())
        _members.erase(it);

    // If user was an operator, remove from operators too
    removeOperator(user);
}

bool Channel::isMember(User* user) const
{
    return std::find(_members.begin(), _members.end(), user) != _members.end();
}

User* Channel::getMember(const std::string& nick) const
{
    for (size_t i = 0; i < _members.size(); ++i) {
        if (_members[i]->getNickname() == nick)
            return _members[i];
    }
    return NULL;
}

// [CRITICAL] Implementation needed for NICK spam fix
const std::vector<User*>& Channel::getMembers() const
{
    return _members;
}

// ============================================================================
// OPERATOR MANAGEMENT
// ============================================================================

void Channel::addOperator(User* user)
{
    if (!isOperator(user))
        _operators.push_back(user);
}

void Channel::removeOperator(User* user)
{
    std::vector<User*>::iterator it = std::find(_operators.begin(), _operators.end(), user);
    if (it != _operators.end())
        _operators.erase(it);
}

bool Channel::isOperator(User* user) const
{
    return std::find(_operators.begin(), _operators.end(), user) != _operators.end();
}

// ============================================================================
// INVITE MANAGEMENT
// ============================================================================

void Channel::addInvite(const std::string& nick)
{
    _invites.insert(nick);
}

bool Channel::isInvited(User* user) const
{
    return _invites.find(user->getNickname()) != _invites.end();
}

// ============================================================================
// COMMUNICATION
// ============================================================================

void Channel::broadcast(const std::string& message, User* exclude)
{
    for (std::vector<User*>::iterator it = _members.begin(); it != _members.end(); ++it)
    {
        User* member = *it;
        
        if (member == exclude)
            continue;
        
        ClientConnection* conn = member->getConnection();
        if (conn && !conn->isClosed())
        {
            conn->queueSend(message);
            
            // FIX: Force immediate send if possible
            // This can't be done from here because Channel doesn't know Server
        }
    }
}

std::string Channel::getNamesList() const
{
    std::string list = "";
    for (size_t i = 0; i < _members.size(); ++i)
    {
        if (i > 0) list += " ";
        
        // Operator prefix with color
        if (isOperator(_members[i]))
            list += std::string(BRIGHT_RED) + "@" + MAGENTA;
        else
            list += std::string(GREEN);
        
        list += _members[i]->getNickname() + RESET;
    }
    return list;
}
