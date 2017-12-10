//
// Created by orel on 02/12/17.
//

#include <fstream>
#include "Server.h"
using namespace std;

Server::Server() {
    string ip;
    char ipAddress[20], port[4];
    ifstream myFile;
    myFile.open("serverSettings.txt");
    if(myFile.is_open()){
        //read the ip address
        myFile>>ipAddress;
        ip = ipAddress;
        //read the port number
        myFile>>port;
        this->port = atoi (port);
        myFile>>this->port;
    }
    //close "settings.txt" file
    myFile.close();
}



void Server::start() {
    //create socket that works as TCP
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error openning socket";
    }
    //define local address for the socket of the server
    struct sockaddr_in serverAdress;
    bzero((void*)&serverAdress, sizeof(serverAdress));
    serverAdress.sin_family = AF_INET;
    serverAdress.sin_addr.s_addr = INADDR_ANY;
    serverAdress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr*)&serverAdress, sizeof(serverAdress)) ==-1) {
        throw "Error on binding";
    }

    while(true) {

        //waiting for the first client to connect
        listen(serverSocket, MAX_CONNECTED_CLIENTS);
        cout << "waiting for clients to connect" << endl;
        //accept the first client
        int firstClient = getSocketOfClient(), turn, n;
        cout << "waiting for other player" << endl;
        //accept the second pla
        int secondClient = getSocketOfClient();
        //tell both of the players about their type and turn
        //write the turn of the player into the socket of the first client
        turn = 1;
        n = write(firstClient, &turn, sizeof(turn));
        if (n == -1) {
            throw "Error writing to the first client socket";
        }
        //write the turn of the player into the socket of the second client
        turn = 2;
        n = write(secondClient, &turn, sizeof(turn));
        if (n == -1) {
            throw "Error writing to the second client socket";
        }
        handleClient(firstClient, secondClient);
        //disconnect both of the players in the end of the game
        close(firstClient);
        close(secondClient);
        cout << "Game Over" << endl;
    }

}


int Server::getSocketOfClient() {
    struct sockaddr_in address;
    socklen_t addressLength;
    //accept a new client connection
    int socketOfClient = accept(serverSocket, (struct sockaddr*)&address, &addressLength);
    if (socketOfClient==-1) {
        throw "Error during accepting the client";
    }
    return socketOfClient;
}



void Server::handleClient(int client1, int client2) {
    int row, col, currentClient = client1, otherClient = client2,n;
    while (true) {
        //read row value from the socket of the current player
        n = read(currentClient, &row, sizeof(row));
        if (n==-1) {
            cout << "Error reading the row value";
            return;
        }
        //read col value from the socket of the current player
        n = read(currentClient,&col,sizeof(col));
        if (n ==-1) {
            cout <<"Error reading the col value" <<endl;
            return;
        }
        //inform opponent about selected move
        n = write(otherClient,&row,sizeof(row));
        if (n ==-1) {
            cout <<"Error writing to socket" <<endl;
            return;
        }
        n = write(otherClient,&col,sizeof(col));
        if (n ==-1) {
            cout <<"Error writing to socket" <<endl;
            return;
        }

        if(row == -2)
            break;
        changeClient(&currentClient, &otherClient);
    }
}


void Server::changeClient(int *currentClient, int *opponentClient){
    int temp = *currentClient;
    *currentClient = *opponentClient;
    *opponentClient = temp;
}


void Server::stop() {
    close(this->serverSocket);
}
