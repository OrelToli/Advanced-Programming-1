//
// Created by orel on 02/12/17.
//

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;
#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port): port(port), serverSocket(0) {
    cout << "Server" << endl;
}

void Server::start() {

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == -1) {
        throw "Error opening socket";
    }

    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress,sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if( bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }

    listen(serverSocket,MAX_CONNECTED_CLIENTS);

    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen;

    while(true) {
        cout << "Waiting for client connections.." << endl;

        int clientSocket = accept(serverSocket, (
        struct sockaddr *)&clientAddress, &clientAddressLen);

        cout << "Client connected" << endl;
        if(clientSocket == -1)
            throw "Error on accept";

        handleClient(clientSocket);
        close(clientSocket);
    }


}

void Server::handleClient(int clientSocket) {

    //check if client is first or second and tell them accordingly so they will be X or O

    //wait for both players to connect
    //send to first player 1
    //send to second player 2
}