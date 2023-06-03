cmake_minimum_required(VERSION 3.24)
project(webserve)

set(CMAKE_CXX_STANDARD 17)
ADD_COMPILE_OPTIONS( -g3)
# 객체 빌드
#add_library(obj SHARED webserve/TestExample/TestExample.cpp webserve/TestExample/TestExample.hpp)
add_library(libft webserve/lib/ft/ft.hpp 
                  webserve/lib/ft/splitBlockString.cpp 
                  webserve/lib/ft/readFileIntoString.cpp 
                  webserve/lib/ft/splitString.cpp 
                  webserve/lib/ft/itos.cpp 
		          webserve/lib/ft/stoul.cpp
		          webserve/lib/ft/stoi.cpp )
add_library(Configuration	webserve/Configuration/Parser/parseTryFiles.cpp 
							webserve/Configuration/Parser/parseAllowMethod.cpp 
							webserve/Configuration/Parser/parseListen.cpp  
							webserve/Configuration/Parser/parseErrorPage.cpp 
							webserve/Configuration/Parser/parseClientMaxBodySize.cpp 
							webserve/Configuration/Parser/SimpleException.cpp  
							webserve/Configuration/Parser/Parser.hpp 
							webserve/Configuration/Parser/Parser.cpp 
							webserve/Configuration/Block/Block.hpp 
							webserve/Configuration/Block/Block.cpp 
							webserve/Configuration/Block/BlockException.cpp
							webserve/Configuration/LocationBlock/LocationBlock.hpp 
							webserve/Configuration/LocationBlock/LocationBlock.cpp 
							webserve/Configuration/Conf/Conf.hpp 
							webserve/Configuration/Conf/Conf.cpp 
							webserve/Configuration/Scripter/Scripter.cpp
							webserve/Configuration/Scripter/Scripter.hpp
							webserve/Configuration/ServerBlock/ServerBlock.hpp
							webserve/Configuration/ServerBlock/ServerBlock.cpp)

add_library(http_message webserve/HttpMessage/HttpMessage.cpp
                        webserve/HttpMessage/HttpMessage.hpp
                        webserve/HttpMessage/HttpRequestMessage.cpp
                        webserve/HttpMessage/HttpRequestMessage.hpp
                        webserve/HttpMessage/HttpResponseMessage.cpp
                        webserve/HttpMessage/HttpResponseMessage.hpp)
					#add_library(log webserve/CommonLogFormat/CommonLogFormat.hpp webserve/CommonLogFormat/CommonLogFormat.cpp)
#add_library(handler webserve/ServerHandler/ServerHandler.hpp webserve/ServerHandler/ServerHandler.cpp)


## 실행 프로그램 빌드
#include_directories(obj)
#add_executable(webserve webserve/main.cpp)
#target_link_libraries(webserve obj)

# gtest 빌드
set(gtest_SRC_DIR tests/googletest-1.13.0)
add_subdirectory(${gtest_SRC_DIR})

# TestExampleUnitTest 빌드
#include_directories(obj)
#include_directories(${gtest_SRC_DIR}/googletest/include)
#add_executable(TestExampleUnitTest webserve/TestExample/TestExample.test.cpp)
#target_link_libraries(TestExampleUnitTest gtest gtest_main)
#target_link_libraries(TestExampleUnitTest obj)

# ft 라이브러리 단위테스트 빌드
include_directories(libft)
add_executable(libftUnitTest webserve/lib/ft/ft.test.cpp)
target_link_libraries(libftUnitTest gtest gtest_main)
target_link_libraries(libftUnitTest libft)

## server parser 라이브러리 단위테스트 빌드
# include_directories(libft)
# include_directories(${gtest_SRC_DIR}/googletest/include)
# include_directories(sv_parser)
# add_executable(ServerParserTest webserve/ServerParser/testServerParser.cpp)
# target_link_libraries(ServerParserTest gtest gtest_main)
# target_link_libraries(ServerParserTest libft)
# target_link_libraries(ServerParserTest sv_parser)

# location parser 라이브러리 단위테스트 빌드
# include_directories(libft)
# include_directories(${gtest_SRC_DIR}/googletest/include)
# include_directories(location_parser)
# add_executable(LocationParserTest webserve/LocationParser/LocationParser.test.cpp)
# target_link_libraries(LocationParserTest gtest gtest_main)
# target_link_libraries(LocationParserTest libft)
# target_link_libraries(LocationParserTest location_parser)

# http message 단위테스트 빌드
#include_directories(http_message)
#add_executable(HttpMessageUnitTest webserve/HttpMessage/HttpMessage.test.cpp)
#target_link_libraries(HttpMessageUnitTest gtest gtest_main)
#target_link_libraries(HttpMessageUnitTest http_message)
#target_link_libraries(HttpMessageUnitTest libft)


# #paresr 단위테스트 빌드
# include_directories(libft)
# include_directories(${gtest_SRC_DIR}/googletest/include)
# include_directories(parser)
# add_executable(ParserTest webserve/Parser/Parser.test.cpp)
# target_link_libraries(ParserTest gtest gtest_main)
# target_link_libraries(ParserTest libft)
# target_link_libraries(ParserTest parser)


# log format 단위테스트 빌드
#include_directories(libft)
#include_directories(${gtest_SRC_DIR}/googletest/include)
#add_executable(LogFormatUnitTest webserve/CommonLogFormat/CommonLogFormat.test.cpp)
#target_link_libraries(LogFormatUnitTest gtest gtest_main)
#target_link_libraries(LogFormatUnitTest libft)
#target_link_libraries(LogFormatUnitTest http_message)
#target_link_libraries(LogFormatUnitTest log)

#conf 단위테스트 빌드
include_directories(libft)
include_directories(${gtest_SRC_DIR}/googletest/include)
include_directories(Configuration)
add_executable(ConfigTest webserve/Configuration/config.test.cpp)
target_link_libraries(ConfigTest gtest gtest_main)
target_link_libraries(ConfigTest libft)
target_link_libraries(ConfigTest Configuration)

# server handler 단위 테스트 빌드
#include_directories(libft)
#include_directories(${gtest_SRC_DIR}/googletest/include)
#add_executable(ServerHandlerTest webserve/ServerHandler/ServerHandler.test.cpp)
#target_link_libraries(ServerHandlerTest gtest gtest_main)
#target_link_libraries(ServerHandlerTest libft)
#target_link_libraries(ServerHandlerTest http_message)
#target_link_libraries(ServerHandlerTest log)
#target_link_libraries(ServerHandlerTest handler)
#target_link_libraries(ServerHandlerTest conf)
#target_link_libraries(ServerHandlerTest block)
#target_link_libraries(ServerHandlerTest server_block)
#target_link_libraries(ServerHandlerTest location_block)
