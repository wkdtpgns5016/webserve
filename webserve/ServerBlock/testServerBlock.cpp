#include "ServerBlock.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string	read_file_into_string(std::string filename)
{
    std::ifstream f(filename);
    std::string str;

    if(f)
    {
        std::ostringstream ss;
        ss << f.rdbuf();
        str = ss.str();
    }
    return str;
}

TEST(ServerBlockTest, parsePortTest)
{
	// given
	std::string a = read_file_into_string("../var/conf/test1.conf");
	ServerBlock sv_block(a);

	// when
	int	answer1 = sv_block.getPort();
	std::string	answer2 = sv_block.getRoot();
	std::string	answer3 = sv_block.getServerName();
	std::string	answer4 = sv_block.getIndex();
	std::string	answer5 = sv_block.getDefaultErrorPaget();
	int	answer6 = sv_block.getClientBodySize();
	std::string answer7 = sv_block.getAddr();


    // then
    EXPECT_EQ(answer1, 80);
    EXPECT_EQ(answer2, "/var/html");
    EXPECT_EQ(answer3, "example.com");
    EXPECT_EQ(answer4, "index.html");
    EXPECT_EQ(answer5, "501 502 503 /50x.html");
    EXPECT_EQ(answer6, 10240);
    EXPECT_EQ(answer7.empty(), true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
