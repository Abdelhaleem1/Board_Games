/**
 * @file Pyramid_Tic_Tac_Toe.h
 * @brief Implementation of Pyramid Tic-Tac-Toe game
 * @date [December 2025]
 *
 * This file contains the class declarations for Pyramid Tic-Tac-Toe,
 * a spatial variant played on a pyramid-shaped board. The playing field
 * has a unique structure with cells arranged in a pyramid pattern across
 * a 3x5 grid, where only specific cells are valid for play.
 *
 * @details
 * Game Structure:
 * - Board is conceptually 3x5 but only certain cells are playable
 * - Row 0: Only cell at column 2 (top of pyramid)
 * - Row 1: Cells at columns 1, 2, 3 (middle tier)
 * - Row 2: All 5 cells at columns 0-4 (base of pyramid)
 * - Total of 9 valid cells forming a pyramid shape
 *
 * Visual representation:
 * @code
 *         [2]           (Row 0)
 *      [1][2][3]        (Row 1)
 *   [0][1][2][3][4]     (Row 2)
 * @endcode
 *
 * Win conditions follow standard Tic-Tac-Toe rules but adapted for the
 * pyramid structure, checking rows, certain columns, and diagonals.
 */


#ifndef PYRAMID_TIC_TAC_TOE_H
#define PYRAMID_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class Pyramid_XO_Board
 * @brief Game board implementation for Pyramid Tic-Tac-Toe
 *
 * This class extends the Board template class to implement the specific logic
 * for Pyramid Tic-Tac-Toe. The board has a unique pyramid structure where only
 * 9 specific cells out of a 3x5 grid are valid for play.
 *
 * @details
 * Valid cell positions:
 * - Row 0: Column 2 only (apex)
 * - Row 1: Columns 1, 2, 3 (middle level)
 * - Row 2: Columns 0, 1, 2, 3, 4 (base)
 *
 * The pyramid shape creates unique strategic considerations:
 * - Limited cells at the top create bottlenecks
 * - Base provides more positioning options
 * - Winning lines must be identified within the pyramid structure
 * - Some traditional Tic-Tac-Toe strategies don't apply due to shape
 */
class Pyramid_XO_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.

public:
    /**
     * @brief Default constructor that initializes a 3x5 Pyramid X-O board
     *
     * @details
     * Constructs a board with 3 rows and 5 columns, but only specific cells
     * are valid for the pyramid structure:
     * - Initializes all cells with the blank symbol
     * - Sets up the pyramid configuration
     * - Prepares win-checking logic for the pyramid shape
     */
    Pyramid_XO_Board();

    /**
     * @brief Updates the board with a player's move
     *
     * @param move Pointer to a Move<char> object containing move coordinates and symbol
     * @return true if the move is valid and successfully applied, false otherwise
     *
     * @details
     * Validates and applies a move to the pyramid board. A move is valid if:
     * - Position is within grid boundaries
     * - Position is a valid cell in the pyramid structure:
     *   - (0,2): top of pyramid
     *   - (1,1), (1,2), (1,3): middle tier
     *   - (2,0), (2,1), (2,2), (2,3), (2,4): base
     * - Target cell is currently empty
     *
     * @note Invalid cells outside the pyramid pattern are rejected
     * @warning Does not check for game-over conditions
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the given player has won the game
     *
     * @param player Pointer to the player being checked
     * @return true if the player has a winning line, false otherwise
     *
     * @details
     * Checks for winning configurations within the pyramid structure.
     * Possible winning lines may include:
     * - Horizontal lines within the pyramid (base row, middle tier)
     * - Vertical lines through valid cells
     * - Diagonal lines following the pyramid shape
     *
     * The win-checking logic is adapted for the non-rectangular board shape,
     * considering only valid cell combinations within the pyramid.
     *
     * @note Winning patterns differ from standard 3x3 Tic-Tac-Toe due to pyramid shape
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the given player has lost the game
     *
     * @param player Pointer to the player being checked
     * @return Always returns false (not used in X-O logic)
     *
     * @details
     * In standard Pyramid Tic-Tac-Toe, there is no explicit lose condition.
     * A player loses only when their opponent wins, which is checked
     * separately through is_win() for the other player.
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game has ended in a draw
     *
     * @param player Pointer to the player being checked
     * @return true if all cells are filled and no player has won, false otherwise
     *
     * @details
     * A draw occurs when:
     * - All 9 valid pyramid cells are filled
     * - Neither player has achieved a winning configuration
     *
     * The draw check only considers the valid pyramid cells, not the entire 3x5 grid.
     *
     * @note Only valid pyramid positions count toward the draw condition
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Determines if the game is over (win or draw)
     *
     * @param player Pointer to the player to evaluate
     * @return true if the game has ended, false otherwise
     *
     * @details
     * Checks all end-game conditions:
     * - Has any player won?
     * - Are all valid pyramid cells filled (draw)?
     *
     * @note Should be called after each move to check game status
     */
    bool game_is_over(Player<char>* player);
};


