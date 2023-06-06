#include "Server.hpp"

Server::Server()
{

}


Server::Server(int server_fd, std::vector<ServerBlock *> config) : _server_fd(server_fd), _configs(config)
{
}

Server::~Server()
{

}

Server::Server(const Server& server)
{
    _server_fd = server._server_fd;
    _configs = server._configs;
    _clients = server._clients;
}

Server& Server::operator=(const Server& server)
{
    _server_fd = server._server_fd;
    _configs = server._configs;
    _clients = server._clients;
    return (*this);
}

void Server::disconnect_client(int client_fd)
{
    close(client_fd);
    _clients.erase(client_fd);
}

void Server::accept_new_client(int client_fd)
{
    char *buf = { '\0', };
    socklen_t addr_len;
    struct sockaddr_in addr;

    getsockname(client_fd, (struct sockaddr *)&addr, &addr_len);
    inet_ntop(AF_INET, &addr.sin_addr, buf, INET_ADDRSTRLEN);
    _clients[client_fd] = Connection(client_fd, std::string(buf));
    Logger::writeInfoLog(_clients[client_fd].getClinetFd(), "Add new Client", false);
}

void Server::checkConnectionTimeout()
{
    for(std::map<int, Connection>::iterator it = _clients.begin() ; it != _clients.end(); ++it)
    {
        if (std::time(NULL) - it->second.getCurrentConnectionTime() > 60)
        {
            Logger::writeInfoLog(it->second.getClinetFd(), "Timeout Connection client", false);
            disconnect_client(it->first);
            break;
        }
    }
}

void Server::sendMessage(int client_fd)
{
    if (!_clients[client_fd].sendMessage())
        disconnect_client(client_fd);
}

void Server::recvMessage(int client_fd)
{
    if (!_clients[client_fd].receiveMessage(_configs))
        disconnect_client(client_fd);
}