#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int N = 9;

// Function to print the Sudoku board
void printBoard(vector<vector<int>>& board) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0 && j != N - 1) {
                cout << "| ";
            }
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i != N - 1) {
            cout << "---------------------" << endl;
        }
    }
}

// Function to check if a number is safe to place in a cell
bool isSafe(vector<vector<int>>& board, int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < N; ++i) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // Check 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(vector<vector<int>>& board) {
    int row, col;

    // Find an empty cell
    bool foundEmpty = false;
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (board[row][col] == 0) {
                foundEmpty = true;
                break;
            }
        }
        if (foundEmpty) {
            break;
        }
    }

    // If no empty cell is found, the puzzle is solved
    if (!foundEmpty) {
        return true;
    }

    // Try placing numbers 1 to 9 in the empty cell
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;

            // Recursively solve the rest of the puzzle
            if (solveSudoku(board)) {
                return true;
            }

            // If the current configuration doesn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    // No solution found for this configuration
    return false;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    vector<vector<int>> board(N, vector<int>(N, 0));

    // Generate a random Sudoku puzzle (incomplete)
    for (int i = 0; i < 20; ++i) {
        int row = rand() % N;
        int col = rand() % N;
        int num = rand() % N + 1;
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
        }
    }

    cout << "Sudoku Puzzle:" << endl;
    printBoard(board);

    if (solveSudoku(board)) {
        cout << "\nSolved Sudoku:" << endl;
        printBoard(board);
    } else {
        cout << "\nNo solution found." << endl;
    }

    return 0;
}
