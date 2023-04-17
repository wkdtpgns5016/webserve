#include "LocationParser.hpp"
#include "gtest/gtest.h"
#include <string>

TEST(LocationParserTest, LocationParserUnitTest)
{
	// given
	std::string a = "location / {"
    "    root /var/html;"
    "    index index.html;"
    "    autoindex on;"
    "    upload_path /var/download;"
    "    allow_method GET POST DELETE;"
    "    try_files $uri $uri/ 404;"
    "}";

	// when
    LocationParser l_parser(a);
    std::string url = l_parser.getUrl();
    std::string root = l_parser.getRoot();
    std::string upload_path = l_parser.getUploadPath();
    bool auto_index = l_parser.getAutoIndex();

    // then
    EXPECT_EQ(url, "/");
    EXPECT_EQ(root, "/var/html");
    EXPECT_EQ(auto_index, 1);
    EXPECT_EQ(upload_path, "/var/download");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
