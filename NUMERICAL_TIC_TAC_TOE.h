/**
 * @file Numerical_Tic_Tac_Toe.h
 * @brief Implementation of Numerical Tic-Tac-Toe game
 * @date December 2025
 *
 * This file contains the class declarations for Numerical Tic-Tac-Toe,
 * a mathematical variant where players use numbers instead of X and O.
 * Players alternate placing numbers on a 3x3 grid, with one player using
 * odd numbers (1,3,5,7,9) and the other using even numbers (2,4,6,8).
 *
 * @details
 * Game Rules:
 * - Player 1 uses odd numbers: 1, 3, 5, 7, 9
 * - Player 2 uses even numbers: 2, 4, 6, 8
 * - A player wins by creating a line (row, column, or diagonal) that sums to 15
 * - Each number can only be used once per game
 * - If all numbers are placed with no line summing to 15, the game is a draw
 *
 * This variant adds a mathematical puzzle element, requiring players to
 * calculate sums and strategically choose which numbers to play.
 */

#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

/**
 * @class Numerical_XO_Board
 * @brief Game board implementation for Numerical Tic-Tac-Toe
 *
 * This class extends the Board template class to implement the specific logic
 * for Numerical Tic-Tac-Toe. Instead of X and O symbols, the board stores
 * numeric characters (1-9). Win conditions are determined by checking if any
 * line (row, column, or diagonal) sums to exactly 15.
 *
 * @details
 * The board manages:
 * - A 3x3 grid storing numeric characters
 * - Move validation to ensure numbers aren't reused
 * - Sum calculations for all possible winning lines
 * - Game state tracking (win, draw, ongoing)
 *
 * Mathematical background:
 * The number 15 is chosen because it's the magic constant of a 3x3 magic square.
 * With the numbers 1-9, there are exactly 8 ways to sum to 15 using three
 * different numbers, corresponding to the 8 possible winning lines.
 */
class Numerical_XO_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
    /**
     * @brief Constructs a new Numerical Tic-Tac-Toe board
     *
     * @details
     * Initializes a 3x3 grid with all cells empty (represented by blank_symbol).
     * Sets up the board state for a new game where no numbers have been played yet.
     */
    Numerical_XO_Board();

    /**
     * @brief Updates the board with a player's move
     *
     * @param move Pointer to Move object containing position and numeric symbol
     * @return true if the move was valid and successfully placed; false otherwise
     *
     * @details
     * Validates and applies a move to the board. A move is valid if:
     * - Position is within the 3x3 grid boundaries (0-2 for both row and column)
     * - Target cell is currently empty
     * - The number hasn't been used yet in the game
     * - The number belongs to the correct player (odd for player 1, even for player 2)
     *
     * If valid, places the numeric symbol at the specified position.
     *
     * @note Numbers 1,3,5,7,9 are for one player; 2,4,6,8 are for the other
     * @warning Each number can only be used once per game
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the specified player has won
     *
     * @param player Pointer to the Player object to check
     * @return true if the player has a line summing to 15; false otherwise
     *
     * @details
     * Scans all possible winning lines to see if any sum to exactly 15:
     * - Three rows (horizontal)
     * - Three columns (vertical)
     * - Two diagonals (main and anti)
     *
     * For each line, converts the three characters to integers and sums them.
     * A player wins if they've created any line that totals 15.
     *
     * @note All three numbers in the winning line must belong to the same player
     * @note Empty cells (blank_symbol) are not counted in sums
     *
     * Example winning combinations that sum to 15:
     * - 1 + 5 + 9 = 15
     * - 2 + 6 + 7 = 15 (if 7 is available to player 2)
     * - 3 + 4 + 8 = 15
     * - 1 + 6 + 8 = 15 (mixed, only valid if same player owns all three)
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the specified player has lost
     *
     * @param Player object pointer (unused)
     * @return Always returns false
     *
     * @details
     * In Numerical Tic-Tac-Toe, there is no explicit lose condition.
     * A player loses only when their opponent wins (achieves a sum of 15).
     * This is checked separately through is_win() for the other player.
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game has ended in a draw
     *
     * @param player Pointer to a Player object (used for context)
     * @return true if all numbers are used with no line summing to 15; false otherwise
     *
     * @details
     * A draw occurs when:
     * - All available numbers (1-9 or a subset) have been placed on the board
     * - No line (row, column, or diagonal) sums to exactly 15
     *
     * This can happen when players strategically block each other from forming
     * lines that sum to 15, or when the mathematical combinations prevent it.
     *
     * @note Checks that neither player has won before declaring a draw
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game has concluded
     *
     * @param player Pointer to the Player object to check against
     * @return true if the game is over (win or draw); false if play continues
     *
     * @details
     * Checks all end-game conditions:
     * - Has any player won? (line summing to 15)
     * - Is the game a draw? (all numbers used, no sum of 15)
     *
     * @note Should be called after each move to determine if gameplay should end
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class Numerical_XO_UI
 * @brief User interface handler for Numerical Tic-Tac-Toe game
 *
 * This class manages all user interactions for the Numerical Tic-Tac-Toe game,
 * handling player setup, move collection, and tracking which numbers have been
 * used. The UI must enforce that each number can only be played once and that
 * players use only their assigned number sets (odd or even).
 *
 * @details
 * Key responsibilities:
 * - Display available numbers for each player
 * - Validate that players choose from their correct number set
 * - Track which numbers have been used
 * - Prevent reuse of already-played numbers
 * - Show the current board state with numbers instead of X/O
 */
