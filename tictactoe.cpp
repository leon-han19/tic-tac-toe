//
//  main.cpp
//  lab04_01
//
//  Created by Leon Han on 2019-10-16.
//  Copyright © 2019 Leon Han. All rights reserved.
//

/* I ran through heavy testing and debugging for the functions that checked the rows, columns and diagonals for 4 in a row of either X or O. I ran through similar steps of scenarios for all three. I tested each one for the X condition and the O condition, and I checked that each individual row/column/diagonal was checking correctly. I also heavily tested the user_move function to ensure that the moves were properly alternating between player X and O's turns. The main problem was figuring out how to check the multi-dimensional array for the location entered by the user, a number from 1 to 16. At first I tried to test it by running through the entire array and check for the number, but I found that a more efficient way was to use mathematical formulas so that the program wouldn't have to loop through the array. To test if the location corresponding to the user input was being selected by the program, I used a cout statement that printed the (x, y) coordinates of the number that the user inputed (cout << "(" << row << "," << column << ")" << endl;). For example, if the user entered 1, it would output (0, 0). */

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;

// fucntion declarations
void run_game(bool x_turn);
void print_board(string board[][4]);
bool user_move(string board[][4], bool x_turn);
bool check_win(string board[][4]);
bool check_row(string board[][4], int cur_row);
bool check_column(string board[][4], int cur_column);
bool check_diagonal_1(string board[][4]);
bool check_diagonal_2(string board[][4]);
bool check_full(string board[][4]);
bool check_tie(string board[][4]);
bool play_again();

int main() {
    // player X goes first
    bool x_turn = true;
    bool restart = false;
    
    do {
        // runs the game and checks to see if the players want to play again at least once using do while
        run_game(x_turn);
        restart = play_again();
        
        // switches turn order after each restart
        x_turn = !x_turn;
        cout << 4 % 10;

    } while (restart);
    
    return 0;
}

// function that is called in user_move function to print the board after every turn is made
void print_board(string board[][4]) {
    cout << "Current board:" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

bool user_move(string board[][4], bool x_turn) {
    int user_input;
    
    cout << "Enter a number between 1 and 16 inclusive." << endl;
    cin >> user_input;
    
    // mathematical equations to find a coordinate corresponding to the user input
    int row = user_input / 4;
    int column = (user_input % 4) - 1;
    
    // cout << "(" << row << "," << column << ")" << endl; --> used to test if correct location was being chosen by the program
    
    if (board[row][column] == "X" || board[row][column] == "O") {
        cout << "That position is already occupied, please enter another location. ";
       
        // breaks out of loops if the location is invalid, but it is still the current player's turn
        return x_turn;
        
    } else if (user_input > 16 || user_input < 1) {
        // checks if the position entered is within the array; if not, it prompts the user to enter a valid location
        cout << "That is not a valid location, please enter a number between 1 and 16 inclusive.";
        
        // returns x_turn because it is still that same player's turn
        return x_turn;
    } else {
        if (x_turn) {
            board[row][column] = "X";
        } else {
            board[row][column] = "O";
        }
    }
    
    // prints out the board each time a player enters a location to check the game status
    print_board(board);

    // ends current player's turn, goes to the other player
    return !x_turn;
}

void run_game(bool x_turn) {
    string board[4][4] = {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "16"}
    };
    print_board(board);
    
    bool game_over = false;
    while(!game_over) {
        x_turn = user_move(board, x_turn);
        if (check_win(board)) {
            game_over = true;
        } else if (check_tie(board)) {
            game_over = true;
        }
    }
}

bool check_win(string board[][4]) {
    // since the game is still running, game_over is set to false to begin
    bool game_over = false;
    
    // loop to check if the check_row function has returned true, meaning somebody has won --> game_over set to true
    for (int row = 0; row < 4; row++) {
        if(check_row(board, row)) {
            game_over = true;
            return game_over;
        }
    }
    
    // loop to check if the check_column function has returned true, meaning somebody has won --> game_over set to true
    for (int column = 0; column < 4; column++) {
        if(check_column(board, column)) {
            game_over = true;
            return game_over;
        }
    }
    
    // if statements to check if the check_diagonal functions have returned true --> game_over set to true
    if (check_diagonal_1(board)) {
        game_over = true;
        return game_over;
    } else if (check_diagonal_2(board)) {
        game_over = true;
        return game_over;
    }
    
    // the program will only reach this point if all the check for win functions have returned false, so the final game_over below will be false
    return game_over;
}

