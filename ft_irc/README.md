# 🌐 FT_IRC - Internet Relay Chat Server

_This project was created as part of the 42 curriculum by miaviles, rmunoz-c, carlsanc_

- Miguel Ángel Avilés (miaviles) - [GitHub](https://github.com/miaviles11)
- Rubén Muñoz Calderón (rmunoz-c) - [GitHub](https://github.com/rmunoz-c)
- Carlos Vicente Sánchez (carlsanc) - [GitHub](https://github.com/CarlosVSL)

## 📖 Description

> 📡 A complete IRC server implemented in C++98 following RFC 1459, with support for channels, operators, modes and an interactive bot as bonus.

### Project Objective

The main objective is to understand and master:
- **TCP/IP socket programming** in C++
- **Multiplexed I/O handling** with `poll()`
- **Managing multiple simultaneous connections** without threads
- **IRC protocol implementation** (authentication, channels, operators, modes)
- **Client-server architecture** and network communication
- **Teamwork and task assignment**
- **Automation and command handling** in the bonus part

### Main Features

- ✅ **Secure authentication** via password
- ✅ **Channel management** with operators and modes (+i, +t, +k, +o, +l)
- ✅ **Standard IRC commands** (JOIN, PART, PRIVMSG, KICK, INVITE, TOPIC, MODE, etc.)
- ✅ **Support for multiple simultaneous users and channels**
- ✅ **Compatible with real IRC clients** (HexChat, Irssi, WeeChat)
- ✅ **Interactive bot (bonus)** with useful and entertaining commands

The server is optimized to handle concurrent connections efficiently, using a non-blocking I/O model that guarantees scalability and performance.

---

## 📋 Table of Contents

- [🚀 Quick Start](#-instructions)
- [✨ Features](#-features)
- [🧪 Testing](#-testing)
  - [Phase 1: Server Startup](#phase-1-server-startup)
  - [Phase 2: Authentication](#-phase-2-authentication)
  - [Phase 3: Basic Channels](#-phase-3-basic-channels)
  - [Phase 4: Channel Operators](#-phase-4-channel-operators)
  - [Phase 5: Channel Modes](#-phase-5-channel-modes)
  - [Phase 6: User Modes](#-phase-6-user-modes)
  - [Phase 7: Multiple Users](#-phase-7-multiple-users-and-channels)
  - [Phase 8: Edge Cases](#️-phase-8-edge-cases-and-errors)
  - [Phase 9: Real IRC Clients](#-phase-9-integration-with-real-irc-clients)
  - [🤖 BONUS: HelpBot](#-bonus-helpbot-irc-bot)
- [👥 Test Users](#-test-users)
- [📚 Resources](#-resources)

---

## 🚀 Instructions

### System Requirements

- **Operating System:** Linux/macOS
- **Compiler:** g++ with C++98 support
- **Tools:** make, netcat (nc)

### Compilation

```bash
# Clone the repository
git clone https://github.com/your-user/ft_irc.git
cd ft_irc

# Compile the IRC server
make

# Compile the bot (bonus)
make bot

# Clean object files
make clean

# Clean everything (including binaries)
make fclean

# Recompile everything from scratch
make re
```

---

## 🧪 Testing

> **Note:** All tests are designed to run with `nc` (netcat) or real IRC clients.

---

<details>
<summary><h3>📌 PHASE 1: SERVER STARTUP</h3></summary>

#### Test 1.1: Basic startup
```bash
# Terminal 1 (Server)
./ircserv 6667 password123
```

**✅ Expected output:**

```
[SERVER] Initializing on port 6667
[SOCKET] Socket created (fd=3)
[SOCKET] ✓ Socket configured (non-blocking + SO_REUSEADDR)
[SOCKET] ✓ Bound to 0.0.0.0:6667
[SOCKET] ✓ Listening (backlog=4096)
[SERVER] ✓ Ready on port 6667

╔══════════════════════════════════════╗
║   IRC SERVER STARTED                 ║
║   Port: 6667                         ║
║   Press Ctrl+C to exit               ║
╚══════════════════════════════════════╝

[SERVER] Main loop started
```

---

#### Test 1.2: Invalid port

```bash
# Test invalid ports
./ircserv 80 test      # ❌ Privileged port
./ircserv 70000 test   # ❌ Out of range
./ircserv abc test     # ❌ Non-numeric
```

**✅ Expected result:** All should error without crashing

---

#### Test 1.3: Empty password

```bash
./ircserv 6667 ""      # ❌ Should reject
```

**✅ Expected result:**
```
[ERROR] Password cannot be empty
```

</details>

---

<details>
<summary><h3>🔐 PHASE 2: AUTHENTICATION</h3></summary>

#### Test 2.1: Basic connection

```bash
# Terminal 2 (USER1)
nc localhost 6667
```

**✅ On the server you should see:**
```
[SOCKET] ✓ Accepted connection from 127.0.0.1 (fd=4)
[SERVER] ✓ New client from 127.0.0.1 (fd=4, total=1)
```

---

#### Test 2.2: Incorrect password

```bash
# Terminal 2
PASS wrongpassword
NICK TestUser
USER test 0 * :Test
```

**✅ You should see:**
```
:ft_irc 464 * :Password incorrect
```
And then the connection closes

---

#### Test 2.3: Correct sequence (PASS → NICK → USER)

```bash
# Terminal 2 (Reconnect if closed)
nc localhost 6667

PASS password123
NICK Alice
USER alice 0 * :Alice Wonderland
```

**✅ You should see welcome messages:**
```
:ft_irc 001 Alice :Welcome to the FT_IRC Network Alice!alice@127.0.0.1
:ft_irc 002 Alice :Your host is ft_irc, running version 1.0
:ft_irc 003 Alice :This server was created today
:ft_irc 004 Alice ft_irc 1.0 io tkl
```

---

#### Test 2.4: Incorrect sequence (without PASS)

```bash
# Terminal 3 (new client)
nc localhost 6667

NICK Bob
USER bob 0 * :Bob

# Try to do something:
JOIN #test
```

**✅ Should see unregistered error**

---

#### Test 2.5: Duplicate nickname

```bash
# Terminal 3 (with correct PASS now)
nc localhost 6667

PASS password123
NICK Alice    # ❌ Already exists
```

**✅ You should see:**
```
:ft_irc 433 * Alice :Nickname is already in use
```

---

#### Test 2.6: Invalid nickname

```bash
# Terminal 3
PASS password123
NICK Alice@123   # ❌ Invalid character
NICK 123Alice    # ❌ Starts with number
```

**✅ Should reject with:**
```
:ft_irc 432 * <nick> :Erroneous nickname
```

---

#### Test 2.7: Nickname change

```bash
# Terminal 2 (Alice connected)
NICK AliceNew
```

**✅ You should see confirmation:**
```
:Alice!alice@127.0.0.1 NICK :AliceNew
```

</details>

---

<details>
<summary><h3>📢 PHASE 3: BASIC CHANNELS</h3></summary>

#### Test 3.1: Create and join channel

```bash
# Terminal 2 (Alice)
JOIN #general
```

**✅ You should see:**
```
:AliceNew!alice@127.0.0.1 JOIN #general
:ft_irc 331 AliceNew #general :No topic is set
:ft_irc 353 AliceNew = #general :@AliceNew
:ft_irc 366 AliceNew #general :End of /NAMES list
```

> **Note:** `@` indicates you are an operator (channel creator)

---

#### Test 3.2: Second user joins

```bash
# Terminal 3 (Bob - make sure you're registered)
nc localhost 6667
PASS password123
NICK Bob
USER bob 0 * :Bob Builder
JOIN #general
```

**✅ Bob sees:**
```
:Bob!bob@127.0.0.1 JOIN #general
:ft_irc 331 Bob #general :No topic is set
:ft_irc 353 Bob = #general :@AliceNew Bob
:ft_irc 366 Bob #general :End of /NAMES list
```

**✅ Alice sees (in Terminal 2):**
```
:Bob!bob@127.0.0.1 JOIN #general
```

---

#### Test 3.3: Send messages to channel

```bash
# Terminal 2 (Alice)
PRIVMSG #general :Hello everyone!
```

**✅ Bob sees (Terminal 3):**
```
:AliceNew!alice@127.0.0.1 PRIVMSG #general :Hello everyone!
```

```bash
# Terminal 3 (Bob responds)
PRIVMSG #general :Hi Alice!
```

**✅ Alice sees:**
```
:Bob!bob@127.0.0.1 PRIVMSG #general :Hi Alice!
```

---

#### Test 3.4: Private message (user to user)

```bash
# Terminal 2 (Alice)
PRIVMSG Bob :This is a private message
```

**✅ Bob sees (Terminal 3):**
```
:AliceNew!alice@127.0.0.1 PRIVMSG Bob :This is a private message
```

> **⚠️ IMPORTANT:** Alice should NOT see this message reflected

---

#### Test 3.5: Join multiple channels

```bash
# Terminal 2 (Alice)
JOIN #random
JOIN #dev

# Terminal 3 (Bob)
JOIN #dev
```

Now:
- Alice is in: `#general`, `#random`, `#dev`
- Bob is in: `#general`, `#dev`

---

#### Test 3.6: PART (leave channel)

```bash
# Terminal 2 (Alice)
PART #random
```

**✅ Alice sees:**
```
:AliceNew!alice@127.0.0.1 PART #random :Leaving
```

```bash
# Test with reason:
PART #dev :Going to sleep
```

**✅ You should see:**
```
:AliceNew!alice@127.0.0.1 PART #dev :Going to sleep
```

> **✅ Bob also sees this (because he's in #dev)**

---

#### Test 3.7: NAMES (list users in channel)

```bash
# Terminal 2 (Alice in #general with Bob and Charlie)
NAMES #general
```

**✅ You should see:**
```
:ft_irc 353 AliceNew = #general :@AliceNew Bob Charlie
:ft_irc 366 AliceNew #general :End of /NAMES list
```

> **Note:** `@` indicates operator

```bash
# Test without parameters (lists ALL channels):
NAMES
```

**✅ You should see all channels you're in:**
```
:ft_irc 353 AliceNew = #general :@AliceNew Bob Charlie
:ft_irc 353 AliceNew = #random :@AliceNew
:ft_irc 366 AliceNew * :End of /NAMES list
```

---

#### Test 3.8: NAMES (without # auto-correction)

```bash
# Terminal 2
NAMES general
```

**✅ The server adds # automatically:**
```
:ft_irc 353 AliceNew = #general :@AliceNew Bob Charlie
:ft_irc 366 AliceNew #general :End of /NAMES list
```

---

#### Test 3.9: NAMES (non-existent channel)

```bash
NAMES #noexiste
```

**✅ Should give error:**
```
:ft_irc 403 AliceNew #noexiste :No such channel
```

---

#### Test 3.10: NAMES (without being registered)

```bash
# New terminal without authentication
nc localhost 6667
PASS password123
NAMES #general
```

**❌ Should fail:**
```
:ft_irc 451 * :You have not registered
```

---

#### Test 3.11: WHO (detailed information of users in channel)

```bash
# Terminal 2 (Alice in #general with Bob)
WHO #general
```

**✅ You should see (table format with colors):**
```
:ft_irc 352 AliceNew #general alice 127.0.0.1 ft_irc AliceNew H@ :0 Alice Johnson
:ft_irc 352 AliceNew #general bob 127.0.0.1 ft_irc Bob H :0 Bob Smith
:ft_irc 315 AliceNew #general :End of /WHO list
```

> **Format:** `<channel> <user> <host> <server> <nick> <flags> :<hop> <realname>`  
> **Flags:** `H` = here, `H@` = here + channel operator

---

#### Test 3.12: WHO (search user by nickname)

```bash
# Terminal 2 (Alice searches for Bob)
WHO Bob
```

**✅ You should see:**
```
:ft_irc 352 AliceNew * bob 127.0.0.1 ft_irc Bob H :0 Bob Smith
:ft_irc 315 AliceNew Bob :End of /WHO list
```

> **Note:** `*` indicates no channel specified (user search)

---

#### Test 3.13-3.16: Additional WHO tests

```bash
# Without parameters
WHO

# Non-existent user
WHO Charlie    # ✅ Error 401

# Non-existent channel
WHO #noexiste  # ✅ Error 403

# Without being registered
# ✅ Error 451
```

---

#### Test 3.17: WHOIS (complete user profile)

```bash
# Terminal 3 (Bob executes WHOIS)
WHOIS Alice
```

**✅ You should see (5 lines with colors):**
```
:ft_irc 311 Bob Alice alice 127.0.0.1 * :Alice Wonderland
:ft_irc 319 Bob Alice :@#general
:ft_irc 312 Bob Alice ft_irc :FT IRC Server
:ft_irc 317 Bob Alice 0 1766171247 :seconds idle, signon time
:ft_irc 318 Bob Alice :End of /WHOIS list
```

**Format explained:**
- `[311]` RPL_WHOISUSER: `<nick> <username> <host> * :<realname>`
- `[319]` RPL_WHOISCHANNELS: `<nick> :<channels>` (`@` = operator)
- `[312]` RPL_WHOISSERVER: `<nick> <server> :<server info>`
- `[317]` RPL_WHOISIDLE: `<nick> <idle_seconds> <signon_timestamp> :description`
- `[318]` RPL_ENDOFWHOIS: `<nick> :End of /WHOIS list`

---

#### Test 3.18: WHOIS (multiple channels)

```bash
# Terminal 2 (Alice in #general, #random, #dev)
JOIN #random
JOIN #dev

# Terminal 3 (Bob)
WHOIS Alice
```

**✅ Line 319 should show:**
```
:ft_irc 319 Bob Alice :@#general @#random @#dev
```

---

#### Test 3.19: WHOIS (idle time increases)

```bash
# Terminal 2 (Alice without writing anything for 30 seconds)

# Terminal 3 (Bob does WHOIS)
WHOIS Alice
```

**✅ Should show:**
```
:ft_irc 317 Bob Alice 30 1766171247 :seconds idle, signon time
```

If Alice writes something, the idle resets to 0-2 seconds.

---

#### Test 3.20-3.23: Additional WHOIS tests

```bash
# Non-existent user
WHOIS Charlie    # ✅ Error 401

# Without parameters
WHOIS            # ✅ Error 431

# Without being registered
# ✅ Error 451

# Comparison WHO vs WHOIS:
# WHO  = fast, multiple users, table format
# WHOIS = detailed, one user, complete profile
```

</details>

---

<details>
<summary><h3>👑 PHASE 4: CHANNEL OPERATORS</h3></summary>

#### Test 4.1: TOPIC (view and change)

```bash
# Terminal 2 (Alice - operator of #general)
TOPIC #general
```

**✅ View current topic:**
```
:ft_irc 331 AliceNew #general :No topic is set
```

```bash
# Change topic:
TOPIC #general :Welcome to the general channel!
```

**✅ Everyone in the channel sees:**
```
:AliceNew!alice@127.0.0.1 TOPIC #general :Welcome to the general channel!
```

---

#### Test 4.2: TOPIC (non-operator user tries to change)

```bash
# Terminal 3 (Bob - NOT an operator)
TOPIC #general :Bob's topic
```

**✅ Should fail with:**
```
:ft_irc 482 Bob #general :You're not channel operator
```

> (Only if +t mode is active, which is default)

---

#### Test 4.3: MODE +o (give operator)

```bash
# Terminal 2 (Alice)
MODE #general +o Bob
```

**✅ Everyone sees:**
```
:AliceNew!alice@127.0.0.1 MODE #general +o Bob
```

```bash
# Now Bob can change the topic:
# Terminal 3 (Bob)
TOPIC #general :Bob is now OP!
```

**✅ Works**

---

#### Test 4.4: KICK (expel user)

```bash
# Terminal 4 (Charlie - new user)
nc localhost 6667
PASS password123
NICK Charlie
USER charlie 0 * :Charlie
JOIN #general

# Terminal 2 (Alice expels Charlie)
KICK #general Charlie :Bad behavior
```

**✅ Everyone in the channel sees:**
```
:AliceNew!alice@127.0.0.1 KICK #general Charlie :Bad behavior
```

**✅ Charlie (Terminal 4) is expelled from the channel**

---

#### Test 4.5: INVITE (invite to +i channel)

```bash
# Terminal 2 (Alice activates invite-only mode)
MODE #general +i
```

**✅ Everyone sees:**
```
:AliceNew!alice@127.0.0.1 MODE #general +i
```

```bash
# Terminal 4 (Charlie tries to join)
JOIN #general
```

**❌ Should fail:**
```
:ft_irc 473 Charlie #general :Cannot join channel (+i)
```

```bash
# Terminal 2 (Alice invites Charlie)
INVITE Charlie #general
```

**✅ Alice sees:**
```
:ft_irc 341 AliceNew Charlie #general
```

**✅ Charlie sees:**
```
:AliceNew!alice@127.0.0.1 INVITE Charlie #general
```

```bash
# Now Charlie can join:
# Terminal 4
JOIN #general
```

**✅ Works**

</details>

---

<details>
<summary><h3>🔧 PHASE 5: CHANNEL MODES</h3></summary>

#### Test 5.1: MODE +k (channel with password)

```bash
# Terminal 2 (Alice)
MODE #general +k secretpass
```

**✅ Confirmation:**
```
:AliceNew!alice@127.0.0.1 MODE #general +k secretpass
```

```bash
# Terminal 4 (Charlie disconnected, reconnects)
nc localhost 6667
PASS password123
NICK Charlie
USER charlie 0 * :Charlie
JOIN #general
```

**❌ Should fail:**
```
:ft_irc 475 Charlie #general :Cannot join channel (+k)
```

```bash
# Try with key:
JOIN #general secretpass
```

**✅ Works**

---

#### Test 5.2: MODE -k (remove password)

```bash
# Terminal 2 (Alice)
MODE #general -k secretpass
```

**✅ Confirmation:**
```
:AliceNew!alice@127.0.0.1 MODE #general -k *
```

Now anyone can join without key

---

#### Test 5.3: MODE +l (user limit)

```bash
# Terminal 2 (Alice)
MODE #general +l 3
```

**✅ Confirmation:**
```
:AliceNew!alice@127.0.0.1 MODE #general +l 3
```

```bash
# Verify current users:
# Alice, Bob, Charlie = 3 users (limit reached)

# Terminal 5 (new user Dave)
nc localhost 6667
PASS password123
NICK Dave
USER dave 0 * :Dave
JOIN #general
```

**❌ Should fail:**
```
:ft_irc 471 Dave #general :Cannot join channel (+l)
```

---

#### Test 5.4: MODE -l (remove limit)

```bash
# Terminal 2 (Alice)
MODE #general -l
```

**✅ Confirmation:**
```
:AliceNew!alice@127.0.0.1 MODE #general -l
```

```bash
# Now Dave can join:
# Terminal 5
JOIN #general
```

**✅ Works**

---

#### Test 5.5: MODE +t (topic restricted to OPs)

```bash
# Terminal 2 (Alice)
MODE #general -t
```

**✅ Now Bob (non-OP) can change the topic:**
```bash
# Terminal 3 (Bob)
TOPIC #general :Anyone can change this
```

**✅ Works**

```bash
# Reactivate restriction:
# Terminal 2 (Alice)
MODE #general +t

# Now Bob can't:
# Terminal 3
TOPIC #general :Bob tries again
```

**❌ Fails:**
```
:ft_irc 482 Bob #general :You're not channel operator
```

---

#### Test 5.6: Query current modes

```bash
# Any user in the channel
MODE #general
```

**✅ Should show:**
```
:ft_irc 324 <nick> #general +it
```

</details>

---

<details>
<summary><h3>👤 PHASE 6: USER MODES</h3></summary>

#### Test 6.1: MODE +i (invisible)

```bash
# Terminal 2 (Alice)
MODE Alice +i
```

**✅ Confirmation:**
```
:AliceNew!alice@127.0.0.1 MODE AliceNew :+i
```

```bash
# Query mode:
MODE Alice
```

**✅ Should show:**
```
:ft_irc 221 AliceNew +i
```

---

#### Test 6.2: MODE -i (visible)

```bash
# Terminal 2
MODE Alice -i
```

**✅ Confirmation:**
```
:AliceNew!alice@127.0.0.1 MODE AliceNew :-i
```

</details>

---

<details>
<summary><h3>🔄 PHASE 7: MULTIPLE USERS AND CHANNELS</h3></summary>

#### Test 7.1: Broadcast in channel with 3+ users

```bash
# Setup: Alice, Bob, Charlie in #general

# Terminal 2 (Alice)
PRIVMSG #general :Testing broadcast
```

- ✅ Bob (Terminal 3) should see the message
- ✅ Charlie (Terminal 4) should see the message
- ⚠️ Alice should NOT see her own message reflected

---

#### Test 7.2: User in multiple channels receives only from the correct channel

```bash
# Setup:
# Alice: #general, #dev
# Bob: #general
# Charlie: #dev

# Terminal 2 (Alice in #general)
PRIVMSG #general :Message to general
```

- ✅ Bob sees it
- ❌ Charlie does NOT see it (not in #general)

```bash
# Terminal 2 (Alice in #dev)
PRIVMSG #dev :Message to dev
```

- ✅ Charlie sees it
- ❌ Bob does NOT see it (not in #dev)

---

#### Test 7.3: QUIT propagates to all channels

```bash
# Setup: Alice in #general and #dev with other users

# Terminal 2 (Alice)
QUIT :Goodbye!
```

**✅ All users in #general and #dev see:**
```
:AliceNew!alice@127.0.0.1 QUIT :Goodbye!
```

**✅ On the server:**
```
[DISCONNECT] fd=4 (graceful close)
```

</details>

---

<details>
<summary><h3>⚠️ PHASE 8: EDGE CASES AND ERRORS</h3></summary>

#### Test 8.1: Commands without registration

```bash
# New terminal without PASS/NICK/USER
nc localhost 6667

JOIN #test
PRIVMSG #test :Hello
KICK #test Bob
```

**✅ All should give:**
```
:ft_irc 451 * :You have not registered
```

---

#### Test 8.2: Missing parameters

```bash
# Registered terminal
JOIN
MODE
KICK #test
INVITE Charlie
TOPIC
```

**✅ All should give:**
```
:ft_irc 461 <nick> <CMD> :Not enough parameters
```

---

#### Test 8.3: Non-existent channel

```bash
PART #nonexistent
PRIVMSG #nonexistent :Hello
```

**✅ Should give:**
```
:ft_irc 403 <nick> #nonexistent :No such channel
```

---

#### Test 8.4: Non-existent user

```bash
PRIVMSG NonExistentUser :Hello
```

**✅ Should give:**
```
:ft_irc 401 <nick> NonExistentUser :No such nick/channel
```

---

#### Test 8.5: Try to kick without being OP

```bash
# Terminal 3 (Bob, non-OP)
KICK #general Charlie :Bye
```

**✅ Should give:**
```
:ft_irc 482 Bob #general :You're not channel operator
```

---

#### Test 8.6: Message flood (stress test)

```bash
# Terminal 2
for i in {1..100}; do echo "PRIVMSG #general :Message $i"; done | nc localhost 6667
```

- ✅ The server should NOT crash
- ✅ All messages should arrive (may take a few seconds)

---

#### Test 8.7: Abrupt disconnection (Ctrl+C on client)

```bash
# Terminal 3 (Bob)
# Press Ctrl+C without QUIT
```

**✅ On server:**
```
[DISCONNECT] fd=X (POLLHUP/ERR)
```

**✅ Other users in Bob's channels see:**
```
:Bob!bob@127.0.0.1 QUIT :Connection closed
```

---

#### Test 8.8: Special characters in messages

```bash
PRIVMSG #general :Test with émojis 🚀 and spëcial çhars
```

**✅ Should transmit correctly**

</details>

---

<details>
<summary><h3>🧪 PHASE 9: INTEGRATION WITH REAL IRC CLIENTS</h3></summary>

#### Test 9.1: HexChat

```bash
# 1. Open HexChat
# 2. Network List → Add
# 3. Name: "ft_irc_test"
# 4. Servers: localhost/6667
# 5. Edit → Password: password123
# 6. Connect
```

- ✅ Should connect successfully
- ✅ Should be able to JOIN, PRIVMSG, etc.

---

#### Test 9.2: Irssi

```bash
irssi

# Inside irssi:
/server add ft_irc localhost 6667 password123
/connect localhost 6667 password123 TestUser
/join #general
```

**✅ Should work as a real server**

---

#### Test 9.3: WeeChat

```bash
weechat

# Inside weechat:
/server add ft_irc localhost/6667
/set irc.server.ft_irc.password password123
/connect ft_irc
/join #general
```

**✅ Should work**

</details>

---

## 👥 Test Users

```bash
# User 1 (Alice)
PASS pass123
NICK Alice
USER alice 0 * :Alice

# User 2 (Bob)
PASS pass123
NICK Bob
USER bob 0 * :Bob

# User 3 (Charlie)
PASS pass123
NICK Charlie
USER charlie 0 * :Charlie
```

### Test Channel

```bash
JOIN #general
```

### Test Message

```bash
PRIVMSG #general :HELLO
```

---

<details>
<summary><h3>🤖 BONUS: HELPBOT (IRC BOT)</h3></summary>

### Prerequisites

```bash
# 1. Compile the bot
make bot

# 2. In a separate terminal, make sure the server is running:
./ircserv 6667 pass123
```

---

#### Test B.1: Start the bot

```bash
# Bot Terminal
./bot 127.0.0.1 6667 pass123
```

**✅ You should see:**
```
[BOT] Connected to 127.0.0.1:6667
[BOT] -> PASS pass123
[BOT] -> NICK HelpBot
[BOT] -> USER helpbot 0 * :IRC Help Bot
[BOT] Authentication sent
[BOT] -> JOIN #general
[BOT] Joining channel: #general
[BOT] -> JOIN #help
[BOT] Joining channel: #help
[BOT] Bot is now running. Listening for messages...
```

> **Note:** The bot automatically joins #general and #help

---

#### Test B.2: Verify the bot is in the channel

```bash
# Terminal 2 (Alice)
nc localhost 6667
PASS pass123
NICK Alice
USER alice 0 * :Alice
JOIN #general
NAMES #general
```

**✅ You should see:**
```
:ft_irc 353 Alice = #general :@HelpBot Alice
                              ^^^^^^^^
                              The bot is present with OP
```

---

#### Test B.3: Command !help (list of commands)

```bash
# Terminal 2 (Alice in #general)
PRIVMSG #general :!help
```

**✅ Alice receives:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Available commands: !help, !time, !uptime, !echo <msg>, !joke, !ping
```

**✅ On the bot (Bot Terminal):**
```
[BOT] <- :Alice!alice@127.0.0.1 PRIVMSG #general :!help
[BOT] -> PRIVMSG #general :Available commands: !help, !time, !uptime, !echo <msg>, !joke, !ping
```

---

#### Test B.4: Command !time (current time)

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!time
```

**✅ Alice receives:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Current time: 2026-01-20 18:45:30
                                                            ^^^^^^^^^^^^^^^^^^^^^^^
                                                            System time
```

---

#### Test B.5: Command !uptime (running time)

```bash
# Terminal 2 (Alice - wait a few seconds after starting the bot)
PRIVMSG #general :!uptime
```

**✅ Alice receives:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Bot uptime: 0h 2m 45s
                                                         ^^^^^^^^^^^
                                                         Time since startup
```

---

#### Test B.6: Command !echo (repeat message)

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!echo Hello IRC World!
```

**✅ Alice receives:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Hello IRC World!
```

```bash
# Test without arguments:
PRIVMSG #general :!echo
```

**✅ Alice receives:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Usage: !echo <message>
```

---

#### Test B.7: Command !joke (random joke)

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!joke
```

**✅ Alice receives (one of 10 random jokes):**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Why do programmers prefer dark mode? Because light attracts bugs!
```

```bash
# Execute several times to see different jokes:
PRIVMSG #general :!joke
PRIVMSG #general :!joke
```

---

#### Test B.8: Command !ping (connection test)

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!ping
```

**✅ Alice receives:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Pong! 🏓
```

---

#### Test B.9: Case-insensitive commands

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!HELP
PRIVMSG #general :!Time
PRIVMSG #general :!PiNg
```

**✅ All work (the bot converts to lowercase)**

---

#### Test B.10: Direct private message to the bot

```bash
# Terminal 2 (Alice)
PRIVMSG HelpBot :!help
```

**✅ Alice receives (PRIVATELY, NOT in the channel):**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG Alice :Available commands: !help, !time, !uptime, !echo <msg>, !joke, !ping
                                   ^^^^^
                                   Private response to Alice
```

> **⚠️ IMPORTANT:** Other users in #general do NOT see this exchange

---

#### Test B.11: Private commands (all functions)

```bash
# Terminal 2 (Alice privately with the bot)
PRIVMSG HelpBot :!time
PRIVMSG HelpBot :!uptime
PRIVMSG HelpBot :!echo Testing private echo
PRIVMSG HelpBot :!joke
PRIVMSG HelpBot :!ping
```

**✅ All responses arrive PRIVATELY to Alice**

---

#### Test B.12: Multiple users using the bot simultaneously

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!time

# Terminal 3 (Bob - connected in #general)
nc localhost 6667
PASS pass123
NICK Bob
USER bob 0 * :Bob
JOIN #general
PRIVMSG #general :!joke
```

- ✅ Both receive their responses in the channel
- ✅ The bot does NOT get confused between users

---

#### Test B.13: Bot in #help channel

```bash
# Terminal 2 (Alice)
JOIN #help
PRIVMSG #help :!help
```

**✅ The bot also responds in #help:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #help :Available commands: !help, !time, !uptime, !echo <msg>, !joke, !ping
```

---

#### Test B.14: Invalid commands ignored

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!invalid
PRIVMSG #general :!xyz123
PRIVMSG #general :Hello everyone
```

- ✅ The bot does NOT respond (only processes valid commands starting with !)
- ✅ Normal messages without '!' are ignored

---

#### Test B.15: Bot responds to server PING automatically

```bash
# Check in the Bot Terminal while it's running
```

**✅ If the server sends PING, you should see:**
```
[BOT] <- PING :ft_irc
[BOT] -> PONG :ft_irc
```

> **⚠️ IMPORTANT:** This happens automatically, no intervention required

---

#### Test B.16: Verify bot cleans ANSI codes correctly

```bash
# Terminal 2 (Alice)
PRIVMSG #general :!help
```

**✅ The bot should respond correctly even if the server sends messages with ANSI color codes**

**✅ Should not send "56:13" or strange characters as target**

**Verify on the server that NO errors appear:**
- ❌ Should NOT see: `[SERVER DEBUG] ERROR: Channel not found`
- ✅ The message is transmitted cleanly

---

#### Test B.17: Bot remains active with server under load

```bash
# Terminal 4 (generate traffic)
for i in {1..50}; do 
  echo "PRIVMSG #general :Message $i"; 
done | nc localhost 6667 &

# Terminal 2 (Alice - while there's traffic)
PRIVMSG #general :!ping
```

- ✅ The bot continues responding correctly
- ✅ Does NOT crash with multiple messages

---

#### Test B.18: Stop the bot with Ctrl+C

```bash
# Bot Terminal
# Press Ctrl+C
```

**✅ The bot should close cleanly:**
```
^C
[BOT] Bot stopped.
```

**✅ On the server:**
```
[DISCONNECT] fd=X (graceful close)
```

**✅ Other users in #general and #help see:**
```
:HelpBot!helpbot@127.0.0.1 QUIT :Connection closed
```

---

#### Test B.19: Restart the bot and verify reset uptime

```bash
# Bot Terminal (after closing and restarting)
./bot 127.0.0.1 6667 pass123

# Wait a few seconds...

# Terminal 2 (Alice)
PRIVMSG #general :!uptime
```

**✅ Alice receives:**
```
:HelpBot!helpbot@127.0.0.1 PRIVMSG #general :Bot uptime: 0h 0m 15s
                                                         ^^^^^^^^^^^
                                                         Time since new start
```

---

#### Test B.20: Bot with incorrect parameters

```bash
# Test with invalid IP
./bot 999.999.999.999 6667 pass123
```

**✅ Should show error without crashing:**
```
[BOT] Error: Invalid IP address
```

```bash
# Test with invalid port
./bot 127.0.0.1 99999 pass123
```

**✅ Should fail to connect:**
```
[BOT] Error: Failed to connect to 127.0.0.1:99999
```

```bash
# Test with incorrect password
./bot 127.0.0.1 6667 wrongpass
```

**✅ Should connect but be rejected:**
```
[BOT] <- :ft_irc 464 * :Password incorrect
```
And then closes

---

### 🎯 Bot Summary

#### Available commands:

| Command | Description |
|---------|-------------|
| `!help` | List of available commands |
| `!time` | Shows current system time |
| `!uptime` | Shows how long the bot has been running |
| `!echo <msg>` | Repeats the provided message |
| `!joke` | Tells a random programming joke |
| `!ping` | Responds with "Pong! 🏓" |

#### Features:

```
✅ Connects automatically to the server
✅ Joins #general and #help on startup
✅ Responds in public channels
✅ Responds to private messages
✅ Case-insensitive commands
✅ Handles PING/PONG automatically
✅ Cleans ANSI codes from server
✅ Doesn't crash with multiple users
✅ Clean shutdown with Ctrl+C
```

#### Usage:

```bash
make bot
./bot <IP> <PORT> <PASSWORD>
```

#### Example:

```bash
./bot 127.0.0.1 6667 pass123
```

</details>

---

## 📚 Resources

### Documentation

- [RFC 2811 - Internet Relay Chat: Channel Management](https://tools.ietf.org/html/rfc2811) - IRC channel management
- [RFC 2812 - IRC Client Protocol](https://tools.ietf.org/html/rfc2812) - Updated IRC client protocol
- [RFC 2813 - IRC Server Protocol](https://tools.ietf.org/html/rfc2813) - IRC server protocol
- [📄 Project Subject (PDF)](https://cdn.intra.42.fr/pdf/pdf/188979/es.subject.pdf) - Official 42 subject


### Tools Used

- **netcat (nc)** - Simple TCP/IP client for testing
- **HexChat** - Graphical IRC client for testing
- **Irssi** - Terminal IRC client
- **WeeChat** - Extensible IRC client
- **Valgrind** - Memory leak and memory error detection

### Use of Artificial Intelligence

In this project **GitHub Copilot** and **ChatGPT** have been used as assistance tools in the following areas:

- **Correction of parsing and code errors**
- **Code optimization**
- **Technical explanations of C++ and IRC protocol**
- **Help with organization and work distribution**
- **Help in general approach and file structure**
- **Testing suggestions and edge case management**

**Important:** All code generated or suggested by AI was:
- ✅ Reviewed and fully understood by the team
- ✅ Adapted to the specific project requirements
- ✅ Exhaustively tested in multiple scenarios
- ✅ Validated against the 42 norm and C++98 standard

AI was used as a **support tool**, not as an automatic code generator. The design, architecture and main technical decisions were made by the development team.

---
