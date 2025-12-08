#include <iostream>
#include <iomanip>
#include <cctype>
#include "Pyramid_Tic_Tac_Toe.h"

using namespace std;

//--------------------------------------- X_O_Board Implementation

Pyramid_XO_Board::Pyramid_XO_Board() : Board(3, 5) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Pyramid_XO_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

bool Pyramid_XO_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    if ((all_equal(board[1][1], board[1][2], board[1][3]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][2], board[2][2]) && board[0][2] == sym))
        return true;
    for (int i = 0; i < 3; i++) {
        if (all_equal(board[2][i], board[2][i+1], board[2][i+2]) && board[2][i] == sym)
            return true;
    }


    // Check diagonals
    if ((all_equal(board[0][2], board[1][3], board[2][4]) && board[0][2] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool Pyramid_XO_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Pyramid_XO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

Pyramid_XO_UI::Pyramid_XO_UI() : UI<char>("Weclome to FCAI X-O Game by Dr El-Ramly", 3) {}

Player<char>* Pyramid_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* Pyramid_XO_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
        while ((x == 0 && y != 2) || (x == 1 && (y == 0 || y == 4))) {
            cout<<"\nInvalid Move! Please enter your move x and y: ";
            cin >> x >> y;
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
        while ((x == 0 && y != 2) || (x == 1 && (y == 0 || y == 4))) {
            x = rand() % player->get_board_ptr()->get_rows();
            y = rand() % player->get_board_ptr()->get_columns();
        }
    }
    return new Move<char>(x, y, player->get_symbol());
}
