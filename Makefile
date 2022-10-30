NAME = ft_irc

# Config
# ****************************************************************************

CXX = c++
INCLUDE = -I src/Server/ -I src/User/ -I src/User/Command -I src/Commands/ConnectionRegistration
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror
CXXFLAGS += $(INCLUDE)

# Source files
# ****************************************************************************

SRC_DIR =		src/
SRC_FILES	=	Server/Server.cpp \
				Server/Error.cpp \
				User/User.cpp \
				User/Command/Command.cpp \
				Commands/ConnectionRegistration/nick.cpp \
				main.cpp \

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = objs/
OBJS = $(SRC_FILES:%.cpp=$(OBJ_DIR)%.o)

# Recipe
# ****************************************************************************

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)Server
	mkdir -p $(OBJ_DIR)User
	mkdir -p $(OBJ_DIR)User/Command
	mkdir -p $(OBJ_DIR)Commands/ConnectionRegistration

run: all
	./ft_irc

clean:
	rm -rf $(OBJ_DIR)
	rm -fr *.dSYM

fclean:
	rm -rf $(NAME) $(OBJ_DIR)
	rm -fr *.dSYM

re: fclean all

.PHONY: all clean fclean re
