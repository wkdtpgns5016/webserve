cmake_minimum_required(VERSION 3.24)
project(webserve)

set(CMAKE_CXX_STANDARD 17)

# 객체 빌드
add_library(obj SHARED webserve/TestExample/TestExample.cpp webserve/TestExample/TestExample.hpp)
add_library(libft webserve/lib/ft/ft.hpp webserve/lib/ft/splitBlockString.cpp webserve/lib/ft/splitString.cpp )
add_library(sv_parser webserve/ServerParser/ServerParser.hpp webserve/ServerParser/ServerParser.cpp)
add_library(location_parser webserve/LocationParser/LocationParser.hpp webserve/LocationParser/LocationParser.cpp)
add_library(http_message webserve/HttpMessage/HttpMessage.cpp
                        webserve/HttpMessage/HttpMessage.hpp
                        webserve/HttpMessage/HttpRequestMessage.cpp
                        webserve/HttpMessage/HttpRequestMessage.hpp
                        webserve/HttpMessage/HttpResponseMessage.cpp
                        webserve/HttpMessage/HttpResponseMessage.hpp)

## 실행 프로그램 빌드
#include_directories(obj)
#add_executable(webserve webserve/main.cpp)
#target_link_libraries(webserve obj)

# gtest 빌드
set(gtest_SRC_DIR tests/googletest-1.13.0)
add_subdirectory(${gtest_SRC_DIR})

# TestExampleUnitTest 빌드
include_directories(obj)
include_directories(${gtest_SRC_DIR}/googletest/include)
add_executable(TestExampleUnitTest webserve/TestExample/TestExample.test.cpp)
target_link_libraries(TestExampleUnitTest gtest gtest_main)
target_link_libraries(TestExampleUnitTest obj)

# ft 라이브러리 단위테스트 빌드
include_directories(libft)
add_executable(libftUnitTest webserve/lib/ft/ft.test.cpp)
target_link_libraries(libftUnitTest gtest gtest_main)
target_link_libraries(libftUnitTest libft)

## server parser 라이브러리 단위테스트 빌드
include_directories(libft)
include_directories(${gtest_SRC_DIR}/googletest/include)
include_directories(sv_parser)
add_executable(ServerParserTest webserve/ServerParser/testServerParser.cpp)
target_link_libraries(ServerParserTest gtest gtest_main)
target_link_libraries(ServerParserTest libft)
target_link_libraries(ServerParserTest sv_parser)

# location parser 라이브러리 단위테스트 빌드
include_directories(libft)
include_directories(${gtest_SRC_DIR}/googletest/include)
include_directories(location_parser)
add_executable(LocationParserTest webserve/LocationParser/LocationParser.test.cpp)
target_link_libraries(LocationParserTest gtest gtest_main)
target_link_libraries(LocationParserTest libft)
target_link_libraries(LocationParserTest location_parser)

# http message 단위테스트 빌드
include_directories(http_message)
add_executable(HttpMessageUnitTest webserve/HttpMessage/HttpMessage.test.cpp)
target_link_libraries(HttpMessageUnitTest gtest gtest_main)
target_link_libraries(HttpMessageUnitTest http_message)
target_link_libraries(HttpMessageUnitTest libft)
