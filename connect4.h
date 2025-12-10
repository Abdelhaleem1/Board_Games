/**
 * @file CONNECT_Board.h
 * @brief Header file for Connect 4 game implementation
 * @date [December 2025]
 *
 * This file contains the class declarations for the Connect 4 board game,
 * including the game board logic and user interface components.
 */

#pragma once
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class CONNECT_Board
 * @brief Represents the game board for Connect 4
 *
 * This class manages the Connect 4 game board state, updates, and win conditions.
 * It inherits from the Board template class with char type for board symbols.
 */
class CONNECT_Board : public Board<char> {
private:
    char blank_symbol = '.';  ///< Symbol used to represent empty cells on the board

public:
    /**
     * @brief Default constructor for CONNECT_Board
     *
     * Initializes a new Connect 4 game board with default dimensions and state.
     */
    CONNECT_Board();

    /**
     * @brief Updates the board with a player's move
     * @param move_ptr Pointer to the Move object containing move details
     * @return true if the move was successfully applied, false otherwise
     *
     * Applies the specified move to the board, handling gravity (pieces fall down).
     */
    bool update_board(Move<char>* move_ptr) override;

    /**
     * @brief Checks if the specified player has won the game
     * @param player Pointer to the Player object to check for win condition
     * @return true if the player has connected 4 pieces in a row, false otherwise
     *
     * Checks horizontal, vertical, and diagonal connections.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the specified player has lost the game
     * @param player Pointer to the Player object to check for lose condition
     * @return true if the player has lost, false otherwise
     *
     * In Connect 4, this typically returns false as there's no lose condition.
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if the game ended in a draw
     * @param player Pointer to the Player object (used for context)
     * @return true if the board is full with no winner, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game has ended
     * @param player Pointer to the Player object to check game status
     * @return true if the game is over (win or draw), false otherwise
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class CONNECT_UI
 * @brief User interface handler for Connect 4 game
 *
 * This class manages all user interactions for the Connect 4 game,
 * including player setup and move input.
 */
class CONNECT_UI : public UI<char> {
public:
    /**
     * @brief Constructor for CONNECT_UI
     *
     * Initializes the UI with a welcome message and player count (3).
     */
    CONNECT_UI() : UI<char>("Weclome to Connect 4 Game", 3) {}

    /**
     * @brief Destructor for CONNECT_UI
     */
    ~CONNECT_UI() {};

    /**
     * @brief Sets up the players for the game
     * @return Array of pointers to Player objects
     *
     * Prompts for player information and creates Player objects.
     */
    Player<char>** setup_players() override;

    /**
     * @brief Creates a single player object
     * @param name Reference to the player's name string
     * @param symbol Character symbol representing the player's pieces
     * @param type Type of player (human, AI, etc.)
     * @return Pointer to the newly created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from the specified player
     * @param player Pointer to the Player making the move
     * @return Pointer to a Move object containing the player's chosen move
     *
     * Prompts the player for their move and validates the input.
     */
    Move<char>* get_move(Player<char>* player) override;
};