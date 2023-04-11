CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 

NAME = webserv

SRCS =	main.cpp \
		Server/Server.cpp \
		ServerRun/ServerRun.cpp \
		ServerParser/ServerParser.cpp \
		WebServer/WebServer.cpp \
		lib/ft/splitBlockString.cpp \
		lib/ft/splitString.cpp

OBJS = $(SRCS:.cpp=.o)
HEAD = ./Server -I./ServerParser -I./ServerRun -I./WebServer -I./lib/ft

all: $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: 
	$(MAKE) fclean 
	$(MAKE) all

.PHONY = all clean fclean re
