#include <iostream>
#include <iomanip>
#include <cctype>
#include "TIC_TAC_TOE_4X4.h"

using namespace std;

XO_4x4_Board::XO_4x4_Board() : Board(4, 4) {

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == 0) {
                if (j%2 == 0) {board[i][j] = 'O';}
                else {board[i][j] = 'X';}
            }
            else if (i == 3) {
                if (j%2 == 1) {board[i][j] = 'O';}
                else {board[i][j] = 'X';}
            }
            else {board[i][j] = blank_symbol;}
        }
    }
}

bool XO_4x4_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    if (move->get_symbol() == board[x][y]) {
        mark = 0;
        xold = x;
        yold = y;
    }
    else if (board[x][y] == blank_symbol && mark == 0 && ((x == xold+1 && y == yold) || (x == xold-1 && y == yold)||
        (y == yold+1 && x == xold) || (y == yold-1 && x == xold))){mark = move->get_symbol();}
    else {return false;}

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

bool XO_4x4_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int j=0; j<2; ++j) {
        for (int i = 0; i < rows; ++i) {
            if ((all_equal(board[i][j], board[i][j+1], board[i][j+2]) && board[i][j] == sym) ||
                (all_equal(board[j][i], board[j+1][i], board[j+2][i]) && board[j][i] == sym))
                return true;
        }

    }


    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym) ||
        (all_equal(board[1][1], board[2][2], board[3][3]) && board[2][2] == sym) ||
        (all_equal(board[0][1], board[1][2], board[2][3]) && board[1][2] == sym) ||
        (all_equal(board[1][0], board[2][1], board[3][2]) && board[2][1] == sym) ||
        (all_equal(board[0][3], board[1][2], board[2][1]) && board[1][2] == sym) ||
        (all_equal(board[1][2], board[2][1], board[3][0]) && board[2][1] == sym) ||
        (all_equal(board[1][3], board[2][2], board[3][1]) && board[3][1] == sym))
        return true;

    return false;
}

bool XO_4x4_Board::is_draw(Player<char>* player) {return false;}

bool XO_4x4_Board::game_is_over(Player<char>* player) {
    return is_win(player);
}

//--------------------------------------- XO_UI Implementation

XO_4x4_UI::XO_4x4_UI() : UI<char>("Weclome to FCAI X-O Game by Dr El-Ramly", 3) {}

Player<char>* XO_4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* XO_4x4_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter x and y you move from (0 to 3): ";
        cin >> x >> y;

        player->get_board_ptr()->update_board(
        new Move<char>(x, y, player->get_symbol())
        );

        cout << "\nPlease enter your move x and y (0 to 3): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
        player->get_board_ptr()->update_board(
        new Move<char>(x, y, player->get_symbol())
        );
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}