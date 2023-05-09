#include <iostream>
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "ServerHandler.hpp"

TEST(ServerHandlerTest, ServerHandlerUnitTest)
{
    // given
	std::string a = ft::readFileIntoString("../var/conf/test.conf");
	Conf conf(a);
	Block* blocks = *conf.getInnerBlock().begin();
    ServerBlock *server_blocks = (dynamic_cast<ServerBlock *>(blocks));
    std::string http_message =   "GET /aaaaaa.a HTTP/1.1\r\n"
                        "Host: 127.0.0.1:500\r\n"
                        "Connection: keep-alive\r\n"
                        "Accept: */*\r\n"
                        "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/16.3 Safari/605.1.15\r\n"
                        "Accept-Language: ko-KR,ko;q=0.9\r\n"
                        "Referer: http://127.0.0.1:500/\r\n"
                        "Accept-Encoding: gzip, deflate\r\n"
                        "\r\n"
                        "test message body";

	// when
    ServerHandler handler(server_blocks, http_message);
    HttpResponseMessage response = handler.requestHandler();

    // then
    EXPECT_EQ(response.getStartLine().getString(), "HTTP/1.1 404 Not Found");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
