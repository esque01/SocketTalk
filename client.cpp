#include "client.h"

Client::Client(const char* serverIP, int serverPort) : serverIP(serverIP), serverPort(serverPort) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating client socket..." << std::endl;
    }
}

Client::~Client() {
    close(clientSocket);
}

bool Client::connectToServer(){
    struct sockaddr_in serverAddr;

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);

    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to the server" << std::endl;
        close(clientSocket);
        return false;
    }
    return true;
}

void Client::sendData(const char* data) {
    send(clientSocket, data, strlen(data), 0);
}

void Client::closeConnection() {
    close(clientSocket);
}

