#include <iostream>
using namespace std;

char board[9] = {'1','2','3','4','5','6','7','8','9'};
char human = 'X';
char ai = 'O';

void display() {
    cout << "\n";
    cout << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n\n";
}

// Simple winner checker (no auto, no arrays)
bool checkWinner(char p) {
    // rows
    if (board[0]==p && board[1]==p && board[2]==p) return true;
    if (board[3]==p && board[4]==p && board[5]==p) return true;
    if (board[6]==p && board[7]==p && board[8]==p) return true;

    // columns
    if (board[0]==p && board[3]==p && board[6]==p) return true;
    if (board[1]==p && board[4]==p && board[7]==p) return true;
    if (board[2]==p && board[5]==p && board[8]==p) return true;

    // diagonals
    if (board[0]==p && board[4]==p && board[8]==p) return true;
    if (board[2]==p && board[4]==p && board[6]==p) return true;
    return false;
}

bool checkDraw() {
    for (int i = 0; i < 9; i++)
        if (board[i] != 'X' && board[i] != 'O')
            return false;
    return true;
}

int minimax(bool isMax) {
    if (checkWinner(ai)) return 1;
    if (checkWinner(human)) return -1;
    if (checkDraw()) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                char save = board[i];
                board[i] = ai;
                int score = minimax(false);         //false => AI
                board[i] = save;
                if (score > best) best = score;  //>
            }
        }
        return best;
    } 
    else {
        int best = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                char save = board[i];
                board[i] = human;
                int score = minimax(true);          // TRUE => HUMAN
                board[i] = save;
                if (score < best) best = score; //<
            }
        }
        return best;
    }
}

void aiMove() {
    int bestScore = -1000;
    int bestMove = -1;
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            char save = board[i];
            board[i] = ai;
            int score = minimax(false);               // FALSE => AIMOVE
            board[i] = save;

            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }
    board[bestMove] = ai;
    cout << "AI played at position: " << bestMove + 1 << "\n";
}
int main() {
    int pos;

    while (true) {
        display();
        cout << "Enter position (1-9): ";
        cin >> pos;
        pos--;
        if (pos < 0 || pos > 8 || board[pos] == 'X' || board[pos] == 'O') {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[pos] = human;

        if (checkWinner(human)) {
            display();
            cout << "You win!\n";
            break;
        }
        if (checkDraw()) {
            display();
            cout << "Draw!\n";
            break;
        }

        aiMove();

        if (checkWinner(ai)) {
            display();
            cout << "AI wins!\n";
            break;
        }
        if (checkDraw()) {
            display();
            cout << "Draw!\n";
            break;
        }
    }
    return 0;
}
