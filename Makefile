CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 -g

NAME = webserv

SRCS =	webserve/main.cpp \
		webserve/WebServer/WebServer.cpp \
		webserve/Server/Server.cpp \
		webserve/Configuration/Conf/Conf.cpp \
		webserve/Configuration/ConfigDto/ConfigDto.cpp \
		webserve/Configuration/Block/Block.cpp \
		webserve/Configuration/Block/BlockException.cpp \
		webserve/Configuration/LocationBlock/LocationBlock.cpp \
		webserve/Configuration/ServerBlock/ServerBlock.cpp \
		webserve/Configuration/Parser/Parser.cpp \
		webserve/Configuration/Parser/parseListen.cpp \
		webserve/Configuration/Parser/parseAllowMethod.cpp \
		webserve/Configuration/Parser/parseErrorPage.cpp \
		webserve/Configuration/Parser/parseClientMaxBodySize.cpp \
		webserve/Configuration/Parser/parseTryFiles.cpp \
		webserve/Configuration/Parser/parseCgiConfig.cpp \
		webserve/Configuration/Parser/parseReturnValue.cpp \
		webserve/Configuration/Parser/SimpleException.cpp \
		webserve/Configuration/Scripter/Scripter.cpp \
		webserve/RequestHandler/ServerHandler/ServerHandler.cpp \
		webserve/RequestHandler/GetHandler/GetHandler.cpp \
		webserve/RequestHandler/DeleteHandler/DeleteHandler.cpp \
		webserve/RequestHandler/PostHandler/PostHandler.cpp \
		webserve/RequestHandler/PutHandler/PutHandler.cpp \
		webserve/ServerController/ServerController.cpp \
		webserve/Connection/Connection.cpp \
		webserve/HttpMessage/HttpMessage.cpp \
		webserve/HttpMessage/HttpRequestMessage.cpp \
		webserve/HttpMessage/RequestMessageParser.cpp \
		webserve/HttpMessage/HttpResponseMessage.cpp \
		webserve/lib/ft/readFileIntoString.cpp \
		webserve/lib/ft/splitBlockString.cpp \
		webserve/lib/ft/splitString.cpp \
		webserve/lib/ft/itos.cpp \
		webserve/lib/ft/stoi.cpp  \
		webserve/lib/ft/stoul.cpp  \
		webserve/lib/ft/getTime.cpp  \
		webserve/lib/ft/convertHex.cpp  \
		webserve/lib/ft/isNumbers.cpp  \
		webserve/Log/CommonLogFormat/CommonLogFormat.cpp \
		webserve/Log/Logger/Logger.cpp \
		webserve/CGI/CGI.cpp \
		webserve/Buffer/Buffer.cpp
		
		
OBJS = $(SRCS:.cpp=.o)
HEAD =  -I./webserve/Server \
		-I./webserve/WebServer \
		-I./webserve/Configuration/Conf \
		-I./webserve/Configuration/ConfigDto \
		-I./webserve/Configuration/Block \
		-I./webserve/Configuration/ServerBlock \
		-I./webserve/Configuration/LocationBlock \
		-I./webserve/RequestHandler/ServerHandler \
		-I./webserve/RequestHandler/GetHandler \
		-I./webserve/RequestHandler/PostHandler \
		-I./webserve/RequestHandler/PutHandler \
		-I./webserve/RequestHandler/DeleteHandler \
		-I./webserve/ServerController/ \
		-I./webserve/Connection \
		-I./webserve/HttpMessage \
		-I./webserve/lib/ft \
		-I./webserve/Log/CommonLogFormat \
		-I./webserve/Log/Logger \
		-I./webserve/CGI \
		-I./webserve/Buffer

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
