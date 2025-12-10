/**
 * @file DiamondTicTacToe.h
 * @brief Implementation of Diamond Tic-Tac-Toe game on a 5x5 grid
 * @date December 2025
 *
 * This file contains the template class declaration for Diamond Tic-Tac-Toe,
 * a variant where the playing field is diamond-shaped within a 5x5 grid.
 * Valid cells form a diamond pattern based on Manhattan distance from center.
 *
 * @details
 * The game uses a unique winning condition: a player must simultaneously have
 * at least one complete line of length 3 AND one complete line of length 4,
 * where these lines are in different directions (horizontal, vertical, or diagonal).
 */

#ifndef _DIAMOND_TICTACTOE_H
#define _DIAMOND_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
#include <cmath>

 /**
  * @class DiamondTicTacToe
  * @brief Template class for Diamond Tic-Tac-Toe game implementation
  *
  * @tparam T Type of the symbols used on the board (typically char)
  *
  * Diamond Tic-Tac-Toe played on a 5x5 grid where valid cells form a diamond:
  *        abs(r - 2) + abs(c - 2) <= 2
  *
  * Winning condition:
  * - A player wins if they simultaneously have at least one full line of length 3
  *   and at least one full line of length 4, and the two lines are in different
  *   directions (horizontal, vertical, main-diagonal, anti-diagonal). The lines
  *   may share a single common cell.
  *
  * @details
  * The diamond shape is centered at position (2,2) on the 5x5 grid with radius 2.
  * Valid cells are determined by Manhattan distance: |row - 2| + |col - 2| <= 2.
  * This creates a total of 13 valid cells in a diamond pattern.
  *
  * Game features:
  * - Players must form lines in different directions to win
  * - Lines can share up to one common cell
  * - Both 3-length and 4-length lines must be complete
  * - Invalid cells outside the diamond cannot be played
  */
template <typename T>
class DiamondTicTacToe : public Board<T> {
public:
    /**
     * @brief Constructs a new Diamond Tic-Tac-Toe board
     *
     * @param empty_cell Symbol representing empty cells (default is space character)
     *
     * @details
     * Initializes a 5x5 grid where only diamond-shaped cells are valid for play.
     * The constructor:
     * - Sets all cells to the empty marker
     * - Counts the number of valid cells (13 in diamond pattern)
     * - Precomputes all possible winning lines of length 3 and 4
     *
     * @note The diamond is centered at (2,2) with Manhattan distance radius of 2
     */
    DiamondTicTacToe(T empty_cell = static_cast<T>(' ')) :
        Board<T>(5, 5), empty_marker(empty_cell) {
        valid_cell_count = 0;
        for (int r = 0; r < this->rows; ++r) {
            for (int c = 0; c < this->columns; ++c) {
                this->board[r][c] = empty_marker;
                if (is_valid_cell(r, c)) {
                    ++valid_cell_count;
                }
            }
        }
        precompute_lines();
    }

    /**
     * @brief Virtual destructor for Diamond Tic-Tac-Toe board
     *
     * Ensures proper cleanup of derived class resources.
     */
    virtual ~DiamondTicTacToe() {}

    /**
     * @brief Updates the board with a player's move
     *
     * @param move Pointer to Move object containing position (x,y) and player symbol
     * @return true if the move was valid and successfully placed; false otherwise
     *
     * @details
     * Validates and applies a move to the board. A move is valid if:
     * - Position is within 5x5 grid boundaries
     * - Position is a valid cell within the diamond shape
     * - Target cell is currently empty
     *
     * If valid, places the symbol and increments move counter.
     *
     * @note Invalid cells outside the diamond pattern will be rejected
     * @warning Does not check for game-over conditions
     */
    virtual bool update_board(Move<T>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        T sym = move->get_symbol();

        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) return false;
        if (!is_valid_cell(x, y)) return false;
        if (this->board[x][y] != empty_marker) return false;

