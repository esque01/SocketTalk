#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Client
{
public:
    Client(const char*, int);
    ~Client();
    bool connectToServer();
    void closeConnection();
    void sendData(const char*);
private:
    const char* serverIP;
    int serverPort;
    int clientSocket;    
};


#endif