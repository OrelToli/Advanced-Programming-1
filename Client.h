//
// Created by Orel on 03/12/2017.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
using namespace std;
class Client {

public:
    Client(const char *serverIP, int serverPort);
    void connectToServer();
    void sendMove(int* move);
    int getPlayerType();
    void getRemoteMove(int* move);

private:
    const char *serverIP;
    int serverPort;
    int clientSocket;

};
#endif //CLIENT_H