        this->board[x][y] = sym;
        ++this->n_moves;
        return true;
    }

    /**
     * @brief Checks if the specified player has won
     *
     * @param p Pointer to the Player object to check
     * @return true if player has both a 3-line and 4-line in different directions; false otherwise
     *
     * @details
     * A player wins by simultaneously achieving:
     * 1. At least one complete line of length 3
     * 2. At least one complete line of length 4
     * 3. These lines must be in different directions (horizontal, vertical, main diagonal, anti diagonal)
     *
     * The algorithm:
     * - Scans all precomputed 3-length lines for player's symbol
     * - Scans all precomputed 4-length lines for player's symbol
     * - Checks if any 3-line direction differs from any 4-line direction
     *
     * @note Lines may share up to one common cell
     * @note Directions are: 0=horizontal, 1=vertical, 2=main diagonal, 3=anti diagonal
     */
    virtual bool is_win(Player<T>* p) override {
        T sym = p->get_symbol();
        std::vector<int> three_dirs;
        std::vector<int> four_dirs;

        for (size_t i = 0; i < lines3.size(); ++i) {
            if (line_all_symbol(lines3[i].coords, sym)) three_dirs.push_back(lines3[i].dir);
        }
        for (size_t i = 0; i < lines4.size(); ++i) {
            if (line_all_symbol(lines4[i].coords, sym)) four_dirs.push_back(lines4[i].dir);
        }

        for (int d3 : three_dirs)
            for (int d4 : four_dirs)
                if (d3 != d4) return true;

        return false;
    }

    /**
     * @brief Checks if the specified player has lost
     *
     * @param Player object pointer (unused)
     * @return Always returns false
     *
     * @details
     * In Diamond Tic-Tac-Toe, there is no explicit lose condition.
     * A player loses only when their opponent wins, which is checked
     * separately through is_win() for the other player.
     */
    virtual bool is_lose(Player<T>*) override {
        return false;
    }

    /**
     * @brief Checks if the game has ended in a draw
     *
     * @param Player object pointer (unused for validation)
     * @return true if all valid cells are filled with no winner; false otherwise
     *
     * @details
     * A draw occurs when:
     * - All 13 valid cells in the diamond are filled
     * - Neither player X nor player O has satisfied the winning condition
     *
     * The method explicitly checks that neither 'X' nor 'O' has won
     * to ensure the draw is legitimate.
     */
    virtual bool is_draw(Player<T>*) override {
        if (this->n_moves < valid_cell_count) return false;
        if (symbol_has_win(static_cast<T>('X'))) return false;
        if (symbol_has_win(static_cast<T>('O'))) return false;
        return true;
    }

    /**
     * @brief Determines if the game has concluded
     *
     * @param p Pointer to the Player object to check against
     * @return true if the game is over (win, lose, or draw); false if play continues
     *
     * @details
     * Checks all end-game conditions by evaluating:
     * - Has the player won?
     * - Has the player lost?
     * - Is the game a draw?
     *
     * @note Should be called after each move to check game status
     */
    virtual bool game_is_over(Player<T>* p) override {
        return is_win(p) || is_lose(p) || is_draw(p);
    }

