#include "./Parser.hpp"
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

TEST(ParserTest, jumpTrashTest)
{
	// given
	std::string a = "    listen 80;\n"
                    "    root /var/html;\n"
;
	Parser	parser;

	// when
	
	std::string::iterator	answer1 = parser.jumpTrash(a.begin());
	std::string::iterator	answer2 = parser.jumpTrash(a.begin() + a.find(';') + 1);

	// then
    EXPECT_EQ(*answer1, 'l');
    EXPECT_EQ(*answer2, 'r');
}

std::string	makeString(std::pair<std::string::iterator, std::string::iterator> arg)
{
	std::string ret;

	for (; arg.first != arg.second; arg.first++)
		ret += *arg.first;
	return ret;
}

TEST(ParserTest, extractTest)
{
	std::string a = read_file_into_string("../var/conf/test.conf");
	
	Parser parser;
	std::pair<std::string::iterator, std::string::iterator> answer1 = parser.extractBlockID(a.begin(), a.end());
	std::pair<std::string::iterator, std::string::iterator> answer2 = parser.extractElement(answer1.second, a.end());
	std::pair<std::string::iterator, std::string::iterator> answer3 = parser.extractBraces(answer1.second, a.end());

	std::string str1 =	"server\n";
	std::string str2 = "{\n	listen 80;";
	std::string	str3 =	str2 + "\n"
						"	server_name example.com;\n"
						"	root /var/html;\n"
						"	location {\n"
						"	\n"
						"	}\n"
						"	index index.html;\n"
						"	client_max_body_size 10240;\n"
						"	error_page 501 502 503 /50x.html;\n"
						"}";

	
	EXPECT_EQ(makeString(answer1), str1);
	EXPECT_EQ(makeString(answer2), str2);
	EXPECT_EQ(makeString(answer3), str3);


}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