class Numerical_XO_UI : public UI<char> {
public:
    vector<char> nums;  ///< Vector tracking available/used numbers for the game

    /**
     * @brief Constructs the Numerical Tic-Tac-Toe user interface
     *
     * @details
     * Initializes the UI with appropriate settings for Numerical Tic-Tac-Toe:
     * - Sets up the game title
     * - Initializes the nums vector with available numbers (1-9)
     * - Prepares the interface for numeric input instead of X/O
     *
     * The nums vector will be used to track which numbers have been played
     * and which are still available for use.
     */
    Numerical_XO_UI();

    /**
     * @brief Destructs the Numerical XO UI object
     *
     * Cleans up any resources allocated by the UI.
     * Currently performs no special cleanup operations.
     */
    ~Numerical_XO_UI() {};

    /**
     * @brief Creates a single player object
     *
     * @param name Reference to string containing the player's name
     * @param symbol Character representing the player's number type ('O' for odd, 'E' for even)
     * @param type Type of player (human, AI, random, etc.)
     * @return Pointer to the newly created Player object
     *
     * @details
     * Factory method that instantiates the appropriate Player subclass based
     * on the specified type. For Numerical Tic-Tac-Toe:
     * - One player gets odd numbers (1, 3, 5, 7, 9)
     * - Other player gets even numbers (2, 4, 6, 8)
     *
     * AI players need special logic to:
     * - Calculate which combinations can sum to 15
     * - Track which numbers are still available
     * - Block opponents from completing lines that sum to 15
     * - Strategically choose numbers that create multiple winning threats
     *
     * @warning Caller is responsible for deallocating the returned Player object
     * @note Symbol 'O' typically represents odd numbers, 'E' for even numbers
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Prompts for and retrieves a player's move
     *
     * @param player Pointer to the Player object making the move
     * @return Pointer to a Move object containing position and numeric symbol
     *
     * @details
     * For human players, prompts for:
     * - Row and column coordinates (0-2)
     * - The number to place (must be from player's available set)
     *
     * For AI players, automatically calculates the best move.
     *
     * Validates that:
     * - Row and column are within valid range (0-2)
     * - Selected cell is empty
     * - Chosen number belongs to the player's set (odd or even)
     * - Chosen number hasn't been used yet in the game
     *
     * The UI should display:
     * - Available numbers for the current player
     * - Numbers that have already been used
     * - Current board state
     *
     * @note Updates the nums vector to mark the number as used
     * @note Re-prompts if player tries to use an invalid or already-used number
     * @warning Caller is responsible for deallocating the returned Move object
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Sets up all players for the game
     *
     * @return Pointer to an array of Player pointers
     *
     * @details
     * Prompts users to configure each player:
     * - Player 1: Name, type, assigned odd numbers (1,3,5,7,9)
     * - Player 2: Name, type, assigned even numbers (2,4,6,8)
     *
     * Initializes the nums vector with all available numbers and assigns
     * appropriate number sets to each player.
     *
     * @note Player 1 traditionally gets odd numbers, Player 2 gets even
     * @warning Caller is responsible for deallocating the returned array
     */
    Player<char>** setup_players()override;
};
#endif //NUMERICAL_TIC_TAC_TOE_H