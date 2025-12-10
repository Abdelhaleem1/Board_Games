/**
 * @file obs_TicTacToe.h
 * @brief Header for the Obstacles Tic-Tac-Toe game variant.
 *
 * Defines classes for a 6x6 Tic-Tac-Toe game where random obstacles
 * are placed after each move, and players must achieve four in a row to win.
 */

#pragma once
#include "BoardGame_Classes.h"

/**
 * @class obs_TicTacToe_board
 * @brief Represents a 6x6 Tic-Tac-Toe board with dynamic obstacles.
 *
 * This board variant places two random obstacles after each player move.
 * Victory is achieved by placing four symbols consecutively in any direction
 * (horizontal, vertical, or diagonal). Obstacles block cell usage.
 *
 * @see Board
 */
class obs_TicTacToe_board : public Board<char>{
private:
    char blank_symbol = '.'; ///< Symbol representing an empty cell
    char obstacle_symbol = '#'; ///< Symbol representing an obstacle
    vector<pair<int,int>> coordinates; ///< List of available coordinates for obstacle placement
    int last_row_play; ///< Row index of the most recent move
    int last_col_play; ///< Column index of the most recent move

public:
    /**
     * @brief Default constructor that initializes a 6x6 board.
     *
     * Sets up blank cells and populates the coordinates list with all positions.
     */
    obs_TicTacToe_board();

    /**
     * @brief Updates the board with a player's move and places obstacles.
     * @param move Pointer to a Move<char> object containing move details
     * @return true if the move is valid and successfully applied, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if the player has achieved four in a row.
     * @param player Pointer to the player being checked
     * @return true if the player has four consecutive symbols, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the player has lost (not used in this variant).
     * @param player Pointer to the player being checked
     * @return Always returns false
     */
    bool is_lose(Player<char>* player) override { return false; };

    /**
     * @brief Checks if the game has ended in a draw.
     * @param player Pointer to the player being checked
     * @return true if the board is full and no winner, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game is over.
     * @param player Pointer to the player to evaluate
     * @return true if the game has ended (win or draw), false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Places two random obstacles on available cells.
     *
     * Selects random positions from the coordinates list and marks them
     * with the obstacle symbol, then removes them from available positions.
     */
    void random_obs();

    /**
     * @brief Counts consecutive matching symbols in a direction.
     * @param x Starting row position
     * @param y Starting column position
     * @param dr Row direction increment (-1, 0, or 1)
     * @param dc Column direction increment (-1, 0, or 1)
     * @param sym Symbol to count
     * @return Number of consecutive matching symbols
     */
    int dir_cnt(int x, int y, int dr, int dc, char sym);

    /**
     * @brief Checks if all cells on the board are filled.
     * @return true if no blank cells remain, false otherwise
     */
    bool isFull();
};

/**
 * @class obs_TicTacToe_UI
 * @brief User interface class for the Obstacles Tic-Tac-Toe game.
 *
 * Provides player setup and move input functionality specific to
 * the obstacles variant of Tic-Tac-Toe.
 *
 * @see UI
 */
class obs_TicTacToe_UI : public UI<char> {
public:
    /**
     * @brief Constructs an obs_TicTacToe_UI object.
     *
     * Initializes the UI with a welcome message and board size of 6.
     */
    obs_TicTacToe_UI();

    /**
     * @brief Destructor for obs_TicTacToe_UI.
     */
    ~obs_TicTacToe_UI() {};

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player
     * @param symbol Character symbol assigned to the player
     * @param type The type of the player (Human or Computer)
     * @return Pointer to the newly created Player<char> instance
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested
     * @return Pointer to a Move<char> object representing the player's move
     */
    virtual Move<char>* get_move(Player<char>* player);
};