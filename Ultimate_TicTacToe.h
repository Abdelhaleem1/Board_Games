/**
 * @file UltimateTicTacToe.h
 * @brief Implementation of Ultimate Tic-Tac-Toe game
 * @date December 2025
 *
 * This file contains the template class declaration for Ultimate Tic-Tac-Toe,
 * an advanced variant consisting of a 3x3 grid of standard Tic-Tac-Toe boards.
 * Players must win small boards to claim positions in the larger meta-game.
 *
 * @details
 * Game Structure:
 * - Underlying board is 9x9 (physically representing 3x3 of 3x3 sub-boards)
 * - A separate 3x3 "winners" grid tracks which player claimed each small board
 * - Win by getting three small boards in a row on the meta-level
 *
 * Game Rules:
 * - Players alternate placing marks in any available cell
 * - Winning a small 3x3 board claims that position in the meta-board
 * - If a small board fills without a winner, it's marked as a draw
 * - Win the game by getting three small boards in a row (horizontally, vertically, or diagonally)
 *
 * Coordinate System:
 * - All moves use global coordinates [0-8] for both row and column
 * - Small board position calculated as (row/3, col/3)
 * - Cell within small board calculated as (row%3, col%3)
 */

#ifndef _ULTIMATE_TICTACTOE_H
#define _ULTIMATE_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>

 /**
  * @class UltimateTicTacToe
  * @brief Template class for Ultimate Tic-Tac-Toe game implementation
  *
  * @tparam T Type of the symbols used on the board (typically char)
  *
  * Ultimate Tic-Tac-Toe implemented as a 9x9 underlying board (3x3 of 3x3 sub-boards).
  * - Underlying Board (Board<T>) size = 9 x 9 (rows, columns)
  * - A separate 3x3 `winners` grid tracks which player (if any) has claimed each small board.
  *
  * Move coordinates are global: row and column are in range [0..8].
  *
  * @details
  * The game maintains two data structures:
  * 1. A 9x9 board storing individual cell marks
  * 2. A 3x3 winners grid tracking small board outcomes
  *
  * Strategic depth comes from the meta-game layer:
  * - Players must balance local (small board) and global (meta-board) strategy
  * - Claiming key small boards controls the meta-game
  * - Small board draws ('D') block that meta-position
  *
  * Small Board Positions (0-8):
  * @code
  *   0 | 1 | 2
  *  -----------
  *   3 | 4 | 5
  *  -----------
  *   6 | 7 | 8
  * @endcode
  *
  * Each small board internally is a standard 3x3 Tic-Tac-Toe grid.
  */
template <typename T>
class UltimateTicTacToe : public Board<T> {
public:
    /**
     * @brief Constructs a new Ultimate Tic-Tac-Toe board
     *
     * @param empty_cell Symbol representing empty cells (default is space character)
     *
     * @details
     * Initializes the game with:
     * - A 9x9 main board filled with empty markers
     * - A 3x3 winners grid initialized to empty
     * - Move counter set to zero
     *
     * The board is ready for play immediately after construction,
     * with all 81 cells available for moves.
     */
    UltimateTicTacToe(T empty_cell = static_cast<T>(' '))
        : Board<T>(9, 9), empty_marker(empty_cell) {

        for (int r = 0; r < this->rows; ++r)
            for (int c = 0; c < this->columns; ++c)
                this->board[r][c] = empty_marker;

        winners.assign(3, std::vector<T>(3, empty_marker));
    }

    /**
     * @brief Virtual destructor for Ultimate Tic-Tac-Toe board
     *
     * Ensures proper cleanup of derived class resources.
     */
    virtual ~UltimateTicTacToe() {}

    /**
     * @brief Updates the board with a player's move
     *
     * @param move Pointer to Move object containing global position (0-8, 0-8) and symbol
     * @return true if the move was valid and successfully placed; false otherwise
     *
     * @details
     * Validates and applies a move with the following checks:
     * 1. Position is within 9x9 grid boundaries
     * 2. Target cell is currently empty
     * 3. The small board containing the cell hasn't been won or drawn yet
     *
     * After placing the move:
     * - Checks if the small board now has a winner
     * - If winner found, updates the winners grid
     * - If no winner and small board is full, marks it as draw ('D')
     * - Increments the move counter
     *
     * @note Moves to already-won small boards are rejected
     * @note Small board position calculated as (row/3, col/3)
     * @warning Does not implement "send to" rule (where last move determines next board)
     */
    virtual bool update_board(Move<T>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        T sym = move->get_symbol();

        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) return false;
        if (this->board[x][y] != empty_marker) return false;

