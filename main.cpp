/**
 * @file XO_Demo.cpp
 * @brief Entry point for the FCAI X-O (Tic-Tac-Toe) game.
 *
 * This file initializes the X-O game by creating the user interface, board, and players.
 * It then launches the game loop via the GameManager class.
 * All dynamically allocated objects are properly deleted at the end.
 */

#include <iostream>
#include <ctime> 

#include "BoardGame_Classes.h"
#include "Inf_TicTacToe.h"
#include "Word_TicTacToe.h"
#include "obs_TicTacToe.h"
#include "Inverse_TicTacToe.h"
#include "Inverse_XO_UI.h"
#include "SUS.h"
#include "TIC_TAC_TOE_4X4.h"
#include "NUMERICAL_TIC_TAC_TOE.h""
#include "TicTacToe_5x5.h"
using namespace std;

template<typename T>
void set_up(UI<T>* ui, Board<T>* board) {
    Player<T>** players = ui->setup_players();
    GameManager<T> gameManger(board, players, ui);
    gameManger.run();
    delete ui;
    delete board;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    delete[] players;
}

void menu() {
    cout<<"Welcome to Game Hub"<<"\n";
    cout<<"Choose a Game to play"<<"\n";
    cout<<"1- Infinity Tic-Tac-Toe"<<"\n";
    cout<<"2- Word Tic-Tac-Toe"<<"\n";
    cout<<"3- Obstacles Tic-Tac-Toe"<<"\n";
    cout<<"4- Inverse Tic-Tac-Toe"<<"\n";
    cout<<"5- SUS Game" << "\n";
    cout<<"6- Tic_Tac_Toe_4X4"<<"\n";
    cout<<"7- NUMERICAL Tic_Tac_Toe"<<"\n";
    cout<<"8- 5x5 Tic-Tac-Toe"<<"\n";
    int choice;
    cin>>choice;
    switch (choice) {
        case 1: {
            set_up(new Inf_XO_UI(), new Inf_XO_Board());
            break;
        }
        case 2: {
            set_up(new word_XO_UI(), new word_XO_Board());
            break;
        }
        case 3: {
            set_up(new obs_TicTacToe_UI(), new obs_TicTacToe_board());
            break;
        }
        case 4: {
            set_up(new Inverse_XO_UI(), new InverseTicTacToe<char>());
            break;
        }
        case 5: {
            set_up(new SUS_UI(), new SUS_Board());
            break;
        }
        case 6: {
            set_up(new XO_4x4_UI(), new XO_4x4_Board());
            break;
        }
        case 7: {
            set_up(new Numerical_XO_UI(), new Numerical_XO_Board());
            break;
        }
        case 8: {
            set_up(new TicTacToe_5x5_UI, new TicTacToe_5x5_board());
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
