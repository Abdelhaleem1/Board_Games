#include <iostream>
#include <cctype>
#include <algorithm>
#include "connect4.h"

using namespace std;

//--------------------------------------- connect4_Board Implementation

CONNECT_Board::CONNECT_Board() : Board(6, 7) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool CONNECT_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        return false;
    }

    if (board[x][y] == blank_symbol || mark == 0) {
        if (mark == 0)
        {
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else
        {
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }

    return false;
}

bool CONNECT_Board::is_win(Player<char>* player) {

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == player->get_symbol() &&
                board[i][j + 1] == player->get_symbol() &&
                board[i][j + 2] == player->get_symbol() &&
                board[i][j + 3] == player->get_symbol())

                return true;
        }
    }

    for (int j = 0; j < 7; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][j] == player->get_symbol() &&
                board[i + 1][j] == player->get_symbol() &&
                board[i + 2][j] == player->get_symbol() &&
                board[i + 3][j] == player->get_symbol())

                return true;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == player->get_symbol() &&
                board[i + 1][j + 1] == player->get_symbol() &&
                board[i + 2][j + 2] == player->get_symbol() &&
                board[i + 3][j + 3] == player->get_symbol())

                return true;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 3; j < 7; j++)
        {
            if (board[i][j] == player->get_symbol() &&
                board[i + 1][j - 1] == player->get_symbol() &&
                board[i + 2][j - 2] == player->get_symbol() &&
                board[i + 3][j - 3] == player->get_symbol())

                return true;

        }
    }
    return false;
}

bool CONNECT_Board::is_lose(Player<char>* player) {
    return(n_moves == 42 && !is_win(player));
}

bool CONNECT_Board::is_draw(Player<char>* player) {
    return (n_moves == 42 && !is_win(player));
}

bool CONNECT_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}



Player<char>** CONNECT_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player 1");
    PlayerType typeX = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(nameX, 'X', typeX);
    string nameO = get_player_name("Player 2");
    PlayerType typeO = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(nameO, 'O', typeO);

    return players;
}

Player<char>* CONNECT_UI::create_player(string& name, char symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* CONNECT_UI::get_move(Player<char>* player)
{
    int column;
    Board<char>* board = player->get_board_ptr();

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << " (" << player->get_symbol() << ")"
            << ", enter column number (0-6): ";
        while (true) {
            cin >> column;
            if (cin.fail() || column < 0 || column >= 7) {
                cout << "Invalid input! Please enter a column number between 0 and 6: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (board->get_board_matrix()[0][column] != '.') {
                cout << "Column " << column << " is full! Please choose another column: ";
            }
            else {
                break;
            }
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Keep trying until we find a column that's not full
        do {
            column = rand() % 7;
        } while (board->get_board_matrix()[0][column] != '.');

    }

    // Find the lowest empty row in the chosen column
    int row = -1;
    for (int r = 5; r >= 0; r--) {  // Start from bottom row
        if (board->get_cell(r, column) == '.')
        {
            row = r;
            break;  // Found the lowest empty position
        }
    }

    return new Move<char>(row, column, player->get_symbol());
}
