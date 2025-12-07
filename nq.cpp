#include <iostream>
#include <vector>
using namespace std;

void printBoard(vector<vector<char>>& board) {
    cout << endl;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool isSafe(vector<vector<char>>& board, int row, int col) {
    // check vertical up
    for (int i = row - 1; i >= 0; i--) {
        if (board[i][col] == 'Q') {
            return false;
        }
    }

    // check left diagonal up
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    // check right diagonal up
    for (int i = row - 1, j = col + 1; i >= 0 && j < board.size(); i--, j++) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    return true;
}

void nqueen(vector<vector<char>>& board, int row) {
    if (row == board.size()) {
        printBoard(board);
        return;
    }

    for (int j = 0; j < board.size(); j++) {
        if (isSafe(board, row, j)) {
            board[row][j] = 'Q';
            nqueen(board, row + 1);
            board[row][j] = 'X'; // backtrack
        }
    }
}

int main() {
    int n = 4;
    vector<vector<char>> board(n, vector<char>(n, 'X'));

    cout << "Initial Board Start" << endl;
    printBoard(board);
    cout << "Initial Board End" << endl;

    nqueen(board, 0);

    return 0;
}