private:
    /**
     * @struct LineInfo
     * @brief Structure to store information about a potential winning line
     *
     * @details
     * Contains:
     * - coords: Vector of (row, col) pairs representing cells in the line
     * - dir: Direction identifier (0=horizontal, 1=vertical, 2=main diagonal, 3=anti diagonal)
     */
     // Direction identifiers
     // 0 = horizontal, 1 = vertical, 2 = main diagonal (TL-BR), 3 = anti diagonal (TR-BL)
    struct LineInfo { std::vector<std::pair<int, int>> coords; int dir; };

    T empty_marker;                    ///< Symbol representing empty cells
    int valid_cell_count;              ///< Total number of valid cells in diamond (13)
    std::vector<LineInfo> lines3;      ///< Precomputed list of all valid 3-length lines
    std::vector<LineInfo> lines4;      ///< Precomputed list of all valid 4-length lines

    /**
     * @brief Checks if a cell position is valid within the diamond shape
     *
     * @param r Row index (0-4)
     * @param c Column index (0-4)
     * @return true if cell is within the diamond; false otherwise
     *
     * @details
     * Uses Manhattan distance from center (2,2):
     * Valid if |row - 2| + |col - 2| <= 2
     *
     * This creates a diamond pattern with 13 valid cells.
     */
    bool is_valid_cell(int r, int c) const {
        // Diamond condition centered at (2,2) with radius 2
        return (std::abs(r - 2) + std::abs(c - 2)) <= 2;
    }

    /**
     * @brief Precomputes all possible winning lines of length 3 and 4
     *
     * @details
     * Scans the entire grid in four directions (horizontal, vertical,
     * main diagonal, anti diagonal) to find all valid consecutive lines
     * that:
     * - Consist only of valid diamond cells
     * - Are exactly 3 or 4 cells long
     *
     * Results are stored in lines3 and lines4 vectors.
     * Duplicates are removed to optimize win-checking performance.
     *
     * @note Called once during construction
     * @see deduplicate_lines()
     */
    void precompute_lines() {
        // directions as (dr, dc) with dir id
        const std::vector<std::pair<int, int>> dirs = {
            {0, 1},  // horizontal -> dir 0
            {1, 0},  // vertical   -> dir 1
            {1, 1},  // main diag  -> dir 2
            {1, -1}  // anti diag  -> dir 3
        };

        for (int r = 0; r < this->rows; ++r) {
            for (int c = 0; c < this->columns; ++c) {
                if (!is_valid_cell(r, c)) continue;
                for (int d = 0; d < (int)dirs.size(); ++d) {
                    std::vector<std::pair<int, int>> coords3;
                    bool ok3 = true;
                    for (int k = 0; k < 3; ++k) {
                        int rr = r + k * dirs[d].first;
                        int cc = c + k * dirs[d].second;
                        if (rr < 0 || rr >= this->rows || cc < 0 || cc >= this->columns || !is_valid_cell(rr, cc)) {
                            ok3 = false;
                            break;
                        }
                        coords3.emplace_back(rr, cc);
                    }
                    if (ok3) lines3.push_back({ coords3, d });

                    std::vector<std::pair<int, int>> coords4;
                    bool ok4 = true;
                    for (int k = 0; k < 4; ++k) {
                        int rr = r + k * dirs[d].first;
                        int cc = c + k * dirs[d].second;
                        if (rr < 0 || rr >= this->rows || cc < 0 || cc >= this->columns || !is_valid_cell(rr, cc)) {
                            ok4 = false;
                            break;
                        }
                        coords4.emplace_back(rr, cc);
                    }
                    if (ok4) lines4.push_back({ coords4, d });
                }
            }
        }
        deduplicate_lines(lines3);
        deduplicate_lines(lines4);
    }

    /**
     * @brief Removes duplicate line entries from a vector
     *
     * @param lines Reference to vector of LineInfo structures to deduplicate
     *
     * @details
     * Compares each line's coordinates and direction to find duplicates.
     * Keeps only the first occurrence of each unique line.
     * This optimization reduces redundant win-checking operations.
     *
     * @note Modifies the input vector in place
     */
    static void deduplicate_lines(std::vector<LineInfo>& lines) {
        std::vector<LineInfo> out;
        for (auto& li : lines) {
            bool found = false;
            for (auto& ex : out) {
                if (ex.coords == li.coords && ex.dir == li.dir) { found = true; break; }
            }
            if (!found) out.push_back(li);
        }
        lines.swap(out);
    }

    /**
     * @brief Checks if all cells in a line contain the specified symbol
     *
     * @param coords Vector of (row, col) coordinate pairs representing the line
     * @param sym The symbol to check for
     * @return true if all cells contain the symbol; false if any cell differs
     *
     * @details
     * Helper method used by win-checking logic to verify if a line
     * is completely filled with one player's symbol.
     */
    bool line_all_symbol(const std::vector<std::pair<int, int>>& coords, T sym) const {
        for (auto& p : coords) {
            if (this->board[p.first][p.second] != sym) return false;
        }
        return true;
    }

    /**
     * @brief Checks if a specific symbol has achieved the winning condition
     *
     * @param sym The symbol to check (typically 'X' or 'O')
     * @return true if symbol has both 3-line and 4-line in different directions; false otherwise
     *
     * @details
     * Internal helper method that performs the same win-checking logic as is_win()
     * but for an arbitrary symbol rather than a Player object.
     *
     * Used by is_draw() to verify neither player has won when checking for draw condition.
     *
     * @see is_win()
     */
    bool symbol_has_win(T sym) const {

        std::vector<int> three_dirs;
        std::vector<int> four_dirs;

        for (const auto& li : lines3) {
            if (line_all_symbol(li.coords, sym)) three_dirs.push_back(li.dir);
        }
        for (const auto& li : lines4) {
            if (line_all_symbol(li.coords, sym)) four_dirs.push_back(li.dir);
        }
        for (int d3 : three_dirs)
            for (int d4 : four_dirs)
                if (d3 != d4) return true;
        return false;
    }
};

#endif