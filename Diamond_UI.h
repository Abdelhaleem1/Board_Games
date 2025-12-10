/**
 * @file Diamond_UI.h
 * @brief User interface implementation for Diamond Tic-Tac-Toe game
 * @date December 2025
 *
 * This file contains the UI class declaration for Diamond Tic-Tac-Toe,
 * handling all user interactions including displaying the diamond-shaped
 * board with proper visual formatting and collecting player moves.
 *
 * @details
 * The UI creates a visually appealing diamond-shaped board display by
 * using indentation to represent the diamond pattern. Only valid cells
 * within the diamond are shown, with proper spacing to maintain the
 * diamond's visual structure.
 */

#ifndef _DIAMOND_UI_H
#define _DIAMOND_UI_H
#include "BoardGame_Classes.h"
#include "Diamond_TicTacToe.h"
#include <limits>
#include <iostream>
#include <iomanip>
#include <cmath>

 /**
  * @class Diamond_UI
  * @brief User interface handler for Diamond Tic-Tac-Toe game
  *
  * This class manages all user interactions for the Diamond Tic-Tac-Toe game,
  * specializing in displaying the unique diamond-shaped board with proper
  * visual formatting and handling player input.
  *
  * @details
  * The UI provides:
  * - Diamond-shaped board visualization with appropriate indentation
  * - Row and column numbering for move reference
  * - Input validation for player moves
  * - Clear visual separation between valid and invalid cells
  *
  * The diamond shape is rendered using calculated indentation based on
  * Manhattan distance from the center cell.
  */
class Diamond_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Diamond Tic-Tac-Toe user interface
     *
     * Initializes the UI with the game title "Diamond Tic-Tac-Toe" and
     * sets up for 3 player slots (typically 2 active players are used).
     */
    Diamond_UI() : UI<char>("Diamond Tic-Tac-Toe", 3) {}

    /**
     * @brief Destructs the Diamond UI object
     *
     * Cleans up any resources allocated by the UI.
     * Currently performs no special cleanup operations.
     */
    ~Diamond_UI() override {}

    /**
     * @brief Displays the game board in a diamond shape
     *
     * @param matrix Constant reference to a 2D vector representing the board state
     *
     * @details
     * Renders the board with the following features:
     * - Column numbers displayed across the top
     * - Row numbers displayed on the left side
     * - Cells indented to form a diamond visual pattern
     * - Only valid cells (within diamond shape) are shown
     * - Invalid cells outside the diamond are rendered as spaces
     *
     * The diamond pattern is created using the formula:
     * `abs(center_r - r) + abs(center_c - c) <= center_r`
     *
     * Visual structure:
     * @code
     *         0   1   2   3   4
     *     0       2
     *     1     2 2 2
     *     2   2 2 2 2 2
     *     3     2 2 2
     *     4       2
     * @endcode
     *
     * @note Uses cell_width member variable (inherited) for spacing
     * @note The indentation increases as you move away from center row
     * @note Empty check prevents crashes on uninitialized boards
     */
    void display_board_matrix(const std::vector<std::vector<char>>& matrix) const override {
        if (matrix.empty() || matrix[0].empty()) return;
        int rows = static_cast<int>(matrix.size());
        int cols = static_cast<int>(matrix[0].size());
        int center_r = rows / 2;
        int center_c = cols / 2;
        std::cout << "\n    ";
        for (int c = 0; c < cols; ++c)
            std::cout << std::setw(cell_width + 1) << c;
        std::cout << "\n";
        for (int r = 0; r < rows; ++r) {
            int rowIndent = std::abs(center_r - r);
            std::cout << std::setw(3) << r << " ";
            for (int s = 0; s < rowIndent; ++s)
                std::cout << std::setw(cell_width + 1) << ' ';
            for (int c = 0; c < cols; ++c) {
                bool valid = (std::abs(center_r - r) + std::abs(center_c - c)) <= center_r;
                if (valid)
                    std::cout << std::setw(cell_width) << matrix[r][c] << ' ';
                else
                    std::cout << std::setw(cell_width) << ' ' << ' ';
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    /**
     * @brief Prompts for and retrieves a player's move
     *
     * @param player Pointer to the Player object making the move
     * @return Pointer to a Move object containing the selected row, column, and player symbol
     *
     * @details
     * Prompts the player to enter row and column coordinates for their move.
     * The input format is: "row col" (two integers separated by space)
     *
     * Input validation:
     * - Checks that input consists of two valid integers
     * - Clears invalid input from the stream
     * - Re-prompts on invalid input (non-integer values)
     * - Does NOT validate if the position is within the diamond or already occupied
     *   (that validation occurs in the Board's update_board method)
     *
     * Example interaction:
     * @code
     * Player1 (X) enter move (row col): 2 2
     * // Creates Move object with position (2,2) and symbol 'X'
     * @endcode
     *
     * @note The method loops indefinitely until valid integer input is received
     * @warning Caller is responsible for deallocating the returned Move object
     * @warning Does not validate if move is legal (within diamond or cell empty)
     *
     * @see Board::update_board() for move legality validation
     */
    Move<char>* get_move(Player<char>* player) override {
        int x = 0, y = 0;
        while (true) {
            std::cout << player->get_name() << " (" << player->get_symbol() << ") enter move (row col): ";
            if (!(std::cin >> x >> y)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter two integers.\n";
                continue;
            }
            return new Move<char>(x, y, player->get_symbol());
        }
    }
};
#endif