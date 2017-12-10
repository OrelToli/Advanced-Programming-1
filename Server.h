//
// Created by orel on 02/12/17.
//

#ifndef SERVER_H
#define SERVER_H
#define MAX_CONNECTED_CLIENTS 2

#define NO_MOVES "NoMove"
#define END_GAME "End"
using namespace std;
#include <iostream>
class Server {

public:
    Server(int port);
    void start();
    void stop();
    void handleClient(int client1, int client2);
    int getSocketOfClient();
    void changeClient(int *currentClient, int *opponentClient);
private:
    int port;
    int serverSocket;
};


#endif //SERVER_H

