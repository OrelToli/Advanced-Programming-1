/**
 * Limor Levi 308142389
 * Orel Israeli 204225148
 */

#include "PrintConsole.h"

PrintConsole::PrintConsole() {}

void PrintConsole::printBoard(Board& gameBoard){
    cout<<endl;
    cout<<"Current Board"<<endl<<endl;
    for (int i = 0; i < gameBoard.getBoardSize() ; i++) {
        cout << " | " << (i+1);
    }
    cout << " |" << endl;
    cout << "--";
    for (int k = 0; k < gameBoard.getBoardSize() ; k++)
        cout << "----";
    cout << endl;

    for (int i = 0; i < gameBoard.getBoardSize(); i++) {
        cout << (i + 1) << "|";
        for (int j = 0; j < gameBoard.getBoardSize(); j++){
            cout << " "<<returnType(gameBoard.getSquareType(i,j))<< " |";
        }
        cout << "" << endl;
        cout << "--";
        for (int k = 0; k < gameBoard.getBoardSize(); k++)
            cout << "----";
        cout << endl;
    }
    cout<<endl;
}


void PrintConsole::printOptionsToPlayer(vector<Square> &options){
    cout<<"your possible moves: ";
    for(int i=0;i<options.size();i++) {
        if(i!=options.size()-1){
            cout << "("<<(options[i].getX()+1)<<","<<(options[i].getY()+1)<<"), ";
        }
        else
            cout << "("<<(options[i].getX()+1)<<","<<(options[i].getY()+1)<<")";
    }
    cout<<endl;
}


void PrintConsole::announceTurn(Player& currentPlayer){
    cout<<returnType(currentPlayer.getType())<<": It's your move."<<endl;
}


void PrintConsole::askMoveFromPlayer(){
    cout<<"please enter your move row,col (for example  1,1) : "<<endl;
}


void PrintConsole::wrongInput(){
    cout<<"your choice isn't in the options "<<endl;
}


void PrintConsole::announceWhoWins(enum Type winner) {
    if(winner != typeEmpty)
        cout<<"the winner is: "<<returnType(winner)<<"!!!"<<endl;
    else
        cout<<"draw!!!"<<endl;
}


void PrintConsole::noOptionsToBothPlayers() {
    cout<<"there are no possible options to both of the players"<<endl;
}


void PrintConsole::fullBoard(){
    cout<<"The board is full"<<endl;
}


void PrintConsole::createSpace(){
    cout<<endl<<endl;
}


void PrintConsole::noPossibleOptionsToCurrentPlayer(enum Type currentPlayer) {
    cout<<"Player "<<returnType(currentPlayer)<<" - doesn't have any possible moves to play and loses the turn"<<endl;
}


void PrintConsole::chooseGameType() {
    cout<<"Choose an opponent type :"<<endl;
    cout<<"1. a human local player"<<endl;
    cout<<"2. an AI player"<<endl;
    cout<<"3. a remote player"<<endl;

}

void PrintConsole::printPlayAI(int row, int col) {
    cout<<endl;
    cout<<"O played ("<<row<<","<<col<<")"<<endl;

}

void PrintConsole::boardAfterUser(Player& player, int row, int col) {
    cout<<endl;
    cout<<"The Board After "<<returnType(player.getType())<<" Played:("<<row<<","<<col<<")"<<endl;
}

char PrintConsole::returnType(enum Type type) {
    switch (type){
        case (typeEmpty):
            return ' ';
        case (typeO):
            return 'O';
        case (typeX):
            return 'X';
    }
}



void PrintConsole::connectedToServer(){
    cout<<"Connected to server"<<endl;
}


void PrintConsole::waitingForOtherPlayer(){
    cout<<"waiting for other player to join..."<<endl;
}


void PrintConsole::waitingForClientConnection(){
    cout <<"Waiting for client connections..."<<endl;
}

