#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <set>
#include <algorithm>

// Forward declaration to avoid circular dependencies
class User;

class Channel
{
    public:
        // Constructor and Destructor
        Channel(const std::string& name);
        ~Channel();

        // ------------------------------------------------------------------
        // BASIC GETTERS
        // ------------------------------------------------------------------
        const std::string& getName() const;
        const std::string& getTopic() const;
        const std::string& getKey() const;
        
        // Limits and Count
        size_t getUserCount() const;
        int    getLimit() const;
        
        // ------------------------------------------------------------------
        // CHANNEL MODES (+i, +t, +k, +l)
        // ------------------------------------------------------------------
        std::string getModes() const;           // Returns string like "+itk" for RPL_CHANNELMODEIS
        bool        hasMode(char mode) const;
        void        setMode(char mode, bool active);
        
        void        setKey(const std::string& key);
        void        setLimit(int limit);
        void        setTopic(const std::string& topic);

        // ------------------------------------------------------------------
        // MEMBER MANAGEMENT
        // ------------------------------------------------------------------
        void    addMember(User* user);
        void    removeMember(User* user);
        bool    isMember(User* user) const;
        User*   getMember(const std::string& nick) const;

        /**
         * [IMPORTANT] REQUIRED FOR NICK COMMAND (Avoid Spam)
         * Returns the complete list of users to iterate and filter
         * who we send global notifications to.
         * Don't touch this >:(
         */
        const std::vector<User*>& getMembers() const;

        // ------------------------------------------------------------------
        // OPERATOR MANAGEMENT (+o)
        // ------------------------------------------------------------------
        void    addOperator(User* user);
        void    removeOperator(User* user);
        bool    isOperator(User* user) const;

        // ------------------------------------------------------------------
        // INVITE MANAGEMENT (+i)
        // ------------------------------------------------------------------
        void    addInvite(const std::string& nick);
        bool    isInvited(User* user) const; // Checks if user is in the whitelist

        // ------------------------------------------------------------------
        // COMMUNICATION
        // ------------------------------------------------------------------
        /**
         * Broadcast a message to all channel members.
         * 
         * Sends the message to all members in the channel.
         * If excludeUser is NULL, the message is sent to everyone.
         * If excludeUser is a valid User pointer, that user is skipped.
         * 
         * @param msg Message to send (must end with \r\n for IRC protocol)
         * @param excludeUser User to skip sending to (NULL = send to everyone)
         */
        void    broadcast(const std::string& msg, User* excludeUser);
        
        // Generates the names list for RPL_NAMREPLY (e.g.: "@Admin +User1 User2")
        std::string getNamesList() const;

    private:
        std::string _name;
        std::string _topic;
        std::string _key;       // Channel password (+k)
        int         _limit;     // User limit (+l), 0 = no limit

        // Boolean mode flags
        bool _inviteOnly;       // +i
        bool _topicOpOnly;      // +t
        bool _hasKey;           // +k enabled
        bool _hasLimit;         // +l enabled

        // Internal lists
        std::vector<User*>    _members;   // All users inside
        std::vector<User*>    _operators; // Subset of users who are OP
        std::set<std::string> _invites;   // Invited nicks (whitelist for +i)

        // Private constructor to forbid channels without name
        Channel(); 
};

#endif