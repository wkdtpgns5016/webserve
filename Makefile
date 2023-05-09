CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g

NAME = webserv

SRCS =	webserve/main.cpp \
		webserve/WebServer/WebServer.cpp \
		webserve/Server/Server.cpp \
		webserve/Configuration/Conf/Conf.cpp \
		webserve/Configuration/Block/Block.cpp \
		webserve/Configuration/LocationBlock/LocationBlock.cpp \
		webserve/Configuration/ServerBlock/ServerBlock.cpp \
		webserve/ServerHandler/ServerHandler.cpp \
		webserve/HttpMessage/HttpMessage.cpp \
		webserve/HttpMessage/HttpRequestMessage.cpp \
		webserve/HttpMessage/HttpResponseMessage.cpp \
		webserve/lib/ft/readFileIntoString.cpp \
		webserve/lib/ft/splitBlockString.cpp \
		webserve/lib/ft/splitString.cpp \
		webserve/lib/ft/itos.cpp \
		webserve/lib/ft/stoi.cpp  \
		webserve/CommonLogFormat/CommonLogFormat.cpp
		
		
OBJS = $(SRCS:.cpp=.o)
HEAD =  -I./webserve/Server \
		-I./webserve/WebServer \
		-I./webserve/Configuration/Conf \
		-I./webserve/Configuration/Block \
		-I./webserve/Configuration/ServerBlock \
		-I./webserve/Configuration/LocationBlock \
		-I./webserve/ServerHandler \
		-I./webserve/HttpMessage \
		-I./webserve/lib/ft \
		-I./webserve/CommonLogFormat

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
