#include "ServerParser.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

TEST(ServerParserTest, parsePortTest)
{
	// given
	std::string a = read_file_into_string("../var/conf/test.conf");
	ServerParser sv_parser(a);

	// when
	int	answer1 = sv_parser.getPort();

    // then
    EXPECT_EQ(answer1, 80);
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
