//
// Created by Sehoon Jang on 3/29/23.
//
#include "./Conf/Conf.hpp"
#include "./ServerBlock/ServerBlock.hpp"
#include "./LocationBlock/LocationBlock.hpp"
#include "Block/Block.hpp"

#include <iostream>
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string	readFileIntoString(std::string filename)
{
    std::ifstream f(filename);
    std::string str;

    if (!f.good() || !f.is_open())
	{
		std::cout << "Error: Do not stream open of file open." << std::endl;
		return (str);
	}

    if(f)
    {
        std::ostringstream ss;
        ss << f.rdbuf();
        str = ss.str();
    }
    return str;
}

TEST(ConfigTest, Config1Test)
{
    // given
	std::string a = readFileIntoString("../var/conf/test.conf");
	Conf conf(a);
	Block* server_blocks = *conf.getInnerBlock().begin();

	// when
	int	port_result = server_blocks->getPort();
	std::string	root_result = server_blocks->getRoot();
	std::string	addr_result = server_blocks->getAddr();
	std::string	server_name_result = server_blocks->getServerName();
	std::string	index_result = server_blocks->getIndex();
	std::string	default_error_page_result = server_blocks->getDefaultErrorPage();
	int			client_body_size_result = server_blocks->getClientBodySize();
    // then
    EXPECT_EQ(port_result, 80);
    EXPECT_EQ(root_result, "/var/html");
    EXPECT_EQ(addr_result.empty(), true);
    EXPECT_EQ(server_name_result, "example.com");
    EXPECT_EQ(index_result, "index.html");
    EXPECT_EQ(default_error_page_result, "501 502 503 /50x.html");
    EXPECT_EQ(client_body_size_result, 10240);
}