        int br = x / 3;
        int bc = y / 3;


        if (winners[br][bc] != empty_marker) return false;


        this->board[x][y] = sym;
        ++this->n_moves;

        if (check_and_set_small_winner(br, bc)) {

        }
        else {

            if (small_board_full(br, bc)) {
                winners[br][bc] = draw_marker();
            }
        }

        return true;
    }

    /**
     * @brief Checks if the specified player has won
     *
     * @param p Pointer to the Player object to check
     * @return true if player has three small boards in a row on meta-level; false otherwise
     *
     * @details
     * A player wins by claiming three small boards in a row in the 3x3 winners grid:
     * - Any horizontal row of three small boards
     * - Any vertical column of three small boards
     * - Either diagonal (main or anti) of three small boards
     *
     * Only considers the player's actual symbol; draws ('D') don't count as wins.
     *
     * @note This is the meta-game win condition, not individual small board wins
     */
    virtual bool is_win(Player<T>* p) override {
        T s = p->get_symbol();
        return three_in_row_winners(s);
    }

    /**
     * @brief Checks if the specified player has lost
     *
     * @param p Pointer to the Player object to check
     * @return true if opponent has three small boards in a row; false otherwise
     *
     * @details
     * In Ultimate Tic-Tac-Toe, a player loses when their opponent wins
     * by claiming three small boards in a row on the meta-level.
     *
     * Determines the opponent's symbol and checks if they have won.
     */
    virtual bool is_lose(Player<T>* p) override {
        T opp = get_opponent_symbol(p);
        return three_in_row_winners(opp);
    }

    /**
     * @brief Checks if the game has ended in a draw
     *
     * @param Player object pointer (unused for validation)
     * @return true if all small boards are decided with no meta-winner; false otherwise
     *
     * @details
     * A draw occurs when:
     * - All 9 small boards are either won by a player or drawn
     * - Neither player has achieved three small boards in a row
     *
     * The winners grid will be completely filled (no empty markers),
     * but no player has a winning line on the meta-level.
     *
     * @note Small boards marked as 'D' (draw) count as decided boards
     * @note Explicitly checks that neither 'X' nor 'O' has won
     */
    virtual bool is_draw(Player<T>*) override {

        if (three_in_row_winners(static_cast<T>('X'))) return false;
        if (three_in_row_winners(static_cast<T>('O'))) return false;


        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                if (winners[r][c] == empty_marker) return false;

        return true;
    }

    /**
     * @brief Determines if the game has concluded
     *
     * @param p Pointer to the Player object to check against
     * @return true if the game is over (win, lose, or draw); false if play continues
     *
     * @details
     * Checks all end-game conditions:
     * - Has the player won? (three small boards in a row)
     * - Has the player lost? (opponent has three small boards in a row)
     * - Is it a draw? (all small boards decided, no meta-winner)
     *
     * @note Should be called after each move to determine if gameplay should end
     */
    virtual bool game_is_over(Player<T>* p) override {
        return is_win(p) || is_lose(p) || is_draw(p);
    }

