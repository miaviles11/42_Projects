/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-05 15:09:53 by rmunoz-c          #+#    #+#             */
/*   Updated: 2025-12-05 15:09:53 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include <string>
#include <vector>

class Channel;
class ClientConnection;

/**
 * -R- Represents the IRC user identity and state.
 * -R- Contains nickname, username, realname, modes, and channel memberships.
 * -R- One User can exist even if the connection drops (for reconnection scenarios).
**/
class User
{
    public:
        User();
        User(const std::string& nickname);
        ~User();

        /* Identity */
        const std::string&	getNickname() const;
        void				setNickname(const std::string& nick);
        
        const std::string&	getUsername() const;
        void				setUsername(const std::string& user);
        
        const std::string&	getRealname() const;
        void				setRealname(const std::string& real);
        
        const std::string&	getHostname() const;
        void				setHostname(const std::string& host);

        /* Full user mask: nick!user@host */
        std::string			getPrefix() const;	//* Returns nick!user@host

        /* Modes */
        bool				isOperator() const;
        void				setOperator(bool op);
        
        bool				isInvisible() const;
        void				setInvisible(bool inv);
        
        bool				isAway() const;
        void				setAway(bool away);
        const std::string&	getAwayMessage() const;
        void				setAwayMessage(const std::string& msg);

        /* Channel membership */
        void				joinChannel(Channel* channel);
        void				leaveChannel(Channel* channel);
        bool				isInChannel(Channel* channel) const;
        const std::vector<Channel*>& getChannels() const;

        /* Connection association */
        void				setConnection(ClientConnection* conn);
        ClientConnection*	getConnection() const;
        bool				isConnected() const;

    private:
        std::string	_nickname;					//* IRC nickname (NICK command)
        std::string	_username;					//* Username from USER command
        std::string	_realname;					//* Real name from USER command
        std::string	_hostname;					//* Client hostname/IP

        bool		_isOperator;				//* Server operator status
        bool		_isInvisible;				//* Invisible mode (+i)
        bool		_isAway;					//* Away status (AWAY command)
        std::string	_awayMessage;				//* Away message if set

        std::vector<Channel*>	_channels;		//* List of joined channels
        ClientConnection*		_connection;	//* NULL if disconnected

        User(const User&);
        User& operator=(const User&);
};

#endif