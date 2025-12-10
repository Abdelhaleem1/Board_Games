/**
 * @file InverseTicTacToe.h
 * @brief Implementation of Inverse (Misère) Tic-Tac-Toe game
 * @date December 2025
 *
 * This file contains the template class declaration for Inverse Tic-Tac-Toe,
 * also known as Misère Tic-Tac-Toe or Anti-Tic-Tac-Toe. This variant reverses
 * the winning condition of standard Tic-Tac-Toe: the objective is to AVOID
 * getting three in a row rather than achieving it.
 *
 * @details
 * Game Rules:
 * - Played on a standard 3x3 grid
 * - Players alternate placing their marks (X and O)
 * - A player LOSES if they complete three in a row (row, column, or diagonal)
 * - If the board fills completely with no three-in-a-row, the game is a draw
 * - Strategic play focuses on forcing your opponent into making three in a row
 */

#ifndef _INVERSE_TICTACTOE_H
#define _INVERSE_TICTACTOE_H
#include "BoardGame_Classes.h"

 /**
  * @class InverseTicTacToe
  * @brief Template class for Inverse (Misère) Tic-Tac-Toe game implementation
  *
  * @tparam T Type of the symbols used on the board (typically char)
  *
  * @brief Inverse (Misère) Tic-Tac-Toe.
  *
  * Rules implemented:
  * - Standard 3x3 board.
  * - A player loses if they complete a line (row, column, diagonal) of three of their own marks.
  * - If the board fills with no player having three-in-a-row, the game is a draw.
  *
  * Mapping to framework:
  * - `is_lose(Player*)` returns true when that player's symbol has a three-in-a-row (they lose).
  * - `is_win(Player*)` returns true when the opponent has a three-in-a-row (opponent wins).
  *
  * @details
  * This variant creates interesting strategic depth as players must:
  * - Avoid creating two-in-a-row situations that could be forced into three
  * - Try to force opponents into positions where they must complete three in a row
  * - Balance offensive and defensive play differently than standard Tic-Tac-Toe
  *
  * The inverted win/lose logic means:
  * - Making three in a row is bad (you lose)
  * - Forcing your opponent to make three in a row is good (you win)
  * - Optimal play often differs significantly from standard Tic-Tac-Toe strategy
  */
template <typename T>
class InverseTicTacToe : public Board<T> {
public:
    /**
     * @brief Constructs a new Inverse Tic-Tac-Toe board
     *
     * @param empty_cell Symbol representing empty cells (default is space character)
     *
     * @details
     * Initializes a standard 3x3 Tic-Tac-Toe board with all cells empty.
     * The board uses the same physical structure as standard Tic-Tac-Toe,
     * but with inverted win/lose conditions.
     */
    InverseTicTacToe(T empty_cell = static_cast<T>(' '))
        : Board<T>(3, 3), empty_marker(empty_cell) {
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                this->board[r][c] = empty_marker;
    }

    /**
     * @brief Virtual destructor for Inverse Tic-Tac-Toe board
     *
     * Ensures proper cleanup of derived class resources.
     */
    virtual ~InverseTicTacToe() {}

