#include "HttpResponseMessage.hpp"
#include "HttpRequestMessage.hpp"
#include "gtest/gtest.h"

TEST(HttpMessageUnitTest, HttpRequestMessageTest)
{
    // given
    std::string str =   "POST / HTTP/1.1\r\n"
                        "Host: 127.0.0.1:500\r\n"
                        "Connection: keep-alive\r\n"
                        "Accept: */*\r\n"
                        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/16.3 Safari/605.1.15\r\n"
                        "Accept-Language: ko-KR,ko;q=0.9\r\n"
                        "Referer: http://127.0.0.1:500/\r\n"
                        "Accept-Encoding: gzip, deflate\r\n"
                        "\r\n"
                        "test message body";
    std::string start_line = "POST /favicon.ico HTTP/1.1";
    std::string message_body = "test message body";

    // when
    HttpRequestMessage *http_message = new HttpRequestMessage(str);

    // then
    EXPECT_EQ(http_message->getStartLine(), start_line);
    EXPECT_EQ(http_message->getMessageBody(), message_body);
    delete http_message;
}

TEST(HttpMessageUnitTest, HttpResponseMessageTest)
{
    // given
    std::string str =   "HTTP/1.1 200 OK\r\n"
                        "Host: 127.0.0.1:500\r\n"
                        "Connection: keep-alive\r\n"
                        "Accept: */*\r\n"
                        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/16.3 Safari/605.1.15\r\n"
                        "Accept-Language: ko-KR,ko;q=0.9\r\n"
                        "Referer: http://127.0.0.1:500/\r\n"
                        "Accept-Encoding: gzip, deflate\r\n"
                        "\r\n"
                        "test message body";
    std::string start_line = "HTTP/1.1 200 OK";
    std::string message_body = "test message body";

    // when
    HttpResponseMessage *http_message = new HttpResponseMessage(str);

    // then
    EXPECT_EQ(http_message->getStartLine(), start_line);
    EXPECT_EQ(http_message->getMessageBody(), message_body);
    delete http_message;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}