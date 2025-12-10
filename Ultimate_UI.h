/**
 * @file Ultimate_UI.h
 * @brief User interface implementation for Ultimate Tic-Tac-Toe game
 * @date December 2025
 *
 * This file contains the UI class declaration for Ultimate Tic-Tac-Toe,
 * handling the display of the complex 9x9 board structure and collecting
 * player moves using global coordinates.
 *
 * @details
 * The UI provides specialized visualization for Ultimate Tic-Tac-Toe:
 * - Displays the full 9x9 grid with visual separators between small boards
 * - Uses heavier dividers every 3 rows/columns to show the 3x3 meta-structure
 * - Accepts moves in global coordinates [0-8] for both row and column
 * - Converts space characters to dots for better visibility
 *
 * The display clearly shows the relationship between the 9 small 3x3 boards
 * and the overall game structure, making it easier for players to understand
 * which small board they're playing in.
 */

#ifndef _ULTIMATE_UI_H
#define _ULTIMATE_UI_H
#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <limits>

 /**
  * @class Ultimate_UI
  * @brief User interface handler for Ultimate Tic-Tac-Toe game
  *
  * Simple UI for Ultimate Tic-Tac-Toe:
  * - Displays the 9x9 underlying board with heavier separators every 3 cells.
  * - Accepts global coordinates in range [0..8].
  *
  * @details
  * This class manages all user interactions for Ultimate Tic-Tac-Toe,
  * with a focus on clear visualization of the multi-level game structure.
  *
  * Key features:
  * - 9x9 grid display with visual grouping of 3x3 small boards
  * - Column and row numbering (0-8) for easy coordinate reference
  * - Heavy separators (|) every 3 columns to divide small boards
  * - Horizontal divider lines every 3 rows
  * - Input validation for coordinates within valid range
  * - Conversion of space characters to dots for visibility
  *
  * The visual structure helps players understand:
  * - Which small board they're playing in
  * - The overall meta-game state
  * - Available positions within each small board
  */
class Ultimate_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Ultimate Tic-Tac-Toe user interface
     *
     * Initializes the UI with the game title "Ultimate Tic-Tac-Toe" and
     * sets up for single-player-at-a-time input (parameter 1).
     *
     * @details
     * The constructor prepares the UI for handling the complex 9x9 board
     * display and coordinate-based move input system.
     */
    Ultimate_UI() : UI<char>("Ultimate Tic-Tac-Toe", 1) {}

    /**
     * @brief Destructs the Ultimate UI object
     *
     * Cleans up any resources allocated by the UI.
     * Currently performs no special cleanup operations.
     */
    ~Ultimate_UI() override {}

    /**
     * @brief Displays the 9x9 game board with visual small board separators
     *
     * @param matrix Constant reference to a 2D vector representing the 9x9 board state
     *
     * @details
     * Creates a formatted display of the entire Ultimate Tic-Tac-Toe board with:
     *
     * Visual Features:
     * - Column numbers (0-8) displayed across the top
     * - Row numbers (0-8) displayed on the left side
     * - Vertical bars (|) every 3 columns to separate small boards
     * - Horizontal dashed lines every 3 rows to separate small boards
     * - Space characters converted to dots (.) for better visibility
     *
     * Structure:
     * @code
     *      0  1  2  | 3  4  5  | 6  7  8
     *   0  X  .  O  | .  .  .  | .  .  .
     *   1  .  X  .  | .  .  .  | .  .  .
     *   2  O  .  X  | .  .  .  | .  .  .
     *      --------------------------------
     *   3  .  .  .  | X  O  .  | .  .  .
     *   4  .  .  .  | .  X  .  | .  .  .
     *   5  .  .  .  | O  .  X  | .  .  .
     *      --------------------------------
     *   6  .  .  .  | .  .  .  | .  .  .
     *   7  .  .  .  | .  .  .  | .  .  .
     *   8  .  .  .  | .  .  .  | .  .  .
     * @endcode
     *
     * The separators make it easy to identify:
     * - Small board (0,0): rows 0-2, cols 0-2
     * - Small board (0,1): rows 0-2, cols 3-5
     * - Small board (1,1): rows 3-5, cols 3-5 (center)
     * - etc.
     *
     * @note Converts space (' ') to dot ('.') for empty cells
     * @note Empty check prevents crashes on uninitialized boards
     * @note Visual dividers appear at positions divisible by 3
     * @note This is a const method and does not modify the board
     */
    void display_board_matrix(const std::vector<std::vector<char>>& matrix) const override {
        if (matrix.empty() || matrix[0].empty()) return;
        int rows = static_cast<int>(matrix.size());
        int cols = static_cast<int>(matrix[0].size());
        std::cout << "\n    ";
        for (int c = 0; c < cols; ++c) {
            std::cout << std::setw(2) << c << ((c % 3 == 2 && c != cols - 1) ? " |" : " ");
        }
        std::cout << "\n";
        for (int r = 0; r < rows; ++r) {
            std::cout << std::setw(3) << r << " ";
            for (int c = 0; c < cols; ++c) {
                char ch = matrix[r][c];
                if (ch == static_cast<char>(' ')) ch = '.';
                std::cout << " " << ch << ((c % 3 == 2 && c != cols - 1) ? " |" : " ");
            }
            std::cout << "\n";
            if (r % 3 == 2 && r != rows - 1) {
                std::cout << "    " << std::string(cols * 3 + 4, '-') << "\n";
            }
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prompts for and retrieves a player's move in global coordinates
     *
     * @param player Pointer to the Player object making the move
     * @return Pointer to a Move object containing the selected global row, column, and symbol
     *
     * @details
     * Prompts the player to enter global coordinates for their move.
     * The coordinate system uses a single continuous range for the entire 9x9 board:
     * - Row: 0-8 (not separate 0-2 ranges per small board)
     * - Column: 0-8 (not separate 0-2 ranges per small board)
     *
     * Example coordinate mapping:
     * - Position (0,0): Top-left cell of top-left small board
     * - Position (1,4): Middle row, middle column of top-center small board
     * - Position (8,8): Bottom-right cell of bottom-right small board
     *
     * Input Validation:
     * - Checks that input consists of two valid integers
     * - Validates both coordinates are in range [0-8]
     * - Clears invalid input from the stream
     * - Re-prompts on any invalid input
     * - Does NOT validate if the cell is empty or small board is won (handled by Board)
     *
     * The prompt clearly indicates the valid range [0-8] to help players
     * understand the global coordinate system.
     *
     * Example interaction:
     * @code
     * Player1 (X) enter move (row col) [0-8]: 2 4
     * // Creates Move at global position (2,4)
     * // This is: small board (0,1), local position (2,1)
     * @endcode
     *
     * @note Loops indefinitely until valid integer input in range is received
     * @note Does not validate move legality (empty cell, board availability)
     * @warning Caller is responsible for deallocating the returned Move object
     *
     * @see UltimateTicTacToe::update_board() for move legality validation
     */
    Move<char>* get_move(Player<char>* player) override {
        int x = 0, y = 0;
        while (true) {
            std::cout << player->get_name() << " (" << player->get_symbol() << ") enter move (row col) [0-8]: ";
            if (!(std::cin >> x >> y)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter two integers in range 0..8.\n";
                continue;
            }
            if (x < 0 || x > 8 || y < 0 || y > 8) {
                std::cout << "Coordinates out of range. Use values 0..8.\n";
                continue;
            }
            return new Move<char>(x, y, player->get_symbol());
        }
    }
};
#endif