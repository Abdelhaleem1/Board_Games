/**
 * @file Word_TicTacToe.h
 * @brief Header for the Word Tic-Tac-Toe game variant.
 *
 * Defines classes for a Tic-Tac-Toe game where players place letters
 * to form valid English words. Victory is achieved by creating a valid
 * 3-letter word in any row, column, or diagonal.
 *
 * @details
 * This innovative variant transforms traditional Tic-Tac-Toe into a word game:
 * - Players place any letter A-Z instead of X or O
 * - Win by forming a valid 3-letter English word
 * - Words can be horizontal, vertical, or diagonal
 * - Words validated against an external dictionary file (dic.txt)
 * - Words can be read forward or backward
 *
 * Game Features:
 * - Dictionary-based validation ensures only real words count
 * - Strategic letter placement required
 * - Both vocabulary and spatial reasoning needed
 * - Support for undo operations
 * - Draw occurs when board fills without forming valid words
 *
 * Example winning words: CAT, DOG, THE, ARE, etc.
 */

#pragma once

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class word_XO_Board
 * @brief Represents a Word-based Tic-Tac-Toe game board.
 *
 * This variant allows players to place any letter (A-Z) on the board.
 * Victory is achieved by forming a valid 3-letter English word in any
 * row, column, or diagonal. Words are validated against a dictionary file.
 *
 * @details
 * Board Mechanics:
 * - Standard 3x3 grid (9 cells)
 * - Each cell can contain any uppercase letter A-Z
 * - Empty cells represented by '.'
 * - All letters automatically converted to uppercase
 * - Dictionary loaded once during initialization for efficiency
 *
 * Win Condition:
 * - Complete any row, column, or diagonal with letters
 * - Resulting 3-letter sequence must be a valid English word
 * - Words checked in both forward and reverse directions
 * - First valid word formation wins the game
 *
 * Dictionary System:
 * - Words loaded from "dic.txt" file into unordered_set for O(1) lookup
 * - File must contain one word per line
 * - Case-insensitive matching (all stored as uppercase)
 * - Supports both forward and reversed word validation
 *
 * Strategic Considerations:
 * - Players must think about letter combinations
 * - Blocking opponent requires vocabulary knowledge
 * - Multiple winning paths possible simultaneously
 * - Letter placement affects multiple potential words
 *
 * @see Board
 */
class word_XO_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character representing an empty cell on the board
    ifstream file; ///< File stream for reading dictionary file
    unordered_set<string> words; ///< Set of valid English words loaded from dictionary

