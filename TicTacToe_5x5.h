/**
 * @file TicTacToe_5x5.h
 * @brief Header for the 5x5 Tic-Tac-Toe game variant.
 *
 * Defines classes for a 5x5 Tic-Tac-Toe game where players compete to
 * create the most three-in-a-row sequences. Winner is determined by
 * who has more sequences after the board is filled.
 */

#pragma once

#include "BoardGame_Classes.h"

/**
 * @class TicTacToe_5x5_board
 * @brief Represents a 5x5 Tic-Tac-Toe board with sequence counting.
 *
 * This variant counts three-in-a-row sequences for both players after
 * 24 moves (full board). The player with more sequences wins. For sequences
 * of length n >= 3, the score increases by (n-2).
 *
 * @see Board
 */
class TicTacToe_5x5_board : public Board<char>{
private:
    char blank_symbol = '.'; ///< Symbol representing an empty cell
    int cntX = 0; ///< Counter for player X's three-in-a-row sequences
    int cntO = 0; ///< Counter for player O's three-in-a-row sequences
    vector<string> names; ///< Stores player names for result display

public:
    /**
     * @brief Default constructor that initializes a 5x5 board.
     *
     * Sets all cells to blank and initializes sequence counters to zero.
     */
    TicTacToe_5x5_board();

    /**
     * @brief Updates the board with a player's move.
     * @param move Pointer to a Move<char> object containing move details
     * @return true if the move is valid and successfully applied, false otherwise
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if player O has won (more sequences than X).
     *
     * Calculates sequences for both players at move 24 and determines
     * if O has more. Displays the sequence counts.
     *
     * @param player Pointer to the player being checked
     * @return true if O has more sequences than X, false otherwise
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if player X has won (more sequences than O).
     *
     * Determines if X has more sequences than O at move 24.
     * Displays the sequence counts.
     *
     * @param player Pointer to the player being checked
     * @return true if X has more sequences than O, false otherwise
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if the game has ended in a draw.
     *
     * A draw occurs at move 24 when both players have equal sequences.
     * Displays the sequence counts.
     *
     * @param player Pointer to the player being checked
     * @return true if both players have equal sequences, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game is over.
     * @param player Pointer to the player to evaluate
     * @return true if the game has ended (win, draw, or lose), false otherwise
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Counts all three-in-a-row sequences for a symbol.
     *
     * Scans the board in all directions (horizontal, vertical, main diagonal,
     * anti-diagonal) and counts consecutive sequences of 3 or more cells.
     * Updates the appropriate counter (cntX or cntO) based on the symbol.
     *
     * @param symbol The player's symbol ('X' or 'O') to count sequences for
     */
    void consecutive_cells(char symbol);
};

/**
 * @class TicTacToe_5x5_UI
 * @brief User interface class for the 5x5 Tic-Tac-Toe game.
 *
 * Provides player setup and move input functionality specific to
 * the 5x5 sequence-counting variant of Tic-Tac-Toe.
 *
 * @see UI
 */
class TicTacToe_5x5_UI : public UI<char> {
public:
    /**
     * @brief Constructs a TicTacToe_5x5_UI object.
     *
     * Initializes the UI with a welcome message and board size of 5.
     */
    TicTacToe_5x5_UI();

    /**
     * @brief Destructor for TicTacToe_5x5_UI.
     */
    ~TicTacToe_5x5_UI() override = default;

    /**
     * @brief Creates a player of the specified type.
     * @param name Name of the player
     * @param symbol Character symbol assigned to the player
     * @param type The type of the player (Human or Computer)
     * @return Pointer to the newly created Player<char> instance
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Retrieves the next move from a player.
     * @param player Pointer to the player whose move is being requested
     * @return Pointer to a Move<char> object representing the player's move
     */
    Move<char>* get_move(Player<char>* player) override;
};