/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NumericReplies.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlsanc <carlsanc@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:33:12 by carlsanc          #+#    #+#             */
/*   Updated: 2025/12/10 20:33:12 by carlsanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERIC_REPLIES_HPP
#define NUMERIC_REPLIES_HPP

/* ========================================================================== */
/* INFORMATIONAL REPLIES (001-399)                                            */
/* ========================================================================== */

// Connection & Welcome
#define RPL_WELCOME         "001"
#define RPL_YOURHOST        "002"
#define RPL_CREATED         "003"
#define RPL_MYINFO          "004"

// Server Ops
#define RPL_YOUREOPER       "381"

// Channel Info
#define RPL_CHANNELMODEIS   "324" // <channel> <modes> <mode-params>
#define RPL_CREATIONTIME    "329" // <channel> <creationtime>
#define RPL_NOTOPIC         "331"
#define RPL_TOPIC           "332"
#define RPL_INVITING        "341"
#define RPL_NAMREPLY        "353"
#define RPL_ENDOFNAMES      "366"

// User Info
#define RPL_UMODEIS         "221"
#define RPL_WHOISUSER       "311"
#define RPL_WHOISSERVER     "312"
#define RPL_WHOISOPERATOR   "313"
#define RPL_ENDOFWHO        "315"
#define RPL_WHOISIDLE       "317"
#define RPL_ENDOFWHOIS      "318"
#define RPL_WHOISCHANNELS   "319"
#define RPL_WHOREPLY        "352"

// Lists
#define RPL_LISTSTART       "321"
#define RPL_LIST            "322"
#define RPL_LISTEND         "323"

/* ========================================================================== */
/* ERROR REPLIES (400-599)                                                    */
/* ========================================================================== */

// Generic / Nicknames
#define ERR_NOSUCHNICK          "401"
#define ERR_NOSUCHSERVER        "402"
#define ERR_NOSUCHCHANNEL       "403"
#define ERR_CANNOTSENDTOCHAN    "404"
#define ERR_TOOMANYCHANNELS     "405"
#define ERR_NOORIGIN            "409"
#define ERR_NORECIPIENT         "411"
#define ERR_NOTEXTTOSEND        "412"
#define ERR_UNKNOWNCOMMAND      "421"
#define ERR_NOMOTD              "422"
#define ERR_NONICKNAMEGIVEN     "431"
#define ERR_ERRONEUSNICKNAME    "432"
#define ERR_NICKNAMEINUSE       "433"
#define ERR_NICKCOLLISION       "436"
#define ERR_USERNOTINCHANNEL    "441"
#define ERR_NOTONCHANNEL        "442"
#define ERR_USERONCHANNEL       "443"
#define ERR_NOTREGISTERED       "451"

// Parameters & Registration
#define ERR_NEEDMOREPARAMS      "461"
#define ERR_ALREADYREGISTRED    "462"
#define ERR_PASSWDMISMATCH      "464"

// Channel Limits & Modes
#define ERR_CHANNELISFULL       "471"
#define ERR_UNKNOWNMODE         "472"
#define ERR_INVITEONLYCHAN      "473"
#define ERR_BANNEDFROMCHAN      "474"
#define ERR_BADCHANNELKEY       "475"
#define ERR_BADCHANMASK         "476"

// Permissions
#define ERR_NOPRIVILEGES        "481"
#define ERR_CHANOPRIVSNEEDED    "482"

// Mode specific
#define ERR_UMODEUNKNOWNFLAG    "501"
#define ERR_USERSDONTMATCH      "502"

#endif
