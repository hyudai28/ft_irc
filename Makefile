NAME = ft_irc

# Config
# ****************************************************************************

CXX = g++
INCLUDE = -I src/Server/ -I src/User/
CXXFLAGS =
CXXFLAGS += $(INCLUDE)

# Source files
# ****************************************************************************

SRC_DIR =		src/
SRC_FILES	=	Server/Server.cpp \
			main.cpp
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

clean:
	rm -rf $(OBJ_DIR)
	rm -fr *.dSYM

fclean:
	rm -rf $(NAME) $(OBJ_DIR)
	rm -fr *.dSYM

re: fclean all
.PHONY: all clean fclean re
