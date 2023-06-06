//
// Created by Sehoon Jang on 3/29/23.
//
#include "./Conf/Conf.hpp"
#include "./ServerBlock/ServerBlock.hpp"
#include "./LocationBlock/LocationBlock.hpp"
#include "Block/Block.hpp"

#include <arpa/inet.h>
#include <iostream>
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

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
	unsigned int addr_result = server_blocks->getAddr();
	std::string	server_name_result = server_blocks->getServerName();
	std::string	index_result = server_blocks->getIndex();
	std::string	default_error_page_result = server_blocks->getDefaultErrorPage();
	int			client_body_size_result = server_blocks->getClientMaxBodySize();
    // then
    EXPECT_EQ(port_result, 80);
    EXPECT_EQ(root_result, "/var/html");
    //EXPECT_EQ(addr_result, 0);
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
	ServerBlock* server_blocks1 = static_cast<ServerBlock*>(*conf.getInnerBlock().begin());
	ServerBlock* server_blocks2 = static_cast<ServerBlock*>(conf.getInnerBlock().back());
	LocationBlock* location_blocks3 = static_cast<LocationBlock*>(*server_blocks1->getInnerBlock().begin());
	LocationBlock* location_blocks4 = static_cast<LocationBlock*>(*server_blocks2->getInnerBlock().begin());
	// when
	
	//server1 
	int			port_result1 = server_blocks1->getPort();
	std::string	root_result1 = server_blocks1->getRoot();
	unsigned int	addr_result1 = server_blocks1->getAddr();
	std::string	server_name_result1 = server_blocks1->getServerName();
	std::string	index_result1 = server_blocks1->getIndex();
	std::string	default_error_page_result1 = server_blocks1->getDefaultErrorPage();
	int			client_body_size_result1 = server_blocks1->getClientMaxBodySize();
	std::string	upload_path_result1 = server_blocks1->getUploadPath();
	std::vector<std::string>	allow_method_result1 = server_blocks1->getAllowMethod();
	bool	autoindex_result1 = server_blocks1->getAutoindex();
	std::map<std::string, std::string>	cgi_config_result1 = server_blocks1->getCgiConfigs();
	//server2
	int			port_result2 = server_blocks2->getPort();
	std::string	root_result2 = server_blocks2->getRoot();
	unsigned int	addr_result2 = server_blocks2->getAddr();
	std::string	server_name_result2 = server_blocks2->getServerName();
	std::string	index_result2 = server_blocks2->getIndex();
	std::string	default_error_page_result2 = server_blocks2->getDefaultErrorPage();
	int			client_body_size_result2 = server_blocks2->getClientMaxBodySize();
	std::string	upload_path_result2 = server_blocks2->getUploadPath();
	std::vector<std::string>	allow_method_result2 = server_blocks2->getAllowMethod();
	bool	autoindex_result2 = server_blocks2->getAutoindex();
	std::map<std::string, std::string>	cgi_config_result2 = server_blocks2->getCgiConfigs();


	//location1
	int			port_result3 = location_blocks3->getPort();
	std::string	root_result3 = location_blocks3->getRoot();
	unsigned int addr_result3 = location_blocks3->getAddr();
	std::string	server_name_result3 = location_blocks3->getServerName();
	std::string	index_result3 = location_blocks3->getIndex();
	std::string	default_error_page_result3 = location_blocks3->getDefaultErrorPage();
	int			client_body_size_result3 = location_blocks3->getClientMaxBodySize();
	std::string	upload_path_result3 = location_blocks3->getUploadPath();
	std::vector<std::string>	allow_method_result3 = location_blocks3->getAllowMethod();
	bool	autoindex_result3 = location_blocks3->getAutoindex();
	std::string	url_result3 = location_blocks3->getUrl();
	std::map<std::string, std::string>	cgi_config_result3 = location_blocks3->getCgiConfigs();
	std::pair<int, std::string>	return_value3 = location_blocks3->getReturnValue();

	//location2
	int			port_result4 = location_blocks4->getPort();
	std::string	root_result4 = location_blocks4->getRoot();
	unsigned int addr_result4 = location_blocks4->getAddr();
	std::string	server_name_result4 = location_blocks4->getServerName();
	std::string	index_result4 = location_blocks4->getIndex();
	std::string	default_error_page_result4 = location_blocks4->getDefaultErrorPage();
	int			client_body_size_result4 = location_blocks4->getClientMaxBodySize();
	std::string	upload_path_result4 = location_blocks4->getUploadPath();
	std::vector<std::string>	allow_method_result4 = location_blocks4->getAllowMethod();
	bool	autoindex_result4 = location_blocks4->getAutoindex();
	std::string	url_result4 = location_blocks4->getUrl();
	std::map<std::string, std::string>	cgi_config_result4 = location_blocks4->getCgiConfigs();
	// then
	//server1
    EXPECT_EQ(port_result1, 80);
    EXPECT_EQ(root_result1, "/var/html");
    EXPECT_EQ(addr_result1, inet_addr("127.0.0.1"));
    EXPECT_EQ(server_name_result1, "example.com");
    EXPECT_EQ(index_result1, "index.html");
    EXPECT_EQ(default_error_page_result1, "");
    EXPECT_EQ(client_body_size_result1, 10240);
	EXPECT_EQ(upload_path_result1.size(), 0);
	EXPECT_EQ(allow_method_result1.size(), 0);
	EXPECT_EQ(autoindex_result1, false);
	EXPECT_EQ(cgi_config_result1["bla"], "cgi_tester");
	//server2
	EXPECT_EQ(port_result2, 81);
    EXPECT_EQ(root_result2, "/var/html");
    EXPECT_EQ(addr_result2, inet_addr("127.0.0.1"));
    EXPECT_EQ(server_name_result2, "example.com");
    EXPECT_EQ(index_result2, "index.html");
    EXPECT_EQ(default_error_page_result2, "");
    EXPECT_EQ(client_body_size_result2, 1024);
	EXPECT_EQ(upload_path_result2.size(), 0);
	EXPECT_EQ(allow_method_result2.size(), 0);
	EXPECT_EQ(autoindex_result2, true);
	//location1
	EXPECT_EQ(port_result3, 80);
    EXPECT_EQ(root_result3, "/var/html");
    EXPECT_EQ(addr_result3, inet_addr("127.0.0.1"));
    EXPECT_EQ(server_name_result3, "example.com");
    EXPECT_EQ(index_result3, "test.html");
    EXPECT_EQ(default_error_page_result3, "");
    EXPECT_EQ(client_body_size_result3, 10240);
	EXPECT_EQ(upload_path_result3.size(), 0);
	EXPECT_EQ(allow_method_result3.size(), 0);
	EXPECT_EQ(autoindex_result3, false);
	EXPECT_EQ(url_result3, "/");
	EXPECT_EQ(return_value3.first, 307);
	
	//location2
	EXPECT_EQ(port_result4, 81);
    EXPECT_EQ(root_result4, "/var/html");
    EXPECT_EQ(addr_result4, inet_addr("127.0.0.1"));
    EXPECT_EQ(server_name_result4, "example.com");
    EXPECT_EQ(index_result4, "index.html");
    EXPECT_EQ(default_error_page_result4, "");
    EXPECT_EQ(client_body_size_result4, 1024);
	EXPECT_EQ(upload_path_result4.size(), 0);
	EXPECT_EQ(allow_method_result4.size(), 3);
	EXPECT_EQ(autoindex_result4, true);
	EXPECT_EQ(url_result4, "/");
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
