#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Server
{
private: 
    int serverSocket;
    int port;
public:
    Server(int);
    ~Server();
    void start();
    void stop();
    void handleClient(int);
};

#endif