//
// Created by Orel on 03/12/2017.
//

#include <fstream>
#include <cstdlib>
#include "Client.h"


using namespace std;
Client::Client(){
    char ipAddress[20], port[4];
    ifstream myFile;
    myFile.open("clientSettings.txt");
    if(myFile.is_open()){
        //read the ip address
        myFile>>ipAddress;
        string temp(ipAddress);
        this->ip = temp;
        this->serverIP = ip.c_str();
        //read the port number
        myFile>>port;
        this->port = atoi (port);
        myFile>>this->port;
    }
    //close "settings.txt" file
    myFile.close();
}

void Client::connectToServer() {

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        throw "Error opening socket";
    }
    // Convert the ip string to a network address
    struct in_addr address;
    if (!inet_aton(serverIP, &address)) {
        throw "Can't parse IP address";
    }

    // Get a hostent structure for the given host address
    struct hostent *server;
    server = gethostbyaddr((const char *)&address, sizeof address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *)&address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *)&serverAddress.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    // htons converts values between host and network byte orders
    serverAddress.sin_port = htons(port);
    // Establish a connection with the TCP server
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
}

void Client::sendMove(int* move) {

    int n = write(clientSocket,&move[0], sizeof(int));
    if (n == -1) {
        throw "Error writing row to socket";
    }

    n = write(clientSocket,&move[1], sizeof(int));
    if (n == -1) {
        throw "Error writing col to socket";
    }

}


void Client::getRemoteMove(int* move) {


    cout<<"Waiting for other player's move..."<<endl;
    int n = read(clientSocket,&move[0], sizeof(int));
    if (n == -1) {
        throw "Error reading row from socket";
    }
    n = read(clientSocket,&move[1], sizeof(int));
    if (n == -1) {
        throw "Error reading col from socket";
    }

}

//1 for x, 2 for O
int Client::getPlayerType() {
    int playerType;
    int n = read(clientSocket,&playerType,sizeof(playerType));
    if (n == -1) {
        throw "Error reading from socket";
    }
    return playerType;
}



