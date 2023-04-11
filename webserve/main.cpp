//
// Created by Sehoon Jang on 3/29/23.
//

#include "WebServer/WebServer.hpp"

int main(int argc, char *argv[])
{
    if (argc ==  2)
    {
        WebServer webserver(argv[1]);
        webserver.run();
    }
    else
    {
        std::cout << "Argument Error!\n";
        exit(1);
    }

    return (0);
}
