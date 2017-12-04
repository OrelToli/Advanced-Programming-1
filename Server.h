//
// Created by orel on 02/12/17.
//

#ifndef EX3NEW_SERVER_H
#define EX3NEW_SERVER_H


class Server {

public:
    Server(int port);
    void start();
    void stop();

private:
    int port;
    int serverSocket;

    void handleClient(int clientSocket);



};


#endif //EX3NEW_SERVER_H
