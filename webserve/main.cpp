//
// Created by Sehoon Jang on 3/29/23.
//

#include "./WebServer/WebServer.hpp"

int main(int argc, char *argv[])
{
    std::string conf_path;
    try
    {
        if (argc ==  2)
            conf_path = ft::readFileIntoString(argv[1]);
        else
            conf_path = "var/conf/teester.conf";
        if (conf_path.empty())
        {
            std::cerr << "Invaild File path" << std::endl;
            exit(1);
        }
        Conf conf(conf_path);
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
