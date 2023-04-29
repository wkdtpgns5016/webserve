#include "LocationBlock.hpp"
#include "gtest/gtest.h"
#include <string>

TEST(LocationBlockTest, LocationBlockUnitTest)
{
	// given
	std::string a = "location / {\n"
    "    root /var/html;\n"
    "    index index.html;\n"
    "    autoindex on;\n"
    "    upload_path /var/download;\n"
    "    allow_method GET POST DELETE;\n"
    "    try_files $uri $uri/ 404;\n"
    "}\n";

	// when
    LocationBlock l_block(a);
    std::string url = l_block.getUrl();
    std::string root = l_block.getRoot();
    std::string upload_path = l_block.getUploadPath();
    bool auto_index = l_block.getAutoIndex();

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
