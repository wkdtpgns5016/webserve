//
// Created by Sehoon Jang on 3/29/23.
//

#include "./WebServer/WebServer.hpp"

int main(int argc, char *argv[])
{
    if (argc ==  2)
    {
        try
		{
			Conf conf(ft::readFileIntoString(argv[1]));
			WebServer webserver(conf);
			webserver.run();
		}
		catch (std::exception)
		{
			return 1;
        }
    }
    else
    {
        std::cout << "Argument Error!\n";
        exit(1);
    }

    return (0);
}