public:
    /**
     * @brief Default constructor that initializes a 3x3 word board.
     *
     * Initializes all cells to blank and loads the word dictionary
     * from "dic.txt" file for word validation.
     *
     * @details
     * Construction process:
     * 1. Initializes 3x3 grid with blank symbols ('.')
     * 2. Sets move counter to 0
     * 3. Calls loadWords() to populate the dictionary from "dic.txt"
     * 4. Prepares board for immediate gameplay
     *
     * @note Dictionary file "dic.txt" must exist in the working directory
     * @throws May throw exceptions if dictionary file cannot be loaded
     *
     * @see loadWords() for dictionary loading details
     */
    word_XO_Board();

    /**
     * @brief Updates the board with a letter placement.
     *
     * Places the letter (converted to uppercase) at the specified position
     * if the cell is empty. Supports undo operations.
     *
     * @param move Pointer to a Move<char> object containing coordinates and letter
     * @return true if the move is valid and successfully applied, false otherwise
     *
     * @details
     * Move Validation:
     * - Checks if coordinates are within bounds (0-2 for both row and column)
     * - Verifies target cell is empty (contains blank_symbol)
     * - Accepts any alphabetic character (A-Z, a-z)
     * - Automatically converts lowercase to uppercase
     *
     * Special Features:
     * - Supports undo by allowing placement at non-empty cells in specific contexts
     * - Updates move counter on successful placement
     * - Stores uppercase version of letter for consistency
     *
     * Invalid moves:
     * - Out of bounds coordinates
     * - Occupied cells (in normal play mode)
     * - Non-alphabetic characters
     *
     * @note Letters are automatically uppercased before storage
     * @warning Does not validate if letter forms a word; that's checked separately
     */
    bool update_board(Move<char>* move) override;

    /**
     * @brief Checks if a valid word has been formed.
     *
     * Examines all rows, columns, and diagonals for complete 3-letter sequences.
     * Validates each complete sequence against the loaded dictionary.
     *
     * @param player Pointer to the player being checked
     * @return true if a valid word exists in any line, false otherwise
     *
     * @details
     * Checking Algorithm:
     * 1. Scans all 3 rows (horizontal words)
     * 2. Scans all 3 columns (vertical words)
     * 3. Checks main diagonal (top-left to bottom-right)
     * 4. Checks anti-diagonal (top-right to bottom-left)
     *
     * For each complete line:
     * - Extracts 3-character sequence
     * - Skips lines with blank cells
     * - Validates against dictionary using checkinFile()
     * - Checks both forward and reverse spellings
     *
     * Example winning scenarios:
     * @code
     * Row win:     C A T
     *              . . .
     *              . . .
     *
     * Column win:  D . .
     *              O . .
     *              G . .
     *
     * Diagonal:    T . .
     *              . H .
     *              . . E
     * @endcode
     *
     * @note Any player can win regardless of who placed which letters
     * @note Words can be read forward or backward
     * @see checkinFile() for dictionary validation logic
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the given player has lost the game.
     *
     * @param player Pointer to the player being checked
     * @return Always returns false (not used in word variant)
     *
     * @details
     * In Word Tic-Tac-Toe, there is no explicit lose condition.
     * Both players contribute letters to the board, and any valid word
     * formation ends the game. The concept of individual player loss
     * doesn't apply to this cooperative/competitive hybrid variant.
     */
    bool is_lose(Player<char>* player) override { return false; };

    /**
     * @brief Checks if the game has ended in a draw.
     *
     * A draw occurs when all 9 cells are filled and no valid word was formed.
     *
     * @param player Pointer to the player being checked
     * @return true if board is full and no valid words, false otherwise
     *
     * @details
     * Draw Conditions:
     * - All 9 cells contain letters (no blank symbols)
     * - No row, column, or diagonal forms a valid dictionary word
     * - Neither forward nor reverse reading produces valid words
     *
     * This is relatively common in word variant because:
     * - Players may intentionally avoid completing words
     * - Random letter combinations often don't form words
     * - Strategic blocking can prevent word formation
     *
     * Example draw scenario:
     * @code
     * X Q Z
     * F K J
     * B V W
     * // No valid 3-letter words in any direction
     * @endcode
     *
     * @note Checks is_win() first to ensure no valid word exists
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game is over.
     *
     * @param player Pointer to the player to evaluate
     * @return true if the game has ended (win or draw), false otherwise
     *
     * @details
     * Game ending conditions:
     * - A valid 3-letter word has been formed (win)
     * - All 9 cells are filled without forming a word (draw)
     *
     * @note Should be called after each move to check game status
     */
    bool game_is_over(Player<char>* player) override;

    /**
     * @brief Checks if a word exists in the dictionary.
     *
     * Validates the word or its reverse spelling against the loaded
     * dictionary to handle both normal and reversed valid words.
     *
     * @param target Reference to the string to validate
     * @return true if word or its reverse is in dictionary, false otherwise
     *
     * @details
     * Validation Process:
     * 1. Checks if target string exists in words set (O(1) lookup)
     * 2. If not found, creates reversed version of target
     * 3. Checks if reversed string exists in words set
     * 4. Returns true if either direction matches a dictionary word
     *
     * This dual-direction check allows words to be formed:
     * - Left-to-right or right-to-left (rows)
     * - Top-to-bottom or bottom-to-top (columns)
     * - Along either diagonal direction
     *
     * Examples:
     * - "CAT" is valid (normal)
     * - "TAC" is valid if "CAT" is in dictionary (reversed)
     * - "DOG" forward = "GOD" backward (both valid if in dictionary)
     *
     * @note Assumes words set contains uppercase strings only
     * @note Target should be uppercase before calling
     *
     * @see loadWords() for how dictionary is populated
     */
    bool checkinFile(string& target);

    /**
     * @brief Loads valid words from dictionary file.
     *
     * Opens "dic.txt" and reads all words into the internal set for
     * fast lookup during gameplay. Must be called during initialization.
     *
     * @throws runtime_error if "dic.txt" file cannot be opened
     *
     * @details
     * Loading Process:
     * 1. Opens "dic.txt" from current working directory
     * 2. Reads file line by line
     * 3. Converts each word to uppercase for case-insensitive matching
     * 4. Inserts words into unordered_set for O(1) lookup performance
     * 5. Closes file after loading complete
     *
     * Dictionary File Format:
     * - One word per line
     * - Any case (will be converted to uppercase)
     * - No special formatting required
     * - Recommended: only 3-letter words for efficiency (optional)
     *
     * Performance Considerations:
     * - Uses unordered_set for constant-time word lookups
     * - All words loaded at construction time (one-time cost)
     * - Memory usage proportional to dictionary size
     *
     * Error Handling:
     * - Throws exception if file not found or cannot be opened
     * - Should be caught during board construction
     * - Game cannot proceed without valid dictionary
     *
     * Example dic.txt content:
     * @code
     * CAT
     * DOG
     * THE
     * ARE
     * BAT
     * @endcode
     *
     * @note File must be named exactly "dic.txt"
     * @note File must be in the working directory or provide full path
     * @warning Large dictionaries increase memory usage but improve gameplay
     */
    void loadWords();
};


