#include "ft.hpp"
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

TEST(libftUnitTest, splitStirngTest)
{
    // given
    std::string a = "1, 2, 3, 4";
    std::string b = "1, 2,, 3, 4";

    // when
    std::vector<std::string> result1 = ft::splitString(a, ", ");
    std::vector<std::string> result2 = ft::splitString(a, "2");
    std::vector<std::string> result3 = ft::splitString(b, ",");

    // then
    EXPECT_EQ(result1.size(), 4);
    EXPECT_EQ(result1[2].compare("3"), 0);
    EXPECT_EQ(result2.size(), 2);
    EXPECT_EQ(result2[1].compare(", 3, 4"), 0);
    EXPECT_EQ(result3.size(), 4);
    EXPECT_EQ(result3[2].compare(" 3"), 0);
}

TEST(libftUnitTest, splitBlockStirngTest)
{
    // given
    std::string a = read_file_into_string("../var/conf/default.conf");
    std::string b = "    listen 80;\n"
                    "    listen [::]:80;\n"
                    "\n"
                    "    server_name example.com;\n"
                    "    \n"
                    "    root /var/html;\n"
                    "    \n"
                    "    index index.html;\n"
                    "\n"
                    "    client_max_body_size 10M;\n"
                    "\n"
                    "    location / {\n"
                    "        index test.html;\n"
                    "        try_files $uri $uri/ = 404;\n"
                    "    }\n";
    std::string answer1 = "server {\n"
                         "    listen 80;\n"
                         "    listen [::]:80;\n"
                         "\n"
                         "    server_name example.com;\n"
                         "    \n"
                         "    root /var/html;\n"
                         "    \n"
                         "    index index.html;\n"
                         "\n"
                         "    client_max_body_size 10M;\n"
                         "\n"
                         "    location / {\n"
                         "        index test.html;\n"
                         "        try_files $uri $uri/ = 404;\n"
                         "    }\n"
                         "}\n";
    std::string answer2 = "    location / {\n"
                          "        index test.html;\n"
                          "        try_files $uri $uri/ = 404;\n"
                          "    }\n";

    // when
    std::vector<std::string> result1 = ft::splitBlockString(a);
    std::vector<std::string> result2 = ft::splitBlockString(b);

    // then
    EXPECT_EQ(result1.size(), 2);
    EXPECT_EQ(result1[0], answer1);
    EXPECT_EQ(result2[0], answer2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}