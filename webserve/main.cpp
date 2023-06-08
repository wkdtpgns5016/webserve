//
// Created by Sehoon Jang on 3/29/23.
//

#include "./WebServer/WebServer.hpp"

int main(int argc, char *argv[])
{
    std::string conf_str;
    try
    {
        if (argc ==  2)
            conf_str = ft::readFileIntoString(argv[1]);
        else
            conf_str = ft::readFileIntoString("./var/conf/tester.conf");
        if (conf_str.empty())
        {
            std::cerr << "Invaild Config File" << std::endl;
            exit(1);
        }
        Conf conf(conf_str);
        WebServer webserver(conf);
        webserver.run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what();
        return 1;
    }
    return (0);
}