    /**
     * @brief Updates the board with a player's move
     *
     * @param move Pointer to Move object containing position (x,y) and player symbol
     * @return true if the move was valid and successfully placed; false otherwise
     *
     * @details
     * Validates and applies a move to the board. A move is valid if:
     * - Position is within the 3x3 grid boundaries (0-2 for both row and column)
     * - Target cell is currently empty
     *
     * If valid, places the symbol at the position and increments the move counter.
     *
     * @note Does not check if the move causes the player to lose (three in a row)
     * @warning Does not check for game-over conditions; use game_is_over() separately
     */
    virtual bool update_board(Move<T>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        T sym = move->get_symbol();
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) return false;
        if (this->board[x][y] != empty_marker) return false;
        this->board[x][y] = sym;
        ++this->n_moves;
        return true;
    }

    /**
     * @brief Checks if the specified player has won
     *
     * @param p Pointer to the Player object to check
     * @return true if the opponent has three in a row (player wins); false otherwise
     *
     * @details
     * In Inverse Tic-Tac-Toe, you win when your OPPONENT completes three in a row.
     * This method:
     * 1. Determines the opponent's symbol
     * 2. Checks if the opponent has three in a row
     * 3. Returns true if opponent loses (meaning this player wins)
     *
     * @note This is the inverse of standard Tic-Tac-Toe win logic
     * @see is_lose() for checking if the player has made three in a row (and lost)
     */
    virtual bool is_win(Player<T>* p) override {
        T opp = get_opponent_symbol(p);
        return symbol_has_three_in_row(opp);
    }

    /**
     * @brief Checks if the specified player has lost
     *
     * @param p Pointer to the Player object to check
     * @return true if the player has three in a row (player loses); false otherwise
     *
     * @details
     * In Inverse Tic-Tac-Toe, you lose when YOU complete three in a row.
     * This method checks if the player's symbol appears in any winning line:
     * - Any row (3 horizontal lines)
     * - Any column (3 vertical lines)
     * - Main diagonal (top-left to bottom-right)
     * - Anti-diagonal (top-right to bottom-left)
     *
     * @note This is the inverse of standard Tic-Tac-Toe lose logic
     * @note Making three in a row is the losing condition in this variant
     */
    virtual bool is_lose(Player<T>* p) override {
        T s = p->get_symbol();
        return symbol_has_three_in_row(s);
    }

    /**
     * @brief Checks if the game has ended in a draw
     *
     * @param Player object pointer (unused for validation)
     * @return true if the board is full with no three-in-a-row; false otherwise
     *
     * @details
     * A draw occurs when:
     * - All 9 cells are filled
     * - Neither player X nor player O has three in a row
     *
     * This is the only condition where neither player loses, making it a draw.
     * Unlike standard Tic-Tac-Toe where draws are common with optimal play,
     * draws in Inverse Tic-Tac-Toe require careful maneuvering to avoid
     * being forced into three in a row.
     *
     * @note Explicitly checks that neither 'X' nor 'O' has three in a row
     */
    virtual bool is_draw(Player<T>*) override {
        if (symbol_has_three_in_row(static_cast<T>('X'))) return false;
        if (symbol_has_three_in_row(static_cast<T>('O'))) return false;
        return this->n_moves >= this->rows * this->columns;
    }

    /**
     * @brief Determines if the game has concluded
     *
     * @param p Pointer to the Player object to check against
     * @return true if the game is over (win, lose, or draw); false if play continues
     *
     * @details
     * Checks all end-game conditions:
     * - Has the player won? (opponent made three in a row)
     * - Has the player lost? (player made three in a row)
     * - Is the game a draw? (board full, no three in a row)
     *
     * @note Should be called after each move to determine if gameplay should end
     */
    virtual bool game_is_over(Player<T>* p) override {
        return is_win(p) || is_lose(p) || is_draw(p);
    }

private:
    T empty_marker;  ///< Symbol representing empty cells on the board

    /**
     * @brief Checks if a specific symbol has three in a row
     *
     * @param sym The symbol to check for
     * @return true if the symbol has three in a row in any direction; false otherwise
     *
     * @details
     * Scans all possible winning lines for the specified symbol:
     * - Three rows (horizontal lines)
     * - Three columns (vertical lines)
     * - Main diagonal (top-left to bottom-right)
     * - Anti-diagonal (top-right to bottom-left)
     *
     * Returns false immediately if sym is the empty marker (can't have three in a row).
     *
     * @note This is a helper method used by both is_win() and is_lose()
     * @note Used to check if a player has lost (their own symbol) or won (opponent's symbol)
     */
    bool symbol_has_three_in_row(T sym) const {
        if (sym == empty_marker) return false;
        for (int r = 0; r < 3; ++r)
            if (this->board[r][0] == sym && this->board[r][1] == sym && this->board[r][2] == sym)
                return true;
        for (int c = 0; c < 3; ++c)
            if (this->board[0][c] == sym && this->board[1][c] == sym && this->board[2][c] == sym)
                return true;
        if (this->board[0][0] == sym && this->board[1][1] == sym && this->board[2][2] == sym) return true;
        if (this->board[0][2] == sym && this->board[1][1] == sym && this->board[2][0] == sym) return true;
        return false;
    }

    /**
     * @brief Determines the opponent's symbol
     *
     * @param p Pointer to the Player object whose opponent to find
     * @return The opponent's symbol (type T)
     *
     * @details
     * Attempts to find the opponent's symbol by:
     * 1. Scanning the board for a symbol that is neither the player's symbol nor empty
     * 2. If no opponent symbol found on board, assumes standard X/O setup:
     *    - If player is 'X', opponent is 'O'
     *    - Otherwise, opponent is 'X'
     *
     * This method is robust and works even early in the game when the opponent
     * hasn't placed any pieces yet.
     *
     * @note Assumes a two-player game with symbols 'X' and 'O' as fallback
     * @note Scans entire board, so has O(n²) complexity (9 cells for 3x3)
     */
    T get_opponent_symbol(Player<T>* p) const {
        T s = p->get_symbol();
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c) {
                T cand = this->board[r][c];
                if (cand != s && cand != empty_marker) return cand;
            }
        if (s == static_cast<T>('X')) return static_cast<T>('O');
        return static_cast<T>('X');
    }
};
#endif