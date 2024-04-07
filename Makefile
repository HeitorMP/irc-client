# Folders and Names
NAME		:= simple-irc
SRCDIR		:= srcs
INCLUDES	:= includes
OBJSDIR		:= build

SRCS		:= main.cpp \
			   Classes/Channel.cpp \
			   Classes/User.cpp \
			   Classes/Command.cpp \
			   Classes/Window.cpp \
			   Commands/cmd-channel.cpp

OBJS		:= ${SRCS:%.cpp=$(OBJSDIR)/%.o}

CXX			:= g++
CXXFLAGS	:= -g #-Wall -Wextra -Werror -std=c++11 -g
GRAPHIC		:= -lncurses
ASIO		:= -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -o $(NAME) $(OBJS) $(GRAPHIC) $(ASIO)

$(OBJS): ${OBJSDIR}/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	rm -rf build

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean
