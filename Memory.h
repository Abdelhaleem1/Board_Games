/**
 * @file Memory_Board.h
 * @brief Implementation of Memory Tic-Tac-Toe game board and user interface
 * @date December 2025
 *
 * This file contains the class declarations for implementing the Memory Tic-Tac-Toe game.
 * Memory Tic-Tac-Toe is a variant of the classic game where the board is hidden after
 * each move, requiring players to remember previous moves. Players must recall the
 * positions of their own and opponent's marks to make strategic decisions.
 */

#pragma once
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Memory_Board
 * @brief Game board implementation for Memory Tic-Tac-Toe
 *
 * This class extends the Board template class to implement the specific logic
 * for Memory Tic-Tac-Toe. Unlike standard Tic-Tac-Toe, the board state is hidden
 * from players between moves, creating a memory-based challenge. The board
 * manages game state, validates moves, and determines win/lose/draw conditions.
 *
 * @details
 * The board uses a 3x3 grid (standard Tic-Tac-Toe dimensions) where each cell
 * can contain a player's symbol or remain empty. The memory aspect is handled
 * by the UI layer, which controls when the board is displayed to players.
 */
class Memory_Board : public Board<char> {
private:
    char blank_symbol = '.';  ///< Symbol representing empty cells on the board

public:
    /**
     * @brief Constructs a new Memory Tic-Tac-Toe board
     *
     * Initializes the game board with standard 3x3 Tic-Tac-Toe dimensions
     * and fills all cells with the blank symbol to represent an empty board.
     */
    Memory_Board();

    /**
     * @brief Updates the board with a player's move
     *
     * @param move_ptr Pointer to a Move object containing the position and symbol
     * @return true if the move was valid and successfully placed; false otherwise
     *
     * @details
     * Places the player's symbol at the specified row and column position.
     * The move is only valid if:
     * - The position is within board boundaries (0-2 for both row and column)
     * - The target cell is empty (contains the blank symbol)
     *
     * @note This method does not hide the board; that responsibility lies with the UI
     * @warning Does not check for game-over conditions; call game_is_over() separately
     */
    bool update_board(Move<char>* move_ptr) override;

    /**
     * @brief Checks if the specified player has won
     *
     * @param player Pointer to the Player object to check
     * @return true if the player has three in a row in any winning configuration; false otherwise
     *
     * @details
     * Checks all possible winning combinations for Tic-Tac-Toe:
     * - Three horizontal rows
     * - Three vertical columns
     * - Two diagonals (main diagonal and anti-diagonal)
     *
     * A player wins by having their symbol in all three positions of any line.
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the specified player has lost
     *
     * @param player Pointer to the Player object to check
     * @return true if the player has lost; false otherwise
     *
     * @details
     * In Tic-Tac-Toe, a player loses when their opponent wins. This method
     * typically checks if the other player has achieved three in a row.
     */
    bool is_lose(Player<char>* player) override;

    /**
     * @brief Checks if the game has ended in a draw
     *
     * @param player Pointer to a Player object (used for context)
     * @return true if all cells are filled with no winner; false otherwise
     *
     * @details
     * A draw (also called a "cat's game") occurs when all nine cells are filled
     * and neither player has achieved three in a row. This is a common outcome
     * in Tic-Tac-Toe when both players play optimally.
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game has concluded
     *
     * @param player Pointer to the Player object to check against
     * @return true if the game is over (win or draw); false if play can continue
     *
     * @details
     * The game is over if either:
     * - Any player has won (three in a row)
     * - The board is completely filled (draw)
     *
     * @note This method should be called after each move to determine if gameplay should end
     */
    bool game_is_over(Player<char>* player) override;
};

/**
 * @class Memory_UI
 * @brief User interface handler for Memory Tic-Tac-Toe game
 *
 * This class manages all user interactions for the Memory Tic-Tac-Toe game.
 * The key feature of this UI is that it hides the board between moves,
 * requiring players to memorize positions. It handles player setup, move
 * collection, and special display logic for the memory variant.
 *
 * @details
 * The UI shows the board briefly after each move, then clears or hides it
 * before the next player's turn. This creates a memory challenge where
 * players must track moves mentally rather than visually referencing the board.
 */
class Memory_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Memory Tic-Tac-Toe user interface
     *
     * Initializes the UI with a welcome message and sets up for 3 player slots
     * (though typically only 2 are used in standard gameplay).
     *
     * @note The welcome message contains a typo: "Weclome" instead of "Welcome"
     */
    Memory_UI() : UI<char>("Weclome to Memory Tic-Tac-Toe Game", 3) {}

    /**
     * @brief Destructs the Memory Tic-Tac-Toe UI object
     *
     * Cleans up any resources allocated by the UI. Currently performs no
     * special cleanup operations.
     */
    ~Memory_UI() {};

    /**
     * @brief Creates a single player object
     *
     * @param name Reference to string containing the player's name
     * @param symbol Character symbol representing this player's marks (typically 'X' or 'O')
     * @param type Type of player (human, AI, random, etc.)
     * @return Pointer to the newly created Player object
     *
     * @details
     * Factory method that instantiates the appropriate Player subclass based
     * on the specified type. Supported types may include:
     * - Human player (requires memorization skills)
     * - Random AI (makes random valid moves)
     * - Smart AI (has perfect memory of all moves)
     *
     * @note AI players have an advantage as they can perfectly remember all moves
     * @warning Caller is responsible for deallocating the returned Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    /**
     * @brief Prompts for and retrieves a player's move
     *
     * @param player Pointer to the Player object making the move
     * @return Pointer to a Move object containing the selected row, column, and symbol
     *
     * @details
     * For human players, prompts for row and column coordinates (typically 0-2).
     * For AI players, automatically calculates the move based on the AI algorithm.
     *
     * In Memory Tic-Tac-Toe, players must remember:
     * - Where they've placed their previous marks
     * - Where their opponent has placed marks
     * - Which cells are still empty
     *
     * Validates that:
     * - Row and column numbers are within valid range (0-2)
     * - The selected cell is not already occupied
     * - Input is properly formatted
     *
     * @note Re-prompts the user if invalid input is detected
     * @warning Caller is responsible for deallocating the returned Move object
     */
    Move<char>* get_move(Player<char>* player) override;

    /**
     * @brief Displays the game board matrix to the console
     *
     * @param matrix Constant reference to a 2D vector representing the board state
     *
     * @details
     * This method provides a formatted display of the current board state.
     * It's typically called:
     * - Briefly after a player makes a move (to show the result)
     * - At the end of the game (to reveal the final board state)
     *
     * The display may include:
     * - Row and column numbers for reference
     * - Grid lines separating cells
     * - Player symbols and empty cells
     *
     * In the memory variant, this display is intentionally temporary, giving
     * players only a brief glimpse before hiding the board again.
     *
     * @note This is a const method and does not modify the board state
     * @see The UI may clear the screen after displaying to enforce the memory aspect
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const;
};