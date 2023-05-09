#include "CommonLogFormat.hpp"
#include "gtest/gtest.h"

TEST(LogFormatUnitTest, CommonLogFormatTest)
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
    
    std::string str2 =   "HTTP/1.1 200 OK\r\n"
                        "Host: 127.0.0.1:500\r\n"
                        "Connection: keep-alive\r\n"
                        "Accept: */*\r\n"
                        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/16.3 Safari/605.1.15\r\n"
                        "Accept-Language: ko-KR,ko;q=0.9\r\n"
                        "Referer: http://127.0.0.1:500/\r\n"
                        "Accept-Encoding: gzip, deflate\r\n"
                        "\r\n"
                        "test message body";
    HttpRequestMessage reqeust_message = HttpRequestMessage(str);
    HttpResponseMessage response_message = HttpResponseMessage(str2);


    //when
    CommonLogFormat log = CommonLogFormat(reqeust_message, response_message);

    // then
    EXPECT_EQ(log.getRequestLine().getString(), "POST / HTTP/1.1");
    EXPECT_EQ(log.getStatusCode(), 200);
    EXPECT_EQ(log.getResponseSize(), "17");
    log.wirteLogMessage(1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}