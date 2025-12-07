#include <iostream>
using namespace std;

char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

char human = 'X';
char ai = 'O';
int moveCount = 0;

void display_board() {
    for (int i = 0; i < 3; i++) {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2];
        if (i < 2) cout << "\n---|---|---\n";
    }
    cout << "\n";
}

bool checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool checkDraw() {
    return moveCount == 9;
}

// Simplified minimax WITH moveCount tracking
int minimax(bool isMaximizing) {
    if (checkWin(ai)) return +10;
    if (checkWin(human)) return -10;
    if (checkDraw()) return 0;

    int bestScore = isMaximizing ? -1000 : 1000;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char original = board[i][j];
                board[i][j] = isMaximizing ? ai : human;
                moveCount++;

                int score = minimax(!isMaximizing);

                board[i][j] = original;
                moveCount--;

                if (isMaximizing)
                    bestScore = max(bestScore, score);
                else
                    bestScore = min(bestScore, score);
            }
        }
    }

    return bestScore;
}

void aiMove() {
    int bestScore = -1000;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                char original = board[i][j];
                board[i][j] = ai;
                moveCount++;

                int score = minimax(false);

                board[i][j] = original;
                moveCount--;

                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    board[bestRow][bestCol] = ai;
    moveCount++;

    cout << "AI played at position: " << (bestRow * 3 + bestCol + 1) << "\n\n";
}

int main() {
    int choice;
    bool gameOver = false;

    while (!gameOver) {
        display_board();
        cout << "Player " << human << ", enter a number (1-9): ";
        cin >> choice;

        if (choice < 1 || choice > 9) {
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
            continue;
        }

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Cell already taken. Try again...\n";
            continue;
        }

        board[row][col] = human;
        moveCount++;

        if (checkWin(human)) {
            display_board();
            cout << "Player " << human << " wins!\n";
            gameOver = true;
            break;
        } else if (checkDraw()) {
            display_board();
            cout << "It's a draw!\n";
            gameOver = true;
            break;
        }

        aiMove();

        if (checkWin(ai)) {
            display_board();
            cout << "AI (" << ai << ") wins!\n";
            gameOver = true;
            break;
        } else if (checkDraw()) {
            display_board();
            cout << "It's a draw!\n";
            gameOver = true;
            break;
        }
    }

    cout << "\nGame Over. Thanks for playing!\n";
    return 0;
}
