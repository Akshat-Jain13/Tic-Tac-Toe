#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to draw the game board
void drawBoard(const vector<char>& board) {
    cout << " 1" <<  " | 2" << " | 3    " << " " << board[0] << " | " << board[1] << " | " << board[2] << "\n";
    cout << "---+---+---   " << "---+---+---\n";
    cout << " 4" <<  " | 5" << " | 6    " << " " << board[3] << " | " << board[4] << " | " << board[5] << "\n";
    cout << "---+---+---   " << "---+---+---\n";
    cout << " 7" <<  " | 8" << " | 9    " << " " << board[6] << " | " << board[7] << " | " << board[8] << "\n";
}

// Function to check if a player has won
int checkWin(const vector<char>& board) {
    // Check rows
    for (int i = 0; i < 9; i += 3) {
        if (board[i] != ' ' && board[i] == board[i + 1] && board[i + 1] == board[i + 2]){
            if (board[i] == 'X') return 1;
            else return 2;
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[i] != ' ' && board[i] == board[i + 3] && board[i + 3] == board[i + 6]){
            if (board[i] == 'X') return 1;
            else return 2;
        }
    }

    // Check diagonals
    if (board[0] != ' ' && board[0] == board[4] && board[4] == board[8]){
        if (board[0] == 'X') return 1;
        else return 2;
    }
    if (board[2] != ' ' && board[2] == board[4] && board[4] == board[6]){
        if (board[2] == 'X') return 1;
        else return 2;
    }

    return 0;
}

// Function to check if the game is a draw
bool checkDraw(const vector<char>& board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ')
            return false;
    }
    return true;
}

// Function to evaluate the score of the board for the computer player
int evaluate(const vector<char>& board) {
    if (checkWin(board) == 2)
        return 1;
    else if (checkWin(board) == 1)
        return -1;
    else
        return 0;
}

// Function to perform the minimax algorithm with alpha-beta pruning
int minimax(vector<char>& board, int depth, int alpha, int beta, bool maximizingPlayer) {
    int score = evaluate(board);
    if (score != 0) return score;
    if (checkDraw(board)) return 0;

    if (maximizingPlayer) {
        int maxEval = INT_MIN;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int eval = minimax(board, depth + 1, alpha, beta, false);
                board[i] = ' ';
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha)
                    break;
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < 9; ++i) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int eval = minimax(board, depth + 1, alpha, beta, true);
                board[i] = ' ';
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if (beta <= alpha)
                    break;
            }
        }
        return minEval;
    }
}

// Function to find the best move for the computer player
int findBestMove(vector<char>& board) {
    int bestEval = INT_MIN;
    int bestMove = -1;
    for (int i = 0; i < 9; ++i) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int eval = minimax(board, 0, INT_MIN, INT_MAX, false);
            board[i] = ' ';
            if (eval > bestEval) {
                bestEval = eval;
                bestMove = i;
            }
        }
    }
    return bestMove;
}

// Function to play the game
void playGame() {
    vector<char> board(9, ' '); 
    int currentPlayer = 0;
    int game;
    
    cout << "Enter 1 for single player and 2 for double player: ";
    cin >> game;

    while (true) {
        drawBoard(board);
        cout << endl;
        if (currentPlayer == 0) {
            int position;
            cout << "Player " << (currentPlayer + 1) <<" [X], Enter a position (1-9): ";
            cin >> position;

            --position;

            if (position < 0 || position >= 9 || board[position] != ' ') {
                cout << "Invalid move. Try again.\n";
                continue;
            }
            board[position] = 'X';
            currentPlayer = 1;
        } 
        else if (game == 1) {
            int move = findBestMove(board);
            board[move] = 'O';
            currentPlayer = 0;
        } 
        else {
            int position;
            cout << "Player " << (currentPlayer + 1) <<" [O], Enter a position (1-9): ";
            cin >> position;

            --position;

            if (position < 0 || position >= 9 || board[position] != ' ') {
                cout << "Invalid move. Try again.\n";
                continue;
            }
            board[position] = 'O';
            currentPlayer = 0;
        }

        int winner = checkWin(board);
        if (winner == 1) {
            drawBoard(board);
            cout << "Player 1 won!\n";
            break;
        } 
        else if (winner == 2) {
            drawBoard(board);
            cout << "Player 2 won!\n";
            break;
        } 
        else if (checkDraw(board)) {
            drawBoard(board);
            cout << "It's a draw!\n";
            break;
        }
    }
}

int main() {
    cout << "   === TIC-TAC-TOE ===\n\n";
    playGame();
    return 0;
}
