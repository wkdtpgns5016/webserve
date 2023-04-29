#include "./Block.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

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

TEST(BlockTest, jumpTrashTest)
{
	// given
	std::string a = "    listen 80;\n"
                    "    root /var/html;\n";
	std::string b = "    listen 80;";
	Block	block;

	// when
	
	size_t	answer1 = block.jumpTrash(a, 0);
	size_t	answer2 = block.jumpTrash(a, a.find(';') + 1);
	std::pair<std::string, std::string> answer3 = block.divideElementIdAndValue(b, 0);
	// then
    EXPECT_EQ(a[answer1], 'l');
    EXPECT_EQ(a[answer2], 'r');
    EXPECT_EQ(answer3.first, "listen");
    EXPECT_EQ(answer3.second, "80");

}

std::string	makeString(std::pair<std::string::iterator, std::string::iterator> arg)
{
	std::string ret;

	for (; arg.first != arg.second; arg.first++)
		ret += *arg.first;
	return ret;
}

//TEST(BlockTest, extractTest)
//{
//	std::string a = read_file_into_string("../var/conf/test.conf");
//	
//	Block Block;
//	std::pair<std::string::iterator, std::string::iterator> answer1 = Block.extractBlockID(a.begin(), a.end());
//	std::pair<std::string::iterator, std::string::iterator> answer2 = Block.extractElement(answer1.second, a.end());
//	std::pair<std::string::iterator, std::string::iterator> answer3 = Block.extractBraces(answer1.second, a.end());
//
//	std::string str1 =	"server\n";
//	std::string str2 = "{\n	listen 80;";
//	std::string	str3 =	str2 + "\n"
//						"	server_name example.com;\n"
//						"	root /var/html;\n"
//						"	location {\n"
//						"	\n"
//						"	}\n"
//						"	index index.html;\n"
//						"	client_max_body_size 10240;\n"
//						"	error_page 501 502 503 /50x.html;\n"
//						"}";
//
//	
//	EXPECT_EQ(makeString(answer1), str1);
//	EXPECT_EQ(makeString(answer2), str2);
//	EXPECT_EQ(makeString(answer3), str3);
//
//
//}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
