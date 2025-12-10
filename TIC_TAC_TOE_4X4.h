/**
 * @file Tic_Tac_Toe_4x4.h
 * @brief Implementation of 4x4 Tic-Tac-Toe game
 * @date December 2025
 *
 * This file contains the class declarations for 4x4 Tic-Tac-Toe,
 * an expanded variant of the classic game played on a 4x4 grid.
 * The larger board creates more complex strategic possibilities
 * compared to the standard 3x3 version.
 *
 * @details
 * Game Rules:
 * - Played on a 4x4 grid (16 cells total)
 * - Players alternate placing X and O marks
 * - Win by getting three in a row (not four) - horizontal, vertical, or diagonal
 * - If all 16 cells are filled with no three-in-a-row, the game is a draw
 *
 * The 4x4 board creates interesting strategic depth:
 * - More possible winning lines than 3x3
 * - More opportunities for multiple threats
 * - Requires longer-term planning
 * - The xold/yold tracking suggests possible move history or special rules
 */

#ifndef TIC_TAC_TOE_4X4_H
#define TIC_TAC_TOE_4X4_H
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class XO_4x4_Board
 * @brief Game board implementation for 4x4 Tic-Tac-Toe
 *
 * This class extends the Board template class to implement the specific logic
 * for 4x4 Tic-Tac-Toe. The board manages a 4x4 grid where players attempt to
 * create three consecutive marks in any direction.
 *
 * @details
 * The board maintains:
 * - A 4x4 grid of cells (16 total positions)
 * - Move validation and placement logic
 * - Win detection for three-in-a-row patterns
 * - Tracking variables (xold, yold, mark) for special game mechanics
 *
 * Winning patterns check:
 * - 4 horizontal rows (each can start at 2 positions for 3-in-a-row)
 * - 4 vertical columns (each can start at 2 positions)
 * - Multiple diagonal lines of length 3+
 *
 * The xold/yold variables (initialized to 4) suggest tracking of:
 * - Previous move positions
 * - Special move restrictions
 * - Turn-based mechanics
 */
class XO_4x4_Board : public Board<char> {
private:
    char blank_symbol = '.';  ///< Character used to represent an empty cell on the board
    char mark = 1;            ///< Mark variable for tracking game state or special conditions
    int xold = 4, yold = 4;   ///< Previous move coordinates (initialized to 4, outside 0-3 range)

public:
    /**
     * @brief Constructs a new 4x4 Tic-Tac-Toe board
     *
     * @details
     * Initializes a 4x4 grid with all cells empty.
     * Sets up initial state including:
     * - All 16 cells filled with blank_symbol
     * - Move counter set to zero
     * - Previous move trackers (xold, yold) initialized to 4 (invalid position)
     * - Mark variable initialized to 1
     */
    XO_4x4_Board();