private:
    std::vector<std::vector<T>> winners;  ///< 3x3 grid tracking small board winners (player symbol or 'D' for draw)
    T empty_marker;                       ///< Symbol representing empty cells

    /**
     * @brief Returns the symbol used to mark drawn small boards
     *
     * @return Character 'D' cast to type T
     *
     * @details
     * When a small board fills completely without a winner,
     * it's marked as 'D' in the winners grid to indicate a draw.
     * This blocks that position from contributing to either player's win.
     */
    T draw_marker() const { return static_cast<T>('D'); }

    /**
     * @brief Checks if a small board has a winner and updates winners grid
     *
     * @param br Small board row index (0-2)
     * @param bc Small board column index (0-2)
     * @return true if a winner was found and set; false otherwise
     *
     * @details
     * Examines the specified 3x3 small board for winning patterns:
     * - Three horizontal rows
     * - Three vertical columns
     * - Main diagonal (top-left to bottom-right)
     * - Anti-diagonal (top-right to bottom-left)
     *
     * If a winner is found:
     * - Updates winners[br][bc] with the winning symbol
     * - Returns true
     *
     * The small board's global coordinates range from:
     * - Row: [br*3, br*3+2]
     * - Col: [bc*3, bc*3+2]
     *
     * @note Only checks the specific small board indicated by (br, bc)
     * @note Called automatically after each move to that small board
     */
    bool check_and_set_small_winner(int br, int bc) {
        int base_r = br * 3;
        int base_c = bc * 3;

        for (int r = 0; r < 3; ++r) {
            T a = this->board[base_r + r][base_c + 0];
            if (a != empty_marker && a == this->board[base_r + r][base_c + 1] && a == this->board[base_r + r][base_c + 2]) {
                winners[br][bc] = a;
                return true;
            }
        }

        for (int c = 0; c < 3; ++c) {
            T a = this->board[base_r + 0][base_c + c];
            if (a != empty_marker && a == this->board[base_r + 1][base_c + c] && a == this->board[base_r + 2][base_c + c]) {
                winners[br][bc] = a;
                return true;
            }
        }

        T d1 = this->board[base_r + 0][base_c + 0];
        if (d1 != empty_marker && d1 == this->board[base_r + 1][base_c + 1] && d1 == this->board[base_r + 2][base_c + 2]) {
            winners[br][bc] = d1;
            return true;
        }
        T d2 = this->board[base_r + 0][base_c + 2];
        if (d2 != empty_marker && d2 == this->board[base_r + 1][base_c + 1] && d2 == this->board[base_r + 2][base_c + 0]) {
            winners[br][bc] = d2;
            return true;
        }

        return false;
    }

    /**
     * @brief Checks if a small board is completely filled
     *
     * @param br Small board row index (0-2)
     * @param bc Small board column index (0-2)
     * @return true if all 9 cells in the small board are non-empty; false otherwise
     *
     * @details
     * Scans all 9 cells of the specified small board to determine if it's full.
     * A full small board with no winner should be marked as a draw.
     *
     * Used to detect when a small board should be marked as 'D' (draw)
     * in the winners grid.
     *
     * @note Called after checking for a winner
     * @note A full board without a winner results in a draw marker
     */
    bool small_board_full(int br, int bc) const {
        int base_r = br * 3;
        int base_c = bc * 3;
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                if (this->board[base_r + r][base_c + c] == empty_marker)
                    return false;
        return true;
    }

    /**
     * @brief Checks if a symbol has three in a row in the winners grid
     *
     * @param s The symbol to check for (typically 'X' or 'O')
     * @return true if symbol has three in a row in winners grid; false otherwise
     *
     * @details
     * Checks the 3x3 winners grid for three consecutive positions with the symbol:
     * - Three rows
     * - Three columns
     * - Two diagonals
     *
     * This is the meta-game win condition - winning three small boards in a line.
     *
     * Returns false immediately if symbol is draw marker ('D') or empty marker,
     * as these cannot contribute to a win.
     *
     * @note This checks the meta-level, not individual small boards
     * @note Used by both is_win() and is_draw() methods
     */
    bool three_in_row_winners(T s) const {
        if (s == draw_marker() || s == empty_marker) return false;
        for (int r = 0; r < 3; ++r)

            if (winners[r][0] == s && winners[r][1] == s && winners[r][2] == s)
                return true;

        for (int c = 0; c < 3; ++c)
            if (winners[0][c] == s && winners[1][c] == s && winners[2][c] == s)
                return true;

        if (winners[0][0] == s && winners[1][1] == s && winners[2][2] == s) return true;
        if (winners[0][2] == s && winners[1][1] == s && winners[2][0] == s) return true;

        return false;
    }

    /**
     * @brief Determines the opponent's symbol
     *
     * @param p Pointer to the Player object whose opponent to find
     * @return The opponent's symbol (type T)
     *
     * @details
     * Uses a simple two-player assumption:
     * - If player is 'X', opponent is 'O'
     * - Otherwise, opponent is 'X'
     *
     * This is used to check if the player has lost (opponent has won).
     *
     * @note Assumes standard two-player game with 'X' and 'O' symbols
     */
    T get_opponent_symbol(Player<T>* p) const {
        T s = p->get_symbol();
        if (s == static_cast<T>('X')) return static_cast<T>('O');
        return static_cast<T>('X');
    }
};

#endif