/**
 * @class Pyramid_XO_UI
 * @brief User Interface class for the Pyramid Tic-Tac-Toe game
 *
 * Inherits from the generic `UI<char>` base class and provides
 * Pyramid X-O specific functionality for player setup, move input,
 * and displaying the unique pyramid-shaped board.
 *
 * @details
 * The UI handles:
 * - Displaying the pyramid structure visually with proper formatting
 * - Showing only valid cells in the pyramid pattern
 * - Row and column numbering for move reference
 * - Collecting and validating player moves
 * - Player setup and configuration
 *
 * The display uses special formatting to create a visual pyramid shape,
 * with appropriate spacing and borders to clearly show the structure.
 *
 * @see UI
 */
class Pyramid_XO_UI : public UI<char> {
public:
    /**
     * @brief Constructs a Pyramid_XO_UI object
     *
     * Initializes the base `UI<char>` class with the welcome message
     * for Pyramid Tic-Tac-Toe and sets up the display formatting.
     *
     * @details
     * Sets up the UI to handle the unique pyramid board structure and
     * prepares for displaying the non-rectangular playing field.
     */
    Pyramid_XO_UI();

    /**
     * @brief Destructor for Pyramid_XO_UI
     *
     * Cleans up any resources allocated by the UI.
     * Currently performs no special cleanup operations.
     */
    ~Pyramid_XO_UI() {};

    /**
     * @brief Creates a player of the specified type
     *
     * @param name Name of the player
     * @param symbol Character symbol ('X' or 'O') assigned to the player
     * @param type The type of the player (Human or Computer)
     * @return Pointer to the newly created Player<char> instance
     *
     * @details
     * Factory method that instantiates the appropriate Player subclass.
     * For Pyramid Tic-Tac-Toe, AI players need special logic to:
     * - Understand the pyramid structure and valid positions
     * - Recognize winning patterns in the non-standard shape
     * - Strategize around the limited top positions
     * - Utilize the wider base for positioning
     *
     * @warning Caller is responsible for deallocating the returned Player object
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player
     *
     * @param player Pointer to the player whose move is being requested
     * @return A pointer to a new `Move<char>` object representing the player's action
     *
     * @details
     * For human players, prompts for row and column coordinates.
     * For AI players, automatically calculates the move.
     *
     * Validates that:
     * - Row and column are within grid bounds
     * - Position is a valid pyramid cell
     * - Selected cell is empty
     * - Input is properly formatted
     *
     * Valid positions to enter:
     * - Row 0: Column 2 only
     * - Row 1: Columns 1, 2, or 3
     * - Row 2: Columns 0, 1, 2, 3, or 4
     *
     * @note Re-prompts if invalid position or occupied cell is selected
     * @warning Caller is responsible for deallocating the returned Move object
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Displays the pyramid-shaped game board
     *
     * @param matrix Constant reference to a 2D vector representing the board state
     *
     * @details
     * Creates a visual representation of the pyramid board structure:
     * - Shows column numbers across the top
     * - Displays row numbers on the left
     * - Uses borders and spacing to form pyramid shape
     * - Only displays valid pyramid cells
     * - Empty spaces for invalid grid positions
     *
     * Visual output structure:
     * @code
     *     0   1   2   3   4
     *    ---------------------
     * 0            |X |
     *    ---------------------
     * 1      |O |X |O |
     *    ---------------------
     * 2  |X |O |X |O |X |
     *    ---------------------
     * @endcode
     *
     * Formatting details:
     * - Row 0: Only column 2 displayed with borders
     * - Row 1: Columns 1-3 displayed with borders
     * - Row 2: All columns 0-4 displayed with borders
     * - Invalid positions shown as blank spaces
     * - Uses cell_width for consistent spacing
     *
     * @note This is a const method and does not modify the board
     * @note Empty check prevents crashes on uninitialized boards
     */
    void display_board_matrix(const vector<vector<char>>& matrix) const override {
        if (matrix.empty() || matrix[0].empty()) return;

        int rows = matrix.size();
        int cols = matrix[0].size();

        cout << "\n    ";
        for (int j = 0; j < cols; ++j)
            cout << setw(cell_width + 1) << j;
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";

        for (int i = 0; i < rows; ++i) {
            cout << setw(2) << i;
            if (i == 2)
                cout << " |";
            for (int j = 0; j < cols; ++j)
                if (i == 0 && j == 2) {
                    cout << " |" << setw(cell_width) << matrix[i][j] << " |";
                }
                else if (i == 1 && j == 1) {
                    cout << " |" << setw(cell_width) << matrix[i][j] << " |";
                }
                else if (i == 1 && (j == 2 || j == 3)) {
                    cout << setw(cell_width) << matrix[i][j] << " |";
                }
                else if (i == 2) {
                    cout << setw(cell_width) << matrix[i][j] << " |";
                }
                else {
                    cout << setw(cell_width) << "     ";
                }

            cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
        }
        cout << endl;
    }
};

#endif //PYRAMID_TIC_TAC_TOE_H