    /**
     * @brief Updates the board with a player's move
     *
     * @param move Pointer to Move object containing position and player symbol
     * @return true if the move was valid and successfully placed; false otherwise
     *
     * @details
     * Validates and applies a move to the board. A move is valid if:
     * - Position is within the 4x4 grid boundaries (0-3 for both row and column)
     * - Target cell is currently empty
     * - Any special move restrictions are satisfied (based on xold/yold)
     *
     * After placing the move:
     * - Updates the board with the player's symbol
     * - Updates xold and yold to track this move
     * - Increments the move counter
     * - May update the mark variable
     *
     * @note The xold/yold tracking suggests possible move-ordering rules
     * @warning Does not check for game-over conditions
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the specified player has won
     *
     * @param player Pointer to the Player object to check
     * @return true if the player has three in a row; false otherwise
     *
     * @details
     * Scans the entire 4x4 board for three consecutive marks belonging to the player.
     * Checks all possible winning lines:
     *
     * Horizontal lines:
     * - Row 0: columns (0,1,2), (1,2,3)
     * - Row 1: columns (0,1,2), (1,2,3)
     * - Row 2: columns (0,1,2), (1,2,3)
     * - Row 3: columns (0,1,2), (1,2,3)
     * Total: 8 horizontal lines
     *
     * Vertical lines:
     * - Similar pattern for columns
     * Total: 8 vertical lines
     *
     * Diagonal lines:
     * - Main diagonals of length 3 and 4
     * - Anti-diagonals of length 3 and 4
     * Total: Multiple diagonal lines
     *
     * @note Win requires exactly three in a row, not four
     * @note More winning patterns than standard 3x3 Tic-Tac-Toe
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the specified player has lost
     *
     * @param Player object pointer (unused)
     * @return Always returns false
     *
     * @details
     * In 4x4 Tic-Tac-Toe, there is no explicit lose condition.
     * A player loses only when their opponent wins (achieves three in a row).
     * This is checked separately through is_win() for the other player.
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game has ended in a draw
     *
     * @param player Pointer to a Player object (used for context)
     * @return true if all 16 cells are filled with no three-in-a-row; false otherwise
     *
     * @details
     * A draw occurs when:
     * - All 16 cells on the 4x4 board are filled
     * - Neither player has achieved three consecutive marks in any direction
     *
     * The larger board makes draws less common than in 3x3 Tic-Tac-Toe,
     * as there are more opportunities to create winning lines.
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
     * - Has any player won? (three in a row)
     * - Is the game a draw? (board full, no three-in-a-row)
     *
     * @note Should be called after each move to determine if gameplay should end
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class XO_4x4_UI
 * @brief User interface handler for 4x4 Tic-Tac-Toe game
 *
 * This class manages all user interactions for the 4x4 Tic-Tac-Toe game,
 * handling player setup, move collection, and board display. The UI must
 * accommodate the larger 4x4 grid and potentially more complex move input
 * if special rules based on xold/yold are implemented.
 *
 * @details
 * Key responsibilities:
 * - Display the 4x4 board with row and column labels
 * - Collect player moves with validation
 * - Handle both human and AI player types
 * - Show game status and available moves
 * - Potentially enforce move restrictions based on previous moves
 */
class XO_4x4_UI : public UI<char> {
public:
    /**
     * @brief Constructs the 4x4 Tic-Tac-Toe user interface
     *
     * @details
     * Initializes the UI with appropriate settings for 4x4 Tic-Tac-Toe:
     * - Sets up the game title
     * - Configures for 2-player gameplay
     * - Prepares display formatting for the 4x4 grid
     *
     * The UI is ready to handle player setup and game flow immediately
     * after construction.
     */
    XO_4x4_UI();

    /**
     * @brief Destructs the 4x4 XO UI object
     *
     * Cleans up any resources allocated by the UI.
     * Currently performs no special cleanup operations.
     */
    ~XO_4x4_UI() {};

    /**
     * @brief Creates a single player object
     *
     * @param name Reference to string containing the player's name
     * @param symbol Character symbol representing this player's marks ('X' or 'O')
     * @param type Type of player (human, AI, random, etc.)
     * @return Pointer to the newly created Player object
     *
     * @details
     * Factory method that instantiates the appropriate Player subclass based
     * on the specified type. For 4x4 Tic-Tac-Toe, AI players need strategy for:
     * - Larger search space (16 positions vs 9 in standard)
     * - Multiple simultaneous threats possible
     * - More complex winning pattern recognition
     * - Longer-term strategic planning
     * - Potential move restrictions based on game rules
     *
     * @warning Caller is responsible for deallocating the returned Player object
     * @note AI complexity increases significantly with the larger board
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Prompts for and retrieves a player's move
     *
     * @param player Pointer to the Player object making the move
     * @return Pointer to a Move object containing the selected row, column, and symbol
     *
     * @details
     * For human players, prompts for row and column coordinates (0-3).
     * For AI players, automatically calculates the move based on the AI algorithm.
     *
     * Validates that:
     * - Row and column numbers are within valid range (0-3)
     * - Selected cell is empty
     * - Input is properly formatted
     * - Any special move restrictions are satisfied
     *
     * The UI should display:
     * - Current board state with all 16 positions
     * - Row and column numbers for reference
     * - Which player's turn it is
     * - Any move restrictions if applicable
     *
     * @note The 4x4 board provides 16 possible moves per turn
     * @note Re-prompts the user if invalid input is detected
     * @warning Caller is responsible for deallocating the returned Move object
     */
    virtual Move<char>* get_move(Player<char>* player);
};
#endif