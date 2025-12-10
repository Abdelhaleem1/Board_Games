/**
 * @file Word_TicTacToe.h
 * @brief Header for the Word Tic-Tac-Toe game variant.
 *
 * Defines classes for a Tic-Tac-Toe game where players place letters
 * to form valid English words. Victory is achieved by creating a valid
 * 3-letter word in any row, column, or diagonal.
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
     */
    bool is_win(Player<char>* player) override;

    /**
     * @brief Checks if the given player has lost the game.
     * @param player Pointer to the player being checked
     * @return Always returns false (not used in word variant)
     */
    bool is_lose(Player<char>* player) override { return false; };

    /**
     * @brief Checks if the game has ended in a draw.
     *
     * A draw occurs when all 9 cells are filled and no valid word was formed.
     *
     * @param player Pointer to the player being checked
     * @return true if board is full and no valid words, false otherwise
     */
    bool is_draw(Player<char>* player) override;

    /**
     * @brief Determines if the game is over.
     * @param player Pointer to the player to evaluate
     * @return true if the game has ended (win or draw), false otherwise
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
     */
    bool checkinFile(string& target);

    /**
     * @brief Loads valid words from dictionary file.
     *
     * Opens "dic.txt" and reads all words into the internal set for
     * fast lookup during gameplay. Must be called during initialization.
     *
     * @throws runtime_error if "dic.txt" file cannot be opened
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
 * @see UI
 */
class word_XO_UI : public UI<char> {
public:
    /**
     * @brief Constructs a word_XO_UI object.
     *
     * Initializes the base `UI<char>` class with the welcome message
     * for Word Tic-Tac-Toe and board size of 3.
     */
    word_XO_UI();

    /**
     * @brief Destructor for word_XO_UI.
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
     */
    virtual Move<char>* get_move(Player<char>* player);

    /**
     * @brief Sets up both players for the word game.
     *
     * Overrides default setup to assign '-' symbols to both players
     * since they place letters rather than X/O symbols.
     *
     * @return Pointer to array of two Player pointers
     */
    Player<char>** setup_players() override;
};
