/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */
#include<iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Server.h"
using namespace std;
int main() {
    int portNumber;
    string ipAddress;
    ifstream inputFile;
    inputFile.open("settings.txt");
    char buffer[20];
    if(inputFile.is_open()){
        //read the number of the port to buffer
        inputFile>>buffer;
        
        //convert the number of the port from string to integer
        stringstream temp(buffer);
        temp>>portNumber;
    }
    //close "settings.txt" file
    inputFile.close();
    //create the server of the game
    Server server(portNumber);
    try {
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        exit(-1);
    }

}