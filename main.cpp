/**
 * @file XO_Demo.cpp
 * @brief Entry point for the FCAI X-O (Tic-Tac-Toe) game.
 *
 * This file initializes the X-O game by creating the user interface, board, and players.
 * It then launches the game loop via the GameManager class.
 * All dynamically allocated objects are properly deleted at the end.
 */

#include <iostream> // Required for input/output operations (cout, cin)
#include <string>   // Required for string
#include <vector>   // Required for vector
#include <memory>   // Required for unique_ptr

#include "BoardGame_Classes.h"
#include "Inf_TicTacToe.h"
using namespace std;

void menu() {
    cout<<"Welcome to Game Hub"<<"\n";
    cout<<"Choose a Game to play"<<"\n";
    cout<<"1 - Infinity Tic-Tac-Toe"<<"\n";
    int choice;
    cin>>choice;
    switch (choice) {
        case 1: {
            UI<char>* game_ui = new Inf_XO_UI();
            Board<char>* inf_xo_board = new Inf_XO_Board();
            Player<char>** players = game_ui->setup_players();
            GameManager<char> inf_xo_game(inf_xo_board, players, game_ui);
            inf_xo_game.run();
            delete game_ui;
            delete inf_xo_board;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            delete[] players;
            break;
        }
        default:
            cout<<"Invalid Option"<<"\n";
    }

}


/**
 * @brief Main function to run the X-O game.
 *
 * This function orchestrates the game by:
 * - Initializing the random number generator
 * - Creating the X-O specific UI and board
 * - Setting up players using the UI
 * - Running the main game loop through the GameManager
 * - Performing cleanup of dynamically allocated memory
 *
 * @return int Returns 0 on successful execution.
 */


int main() {

    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    menu();
    return 0; // Exit successfully
}