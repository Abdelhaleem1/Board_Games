/**
 * @file Inverse_XO_UI.h
 * @brief User interface implementation for Inverse Tic-Tac-Toe game
 * @date December 2025
 *
 * This file contains the UI class declaration for Inverse (Misère) Tic-Tac-Toe,
 * handling all user interactions including player setup, move collection, and
 * special validation to warn players when a move would cause them to lose.
 *
 * @details
 * This UI is specifically designed for the inverse variant where creating
 * three in a row means losing. It includes helper methods to check if a
 * proposed move would result in an immediate loss, allowing the UI to
 * provide warnings or prevent accidental losing moves.
 */

#ifndef _INVERSE_XO_UI_H
#define _INVERSE_XO_UI_H
#include "BoardGame_Classes.h"
 // #include "..\..\..\Downloads\BoardGameFramework-v2.3\Inverse_TicTacToe.h"
#include <vector>

/**
 * @class Inverse_XO_UI
 * @brief User interface handler for Inverse Tic-Tac-Toe game
 *
 * This class manages all user interactions for the Inverse Tic-Tac-Toe game,
 * providing specialized functionality for the misère variant. Unlike standard
 * Tic-Tac-Toe UI, this class can check whether a move would cause the player
 * to lose (by creating three in a row) and potentially warn or prevent such moves.
 *
 * @details
 * Key features:
 * - Standard player setup and move collection
 * - Move validation that checks for immediate losing moves
 * - Can warn players before they make a move that creates three in a row
 * - Supports different player types (human, AI)
 *
 * The UI helps prevent accidental losses by identifying moves that would
 * complete three in a row for the current player.
 */
class Inverse_XO_UI : public UI<char> {
public:
    /**
     * @brief Constructs the Inverse Tic-Tac-Toe user interface
     *
     * @details
     * Initializes the UI with appropriate settings for Inverse Tic-Tac-Toe,
     * including the game title and player configuration. Sets up the interface
     * to handle the unique requirements of the misère variant.
     */
    Inverse_XO_UI();

    /**
     * @brief Destructs the Inverse XO UI object
     *
     * Cleans up any resources allocated by the UI.
     * Currently performs no special cleanup operations.
     */
    ~Inverse_XO_UI() override {};

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
     * - Human player (requires strategic thinking to avoid three in a row)
     * - Random AI (makes random valid moves)
     * - Smart AI (strategically avoids creating three in a row)
     *
     * For Inverse Tic-Tac-Toe, AI players need special logic to:
     * - Avoid creating three in a row for themselves
     * - Try to force opponents into making three in a row
     *
     * @warning Caller is responsible for deallocating the returned Player object
     * @note AI strategy for inverse variant differs significantly from standard Tic-Tac-Toe
     */
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;

    /**
     * @brief Prompts for and retrieves a player's move
     *
     * @param player Pointer to the Player object making the move
     * @return Pointer to a Move object containing the selected row, column, and player symbol
     *
     * @details
     * For human players, prompts for row and column coordinates.
     * For AI players, automatically calculates the move based on the AI algorithm.
     *
     * This method may use the would_lose_if_move() helper to:
     * - Warn players if they're about to make a losing move
     * - Prevent accidental losses by requiring confirmation
     * - Display which positions would result in an immediate loss
     *
     * Validates that:
     * - Row and column numbers are within valid range (0-2)
     * - The selected cell is not already occupied
     * - Input is properly formatted
     *
     * @note May provide additional feedback about dangerous moves in inverse variant
     * @note Re-prompts the user if invalid input is detected
     * @warning Caller is responsible for deallocating the returned Move object
     *
     * @see would_lose_if_move() for checking if a move would cause immediate loss
     */
    Move<char>* get_move(Player<char>* player) override;

private:
    /**
     * @brief Checks if a move would cause the player to lose immediately
     *
     * @param player Pointer to the Player object considering the move
     * @param x Row coordinate of the proposed move (0-2)
     * @param y Column coordinate of the proposed move (0-2)
     * @return true if placing the symbol at (x,y) would create three in a row (loss); false otherwise
     *
     * @details
     * This helper method simulates placing the player's symbol at the specified
     * position and checks if it would complete three in a row, which means losing
     * in Inverse Tic-Tac-Toe.
     *
     * The method checks:
     * - The row containing position (x,y)
     * - The column containing position (x,y)
     * - The main diagonal (if x,y is on it)
     * - The anti-diagonal (if x,y is on it)
     *
     * Use cases:
     * - Warning players before they make a losing move
     * - Highlighting dangerous positions in the UI
     * - AI decision-making to avoid immediate losses
     * - Tutorial mode to teach the inverse rules
     *
     * @note Does not modify the actual board; performs read-only checking
     * @note Assumes the position (x,y) is currently empty
     * @note This check is specific to Inverse Tic-Tac-Toe where three-in-a-row is bad
     *
     * Example usage:
     * @code
     * if (would_lose_if_move(player, row, col)) {
     *     std::cout << "Warning: This move would make you lose!\n";
     * }
     * @endcode
     */
     // Return true if placing player's symbol at (x,y) would produce a 3-in-row for that player
    bool would_lose_if_move(Player<char>* player, int x, int y) const;
};
#endif // _INVERSE_XO_UI_H