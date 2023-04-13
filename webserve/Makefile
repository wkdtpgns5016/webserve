CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g

NAME = webserv

SRCS =	main.cpp \
		Server/Server.cpp \
		ServerRun/ServerRun.cpp \
		ServerParser/ServerParser.cpp \
		ServerHandler/ServerHandler.cpp \
		WebServer/WebServer.cpp \
		HttpMessage/HttpMessage.cpp \
		HttpMessage/HttpRequestMessage.cpp \
		HttpMessage/HttpResponseMessage.cpp \
		lib/ft/splitBlockString.cpp \
		lib/ft/splitString.cpp

OBJS = $(SRCS:.cpp=.o)
HEAD = ./Server -I./ServerParser -I./ServerRun -I./ServerHandler -I./WebServer -I./HttpMessage -I./lib/ft

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
