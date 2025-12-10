/**
 * @file SUS.h
 * @brief Header file for SUS game implementation
 * @date [December 2025]
 *
 * This file contains the class declarations for the SUS board game,
 * including the game board logic and user interface components.
 * Players compete to form the word "SUS" on the board.
 */

#ifndef SUS_H
#define SUS_H
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class SUS_Board
 * @brief Represents the game board for the SUS game
 *
 * This class manages the SUS game board state, tracking player scores
 * as they form the word "SUS" horizontally, vertically, or diagonally.
 */
class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.';  ///< Symbol used to represent empty cells on the board
    int last_row_play = 0;    ///< Row coordinate of the last played move
    int last_col_play = 0;    ///< Column coordinate of the last played move
    int count1 = 0;           ///< Score counter for player 1
    int count2 = 0;           ///< Score counter for player 2

public:
    /**
     * @brief Default constructor for SUS_Board
     *
     * Initializes a new SUS game board with default dimensions and state.
     */
    SUS_Board();

    /**
     * @brief Updates the board with a player's move
     * @param move_ptr Pointer to the Move object containing move details
     * @return true if the move was successfully applied, false otherwise
     *
     * Places the player's letter (S or U) on the board and checks for "SUS" formations.
     */
    bool update_board(Move<char>* move_ptr) override;

    /**
     * @brief Checks if the specified player has won the game
     * @param player Pointer to the Player object to check for win condition
     * @return true if the player has the highest score and game is over, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the specified player has lost the game
     * @param player Pointer to the Player object to check for lose condition
     * @return true if the player has a lower score when game ends, false otherwise
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if the game ended in a draw
     * @param player Pointer to the Player object (used for context)
     * @return true if both players have equal scores at game end, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Checks if the game has ended
     * @param player Pointer to the Player object to check game status
     * @return true if the board is full, false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Checks for "SUS" formations after a move
     * @param x Row coordinate to check from
     * @param y Column coordinate to check from
     * @param symbol The symbol that was just placed
     *
     * Scans all directions from the given position to find complete "SUS" words
     * and updates the appropriate player's score.
     */
    void condition(int x, int y, char symbol);
};

/**
 * @class SUS_UI
 * @brief User interface handler for SUS game
 *
 * This class manages all user interactions for the SUS game,
 * including player setup and move input.
 */
class SUS_UI : public UI<char> {
public:
    /**
     * @brief Constructor for SUS_UI
     *
     * Initializes the UI with a welcome message and player count (3).
     */
    SUS_UI() : UI<char>("Weclome to SUS Game", 3) {}

    /**
     * @brief Destructor for SUS_UI
     */
    ~SUS_UI() {};

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
     * @param symbol Character symbol representing the player (S or U)
     * @param type Type of player (human, AI, etc.)
     * @return Pointer to the newly created Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Gets a move from the specified player
     * @param player Pointer to the Player making the move
     * @return Pointer to a Move object containing the player's chosen move
     *
     * Prompts the player for their move (position and letter S or U) and validates input.
     */
    Move<char>* get_move(Player<char>* player) override;
};
#endif