// check if a row has 4 X's or 4 O's
bool check_row(string board[][4], int cur_row) {
    bool game_over = false;
    
    // variables to keep track of how many X's or O's the program comes across while checking the rows
    int count_x = 0;
    int count_o = 0;
    
    // loops through each row to check for X's or O's, and increases the respective character count when one is found
    for (int y1 = 0; y1 < 4; y1++) {
        if (board[cur_row][y1] == "X") {
            count_x++;
        } else if (board[cur_row][y1] == "O") {
            count_o++;
        }
    }
    
    // if either character count reaches 4 then the game is over
    if (count_x == 4) {
        cout << "player X wins!" << endl;
        game_over = true;
    } else if (count_o == 4) {
        cout << "player O wins!" << endl;
        game_over = true;
    }
    
    return game_over;
}

// logic for checking columns is the same as checking rows
bool check_column(string board[][4], int cur_column) {
    bool game_over = false;
    
    // variables to keep track of how many X's or O's the program comes across while checking the columns
    int count_x = 0;
    int count_o = 0;
    
    for (int x1 = 0; x1 < 4; x1++) {
        if (board[x1][cur_column] == "X") {
            count_x++;
        } else if (board[x1][cur_column] == "O") {
            count_o++;
        }
    }
    
    if (count_x == 4) {
        cout << "player X wins!" << endl;
        game_over = true;
    } else if (count_o == 4) {
        cout << "player O wins!" << endl;
        game_over = true;
    }
    
    return game_over;
}

bool check_diagonal_1(string board[][4]) {
    bool game_over = false;
    
    // variables to keep track of how many X's or O's the program comes across while checking the diagonal
    int count_x = 0;
    int count_o = 0;
    
    for (int i = 0; i < 4; i++) {
        if (board[i][i] == "X") {
            count_x++;
        } else if (board[i][i] == "O") {
            count_o++;
        }
    }
    
    if (count_x == 4) {
        cout << "player X wins!" << endl;
        game_over = true;
    } else if (count_o == 4) {
        cout << "player O wins!" << endl;
        game_over = true;
    }
    
    return game_over;
}

bool check_diagonal_2(string board[][4]) {
    bool game_over = false;
    
    // variables to keep track of how many X's or O's the program comes across while checking the diagonal
    int count_x = 0;
    int count_o = 0;
    int j = 3; // used as the "column" variable for the board in the for loop below
    
    for (int i = 0; i < 4; i++) {
        if (board[i][j] == "X") {
            count_x++;
        } else if (board[i][j] == "O") {
            count_o++;
        }
        j--;
    }
    
    if (count_x == 4) {
        cout << "player X wins!" << endl;
        game_over = true;
    } else if (count_o == 4) {
        cout << "player O wins!" << endl;
        game_over = true;
    }
    
    return game_over;
}

// function to check for ties
bool check_tie (string board[][4]) {
    int counter = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // while looping through the array, if the program comes across an X or O, it increases the counter by 1
            if (board[i][j] == "X" || board [i][j] == "O") {
                counter++;
            }
        }
    }
    // if the entire board is filled with X's and O's, print out that it is a tie
    if (counter == 16) {
        cout << "The game is over, it's a tie!" << endl;
    }
    
    // returns false if counter does not reach 16 i.e. if the board is not full of X's and O's
    return counter == 16;
}

// function to ask the user if they want to restart
bool play_again() {
    bool restart = false;
    int user_input;
    
    cout << "Would you like to play again? Enter 1 for yes or 2 for no." << endl;
    cin >> user_input;
    
    if (user_input == 1) {
        restart = true;
    } else if (user_input == 2) {
        return restart;
    }
    
    return restart;
}