TEST(ConfigTest, Config2Test)
{
    // given
	std::string a = readFileIntoString("../var/conf/default1.conf");
	Conf conf(a);
	Block* server_blocks1 = *conf.getInnerBlock().begin();
	Block* server_blocks2 = *(conf.getInnerBlock().begin() + 1);
	Block* location_blocks3 = *server_blocks1->getInnerBlock().begin();
	Block* location_blocks4 = *server_blocks2->getInnerBlock().begin();
	// when
	
	//server1 
	int			port_result1 = server_blocks1->getPort();
	std::string	root_result1 = server_blocks1->getRoot();
	std::string	addr_result1 = server_blocks1->getAddr();
	std::string	server_name_result1 = server_blocks1->getServerName();
	std::string	index_result1 = server_blocks1->getIndex();
	std::string	default_error_page_result1 = server_blocks1->getDefaultErrorPage();
	int			client_body_size_result1 = server_blocks1->getClientBodySize();
	std::string	upload_path_result1 = server_blocks1->getUploadPath();
	std::vector<std::string>	allow_method_result1 = server_blocks1->getAllowMethod();
	std::vector<std::string>	try_files_result1 = server_blocks1->getTryFiles();
	bool	autoindex_result1 = server_blocks1->getAutoindex();

	//server2
	int			port_result2 = server_blocks2->getPort();
	std::string	root_result2 = server_blocks2->getRoot();
	std::string	addr_result2 = server_blocks2->getAddr();
	std::string	server_name_result2 = server_blocks2->getServerName();
	std::string	index_result2 = server_blocks2->getIndex();
	std::string	default_error_page_result2 = server_blocks2->getDefaultErrorPage();
	int			client_body_size_result2 = server_blocks2->getClientBodySize();
	std::string	upload_path_result2 = server_blocks2->getUploadPath();
	std::vector<std::string>	allow_method_result2 = server_blocks2->getAllowMethod();
	std::vector<std::string>	try_files_result2 = server_blocks2->getTryFiles();
	bool	autoindex_result2 = server_blocks2->getAutoindex();

	//location1
	int			port_result3 = location_blocks3->getPort();
	std::string	root_result3 = location_blocks3->getRoot();
	std::string	addr_result3 = location_blocks3->getAddr();
	std::string	server_name_result3 = location_blocks3->getServerName();
	std::string	index_result3 = location_blocks3->getIndex();
	std::string	default_error_page_result3 = location_blocks3->getDefaultErrorPage();
	int			client_body_size_result3 = location_blocks3->getClientBodySize();
	std::string	upload_path_result3 = location_blocks3->getUploadPath();
	std::vector<std::string>	allow_method_result3 = location_blocks3->getAllowMethod();
	std::vector<std::string>	try_files_result3 = location_blocks3->getTryFiles();
	bool	autoindex_result3 = location_blocks3->getAutoindex();

	//location2
	int			port_result4 = location_blocks4->getPort();
	std::string	root_result4 = location_blocks4->getRoot();
	std::string	addr_result4 = location_blocks4->getAddr();
	std::string	server_name_result4 = location_blocks4->getServerName();
	std::string	index_result4 = location_blocks4->getIndex();
	std::string	default_error_page_result4 = location_blocks4->getDefaultErrorPage();
	int			client_body_size_result4 = location_blocks4->getClientBodySize();
	std::string	upload_path_result4 = location_blocks4->getUploadPath();
	std::vector<std::string>	allow_method_result4 = location_blocks4->getAllowMethod();
	std::vector<std::string>	try_files_result4 = location_blocks4->getTryFiles();
	bool	autoindex_result4 = location_blocks4->getAutoindex();

	// then
	//server1
    EXPECT_EQ(port_result1, 80);
    EXPECT_EQ(root_result1, "/var/html");
    EXPECT_EQ(addr_result1.empty(), true);
    EXPECT_EQ(server_name_result1, "example.com");
    EXPECT_EQ(index_result1, "index.html");
    EXPECT_EQ(default_error_page_result1, "");
    EXPECT_EQ(client_body_size_result1, 10240);
	EXPECT_EQ(upload_path_result1.size(), 0);
	EXPECT_EQ(allow_method_result1.size(), 0);
	EXPECT_EQ(try_files_result1.size(), 0);
	EXPECT_EQ(autoindex_result1, false);
	//server2
	EXPECT_EQ(port_result2, 81);
    EXPECT_EQ(root_result2, "/var/html");
    EXPECT_EQ(addr_result2.empty(), true);
    EXPECT_EQ(server_name_result2, "example.com");
    EXPECT_EQ(index_result2, "index.html");
    EXPECT_EQ(default_error_page_result2, "");
    EXPECT_EQ(client_body_size_result2, 1024);
	EXPECT_EQ(upload_path_result2.size(), 0);
	EXPECT_EQ(allow_method_result2.size(), 0);
	EXPECT_EQ(try_files_result2.size(), 0);
	EXPECT_EQ(autoindex_result2, true);
	//location1
	EXPECT_EQ(port_result3, 80);
    EXPECT_EQ(root_result3, "/var/html");
    EXPECT_EQ(addr_result3.empty(), true);
    EXPECT_EQ(server_name_result3, "example.com");
    EXPECT_EQ(index_result3, "test.html");
    EXPECT_EQ(default_error_page_result3, "");
    EXPECT_EQ(client_body_size_result3, 10240);
	EXPECT_EQ(upload_path_result3.size(), 0);
	EXPECT_EQ(allow_method_result3.size(), 0);
	EXPECT_EQ(*try_files_result3.begin(), "$uri $uri/ = 404");
	EXPECT_EQ(autoindex_result3, false);
	//location2
	EXPECT_EQ(port_result4, 81);
    EXPECT_EQ(root_result4, "/var/html");
    EXPECT_EQ(addr_result4.empty(), true);
    EXPECT_EQ(server_name_result4, "example.com");
    EXPECT_EQ(index_result4, "index.html");
    EXPECT_EQ(default_error_page_result4, "");
    EXPECT_EQ(client_body_size_result4, 1024);
	EXPECT_EQ(upload_path_result4.size(), 0);
	EXPECT_EQ(allow_method_result4.size(), 3);
	EXPECT_EQ(*try_files_result4.begin(), "$uri $uri/ = 404");
	EXPECT_EQ(autoindex_result4, true);

}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
