CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g

NAME = webserv

SRCS =	webserve/main.cpp \
		webserve/Server/Server.cpp \
		webserve/ServerRun/ServerRun.cpp \
		webserve/ServerParser/ServerParser.cpp \
		webserve/ServerHandler/ServerHandler.cpp \
		webserve/WebServer/WebServer.cpp \
		webserve/HttpMessage/HttpMessage.cpp \
		webserve/HttpMessage/HttpRequestMessage.cpp \
		webserve/HttpMessage/HttpResponseMessage.cpp \
		webserve/lib/ft/readFileIntoString.cpp \
		webserve/lib/ft/splitBlockString.cpp \
		webserve/lib/ft/splitString.cpp

OBJS = $(SRCS:.cpp=.o)
HEAD =  -I./webserve/Server \
		-I./webserve/ServerParser \
		-I./webserve/ServerRun \
		-I./webserve/ServerHandler \
		-I./WebServer \
		-I./webserve/HttpMessage \
		-I./webserve/lib/ft

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
