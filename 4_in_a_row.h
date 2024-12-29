#ifndef _4_IN_A_ROW_H
#define _4_IN_A_ROW_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>

template <typename T>
class FourInARowBoard : public Board<T> {
public:
    FourInARowBoard();
    ~FourInARowBoard();

    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

private:
    bool check_horizontal_win();
    bool check_vertical_win();
    bool check_diagonal_win();
};

template <typename T>
class FourInARowPlayer : public Player<T> {
public:
    FourInARowPlayer(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class FourInARowRandomPlayer : public RandomPlayer<T> {
public:
    FourInARowRandomPlayer(T symbol);
    void getmove(int& x, int& y) override;
};

// IMPLEMENTATION

// Constructor for FourInARowBoard
template <typename T>
FourInARowBoard<T>::FourInARowBoard() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

// Destructor to prevent memory leaks
template <typename T>
FourInARowBoard<T>::~FourInARowBoard() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

// Update board with special rules for Four-in-a-Row
template <typename T>
bool FourInARowBoard<T>::update_board(int x, int y, T mark) {
    // Special rule: Find the lowest empty cell in the selected column
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }

    // If a 0 mark is used, this is an undo move
    if (mark == 0) {
        this->board[x][y] = 0;
        this->n_moves--;
        return true;
    }

    // Find the lowest empty cell in the column
    int lowest_empty = -1;
    for (int i = this->rows - 1; i >= 0; i--) {
        if (this->board[i][y] == 0) {
            lowest_empty = i;
            break;
        }
    }

    // If column is full, return false
    if (lowest_empty == -1) {
        return false;
    }

    // Place the symbol in the lowest empty cell
    this->board[lowest_empty][y] = toupper(mark);
    this->n_moves++;
    return true;
}

// Display the board
template <typename T>
void FourInARowBoard<T>::display_board() {
    // Print column numbers
    cout << "\n  ";
    for (int j = 0; j < this->columns; j++) {
        cout << " " << j << "  ";
    }
    cout << "\n";

    for (int i = 0; i < this->rows; i++) {
        cout << "| ";
        for (int j = 0; j < this->columns; j++) {
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------\n";
    }
    cout << endl;
}

// Check for win condition
template <typename T>
bool FourInARowBoard<T>::is_win() {
    return check_horizontal_win() ||
           check_vertical_win() ||
           check_diagonal_win();
}

// Check horizontal wins
template <typename T>
bool FourInARowBoard<T>::check_horizontal_win() {
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c <= this->columns - 4; c++) {
            if (this->board[r][c] != 0 &&
                this->board[r][c] == this->board[r][c+1] &&
                this->board[r][c] == this->board[r][c+2] &&
                this->board[r][c] == this->board[r][c+3]) {
                return true;
            }
        }
    }
    return false;
}

// Check vertical wins
template <typename T>
bool FourInARowBoard<T>::check_vertical_win() {
    for (int r = 0; r <= this->rows - 4; r++) {
        for (int c = 0; c < this->columns; c++) {
            if (this->board[r][c] != 0 &&
                this->board[r][c] == this->board[r+1][c] &&
                this->board[r][c] == this->board[r+2][c] &&
                this->board[r][c] == this->board[r+3][c]) {
                return true;
            }
        }
    }
    return false;
}

// Check diagonal wins
template <typename T>
bool FourInARowBoard<T>::check_diagonal_win() {
    // Check positive slope diagonals
    for (int r = 0; r <= this->rows - 4; r++) {
        for (int c = 0; c <= this->columns - 4; c++) {
            if (this->board[r][c] != 0 &&
                this->board[r][c] == this->board[r+1][c+1] &&
                this->board[r][c] == this->board[r+2][c+2] &&
                this->board[r][c] == this->board[r+3][c+3]) {
                return true;
            }
        }
    }

    // Check negative slope diagonals
    for (int r = 3; r < this->rows; r++) {
        for (int c = 0; c <= this->columns - 4; c++) {
            if (this->board[r][c] != 0 &&
                this->board[r][c] == this->board[r-1][c+1] &&
                this->board[r][c] == this->board[r-2][c+2] &&
                this->board[r][c] == this->board[r-3][c+3]) {
                return true;
            }
        }
    }
    return false;
}

// Check for draw condition
template <typename T>
bool FourInARowBoard<T>::is_draw() {
    return (this->n_moves == this->rows * this->columns && !is_win());
}

// Check if game is over
template <typename T>
bool FourInARowBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

// Constructor for FourInARowPlayer
template <typename T>
FourInARowPlayer<T>::FourInARowPlayer(string name, T symbol) : Player<T>(name, symbol) {}

// Get move from human player
template <typename T>
void FourInARowPlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter the column (0 to 6) to place your mark: ";
    cin >> y;

    // In Four-in-a-Row, row is determined automatically
    x = 0;  // This will be corrected in update_board method
}

// Constructor for FourInARowRandomPlayer
template <typename T>
FourInARowRandomPlayer<T>::FourInARowRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

// Get random move for computer player
template <typename T>
void FourInARowRandomPlayer<T>::getmove(int& x, int& y) {
    x = 0;  // Row will be determined automatically
    y = rand() % this->dimension;  // Random column between 0 and 6
}

#endif //_4_IN_A_ROW_H