//HI THIS IS MY FIRST CAHNGES IN GITHUB
//THIS IS MY FIRST PULL REQUEST
#include <iostream>
using namespace std;

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

char currentPlayer = 'X';
int moveCount = 0;

void display_board() {
    for (int i = 0; i < 3; i++) {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2];
        if (i < 2) {
            cout << "\n---|---|---\n";
        }
    }
    cout << "\n";
}

bool checkWin() {
    // check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == currentPlayer &&
            board[i][1] == currentPlayer &&
            board[i][2] == currentPlayer)
            return true;

        if (board[0][i] == currentPlayer &&
            board[1][i] == currentPlayer &&
            board[2][i] == currentPlayer)
            return true;
    }

    // check diagonals
    if (board[0][0] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][2] == currentPlayer)
        return true;

    if (board[0][2] == currentPlayer &&
        board[1][1] == currentPlayer &&
        board[2][0] == currentPlayer)
        return true;

    return false;
}

bool checkDraw() {
    return moveCount == 9;
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

int main() {
    int choice;
    bool gameOver = false;

    while (!gameOver) {
        display_board();

        cout << "Player " << currentPlayer << ", enter a number (1-9): ";
        cin >> choice;

        // Validate input
        if (choice < 1 || choice > 9) {
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        // Check if the cell is already taken
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Cell already taken. Try again...\n";
            continue;
        }

        // Make the move
        board[row][col] = currentPlayer;
        moveCount++;

        // Check win
        if (checkWin()) {
            display_board();
            cout << "Player " << currentPlayer << " wins!\n";
            gameOver = true;
            break;
        }

        // Check draw
        else if (checkDraw()) {
            display_board();
            cout << "It's a draw!\n";
            gameOver = true;
            break;
        }

        // Switch player
        switchPlayer();
    }

    cout << "\nGame Over. Thanks for playing!\n";
    return 0;
}




// #include<iostream>
// using namespace std;
// char board[3][3]={
//     {'1','2','3'},
//     {'4','5','6'},
//     {'7','8','9'}
// };
// char currentPlayer='X'; //start with X
// int moveCount=0;

// void display_board(){
//     for(int i=0;i<3;i++){
//         cout<<" "<<board[i][0]<<" | "<<board[i][1]<<" | "<<board[i][2];
//         if(i<2){
//             cout<<"\n---|---|---\n";
//         }
//     }
//     cout<<"\n";
// }
// bool checkWin(){
//     int i;
//     //check for row,col,diagonal
//     for(i=0;i<3;i++){
//         //check rows
//         if(board[i][0]==currentPlayer && board[i][1]==currentPlayer && board[i][2]==currentPlayer){
//             return true;
//         }

//         //check colums
//         if(board[0][i]==currentPlayer && board[1][i]==currentPlayer && board[2][i]==currentPlayer){
//             return true;
//         }
//     }
//     //check for diagonal primary,secondary
//     //pd
//     if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer){
//         return true;
//     }
//     //sd
//     if(board[2][0]==currentPlayer && board[1][1]==currentPlayer && board[0][2]==currentPlayer){
//         return true;
//     }

//     return false;
// }
// bool checkDraw(){
//     if (moveCount==9){
//         return true;
//     }
//     return false;
// }
// void swichPlayer(){
//     currentPlayer= (currentPlayer=='X')?'O':'X';
// }
// int main(){
//     //initialize_board();
//     //display_board();
//     int choice;
//     bool gameOver=false;
//     while(!gameOver){
//         display_board();

//         cout<<"\nPlayer :"<<currentPlayer<<" :Enter a number(1-9):";
//         cin>>choice;

//         //convert 1-9 to board position
//         int row=(choice-1)/3; 
//         int col=(choice-1)%3;

//         if(board[row][col]=='X' || board[row][col]=='O'){
//             cout<<"cell already taken. try again...";
//             continue;
//         }

//         //if cell not taken then make move
//         board[row][col]=currentPlayer;
//         moveCount++;

//         //check for win
//         if(checkWin()){
//             display_board();
//             cout<<"\nPlayer:"<<currentPlayer<<" wins!!!\n";
//             gameOver=true;
//             break;
//         }

//         //check for draw
//         else if(checkDraw()){
//             display_board();
//             cout<<"\nIt's Draw!\n";
//             gameOver=true;
//             break;
//         }
//         else{
//             swichPlayer();
//         }

//     }
//     return 0;
// }
