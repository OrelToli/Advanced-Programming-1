//
// Created by Orel on 03/12/2017.
//

#ifndef EX3NEW_CLIENT_H
#define EX3NEW_CLIENT_H


class Client {

public:
    Client(const char *serverIP, int serverPort);
    void connectToServer();
    char* sendMove(char* move);
    int getPlayerType();

private:
    const char *serverIP;
    int serverPort;
    int clientSocket;

};
#endif //EX3NEW_CLIENT_H
