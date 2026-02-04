NAME = ircserv
BOT_NAME = bot
CXX = c++

# Detect all folders inside srcs/ for includes (-I)
# This allows #include "Server.hpp" from main.cpp without errors
INC_DIRS = $(shell find srcs -type d)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 $(INC_FLAGS) -MMD -MP

# Search all .cpp files automatically
SRC = $(shell find srcs -name '*.cpp' ! -path '*/bot/*')
OBJ = $(SRC:.cpp=.o)
DEPS = $(OBJ:.o=.d)

# BOT files
BOT_SRC = srcs/bot/HelpBot.cpp srcs/bot/main_bot.cpp
BOT_OBJ = $(BOT_SRC:.cpp=.o)
BOT_DEPS = $(BOT_OBJ:.o=.d)

# ANSI colors
BLUE := \033[34m
GREEN := \033[32m
YELLOW := \033[33m
CYAN := \033[36m
MAGENTA := \033[35m
RESET := \033[0m

# Counter
TOTAL := $(words $(SRC))
BOT_TOTAL := $(words $(BOT_SRC))
CURRENT = 0

.DEFAULT_GOAL := all

all: $(NAME) $(BOT_NAME)
	@printf "$(GREEN)\r✅ Complete compilation [$(TOTAL)/$(TOTAL)]$(RESET)\n"

# Compile server
$(NAME): $(OBJ)
	@printf "$(CYAN)\r🔗 Linking server: $(NAME)                     $(RESET)\n"
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)
	@printf "$(GREEN)\r✅ Server compiled [$(TOTAL)/$(TOTAL)]         $(RESET)\n"

# Compile bot
$(BOT_NAME): $(BOT_OBJ)
	@printf "$(MAGENTA)\r🤖 Linking bot: $(BOT_NAME)                        $(RESET)\n"
	@$(CXX) $(CXXFLAGS) -o $@ $(BOT_OBJ)
	@printf "$(GREEN)\r✅ Bot compiled [$(BOT_TOTAL)/$(BOT_TOTAL)]           $(RESET)\n"

%.o: %.cpp
	@$(eval CURRENT=$(shell echo $$(($(CURRENT)+1))))
	@printf "$(BLUE)\r⚙️  Compiling [$(CURRENT)/$(TOTAL)]: %-50s$(RESET)" "$<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@printf "$(YELLOW)\r🧹 Cleaning objects...                  $(RESET)\n"
	@rm -f $(OBJ) $(DEPS) $(BOT_OBJ) $(BOT_DEPS)

fclean: clean
	@printf "$(YELLOW)\r🗑️  Deleting executable...               $(RESET)\n"
	@rm -f $(NAME) $(BOT_NAME)
	@printf "$(GREEN)\r✅ Complete cleanup.                    $(RESET)\n"

re: fclean all

# Run server
run: $(NAME)
	@./$(NAME) 6667 password123

# Run bot (assumes server is already running)
run-bot: $(BOT_NAME)
	@./$(BOT_NAME) 127.0.0.1 6667 password123

# Compile only the server
server: $(NAME)

# Compile only the bot
bot: $(BOT_NAME)

-include $(DEPS) $(BOT_DEPS)

.PHONY: all clean fclean re run run-bot server bot