#include "server.h"

Server::Server(int p) : port(p)
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Error creating server socket" << std::endl;
    }

    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    int enable = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        std::cerr << "setsockopt(SO_REUSEADDR) failed" << std::endl;
    }

    if (bind(serverSocket, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error binding server socket: " << strerror(errno) << std::endl;
    }

    if (listen(serverSocket, SOMAXCONN) == -1)
    {
        std::cerr << "Error listening for connections" << std::endl;
    }

    std::cout << "Server listening on port: " << port << std::endl;
}

Server::~Server()
{
    close(serverSocket);
}

void Server::handleClient(int clientSocket)
{
    char buffer[1024];
    ssize_t bytesRead;
    
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0)
    {
        buffer[bytesRead] = '\0';
        std::cout << "Recieved from client: " << buffer;

        std::string response = "Server recieved: ";
        response += buffer;

        send(clientSocket, response.c_str(), response.length(), 0);
    }

    if (bytesRead == 0)
    {
        std::cout << "Client closed connection." << std::endl;
    }
    else
    {
        std::cerr << "Error recieving data from client." << std::endl;
    }

    close(clientSocket);
}

void Server::start()
{
    while (true)
    {
        struct sockaddr_in clientAddr;
        socklen_t clientAddLen = sizeof(clientAddr);

        int clientSocket = accept(serverSocket, (struct sockaddr*)(&clientAddr), &clientAddLen);

        if (clientSocket == -1)
        {
            std::cerr << "Error accepting client connection" << std::endl;
        }
        handleClient(clientSocket);
    }
}

void Server::stop() {
    close(serverSocket);
}