/**
 * @class word_XO_UI
 * @brief User Interface class for the Word Tic-Tac-Toe game.
 *
 * Inherits from the generic `UI<char>` base class and provides
 * word-specific functionality for player setup and move input.
 * Players place letters instead of X/O symbols.
 *
 * @details
 * UI Responsibilities:
 * - Display the 3x3 grid with current letters
 * - Prompt players for position and letter choice
 * - Validate input format (coordinates and letter)
 * - Convert letters to uppercase automatically
 * - Show game status and available moves
 *
 * Player Setup:
 * - Both players assigned '-' symbol (not X or O)
 * - Players distinguished by name, not symbol
 * - Any player's letters can contribute to winning word
 *
 * Move Input:
 * - Row: 0-2
 * - Column: 0-2
 * - Letter: Any A-Z (case-insensitive)
 *
 * The UI emphasizes the word-formation aspect rather than
 * traditional player-vs-player competition.
 *
 * @see UI
 */
class word_XO_UI : public UI<char> {
public:
    /**
     * @brief Constructs a word_XO_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message
     * for Word Tic-Tac-Toe and board size of 3.
     *
     * @details
     * Sets up the UI with:
     * - Game title: typically "Word Tic-Tac-Toe"
     * - Board dimension: 3 (for 3x3 grid)
     * - Prepares for letter-based input rather than X/O
     *
     * The UI is ready to handle player setup and move collection
     * immediately after construction.
     */
    word_XO_UI();

    /**
     * @brief Destructor for word_XO_UI.
     *
     * Cleans up any resources allocated by the UI.
     * Currently performs no special cleanup operations.
     */
    ~word_XO_UI() {};

    /**
     * @brief Creates a player of the specified type.
     *
     * Note: In word variant, players don't use traditional X/O symbols.
     * They are assigned '-' symbol since they place letters.
     *
     * @param name Name of the player
     * @param symbol Character symbol assigned (typically '-' for word variant)
     * @param type The type of the player (Human or Computer)
     * @return Pointer to the newly created Player<char> instance
     *
     * @details
     * Player Creation:
     * - Human players: prompt for each move (position + letter)
     * - Computer players: generate random or strategic moves
     * - Both types use '-' as their player symbol
     * - Symbol not used for board display (actual letters shown instead)
     *
     * AI Considerations:
     * - AI must know valid 3-letter words
     * - Should attempt to complete words strategically
     * - May need access to dictionary for intelligent play
     * - Random AI just places random letters at random positions
     *
     * @warning Caller is responsible for deallocating the returned Player object
     * @note Symbol parameter typically ignored; '-' is assigned internally
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Retrieves the next move from a player.
     *
     * For human players: prompts for coordinates and a letter (A-Z).
     * For computer players: generates random coordinates and letter.
     * All letters are converted to uppercase.
     *
     * @param player Pointer to the player whose move is being requested
     * @return Pointer to a Move<char> object with position and chosen letter
     *
     * @details
     * Human Player Input:
     * - Prompts: "Enter row (0-2): "
     * - Prompts: "Enter column (0-2): "
     * - Prompts: "Enter letter (A-Z): "
     * - Validates all inputs
     * - Converts letter to uppercase
     *
     * Computer Player:
     * - Generates random row (0-2)
     * - Generates random column (0-2)
     * - Generates random letter (A-Z)
     * - Returns move immediately
     *
     * Input Validation:
     * - Row must be 0, 1, or 2
     * - Column must be 0, 1, or 2
     * - Letter must be alphabetic (A-Z or a-z)
     * - Non-alphabetic input rejected
     * - Re-prompts on invalid input
     *
     * Move Object:
     * - Contains row coordinate
     * - Contains column coordinate
     * - Contains uppercase letter as symbol
     *
     * Example interaction:
     * @code
     * Enter row (0-2): 1
     * Enter column (0-2): 1
     * Enter letter (A-Z): h
     * // Creates Move(1, 1, 'H')
     * @endcode
     *
     * @note Does not validate if cell is empty (handled by Board)
     * @note Does not validate if letter forms valid word (handled by Board)
     * @warning Caller is responsible for deallocating the returned Move object
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Sets up both players for the word game.
     *
     * Overrides default setup to assign '-' symbols to both players
     * since they place letters rather than X/O symbols.
     *
     * @return Pointer to array of two Player pointers
     *
     * @details
     * Setup Process:
     * 1. Prompts for Player 1 name and type
     * 2. Creates Player 1 with '-' symbol
     * 3. Prompts for Player 2 name and type
     * 4. Creates Player 2 with '-' symbol
     * 5. Returns array of both player pointers
     *
     * Special Features:
     * - Both players get same '-' symbol
     * - Players identified by name, not symbol
     * - Either player can contribute to winning word
     * - Emphasizes collaborative word formation
     *
     * Player Types Supported:
     * - Human: requires manual input each turn
     * - Computer: makes automatic moves (random or strategic)
     *
     * @note Both players use '-' regardless of traditional X/O assignment
     * @warning Caller is responsible for deallocating the returned array
     */
    Player<char>** setup_players() override;
};