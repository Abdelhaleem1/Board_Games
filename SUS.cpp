#include <iostream>
#include <cctype>
#include <algorithm>
#include "SUS.h"

using namespace std;

//--------------------------------------- SUS_Board Implementation

SUS_Board::SUS_Board() : Board(3, 3) {
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool SUS_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

        if (mark == 0)
        {
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else
        {
            last_row_play = x;
            last_col_play = y;
            n_moves++;
            board[x][y] = toupper(mark);
            condition(x, y, toupper(mark));
        }
        return true;
    }
    return false;
}

bool SUS_Board::is_win(Player<char>* player) {
    if (n_moves == 9)
    {
        if (count1 > count2)
            return true;
    }
    return false;
}

bool SUS_Board::is_lose(Player<char>* player) {
    if (n_moves == 9)
    {
        if (count1 < count2)
            return true;
    }
    return false;
}

bool SUS_Board::is_draw(Player<char>* player) {
    return n_moves == 9 && count1 == count2;
}

bool SUS_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player) || is_lose(player);
}



Player<char>** SUS_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player 1");
    PlayerType typeX = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(nameX, 'S', typeX);
    string nameO = get_player_name("Player 2");
    PlayerType typeO = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(nameO, 'U', typeO);

    return players;
}

Player<char>* SUS_UI::create_player(string& name, char symbol, PlayerType type)
{
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* SUS_UI::get_move(Player<char>* player)
{
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n" << player->get_name() << "(" << player->get_symbol() << ")" << ", please enter your move x and y (0 to 2): ";
        while (true) {
            cin >> x >> y;
            if (cin.fail()) {
                cout << "Invalid input! Please enter a number\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else break;
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

void SUS_Board::condition(int x, int y, char symbol) {
    string word = "";
    for (int i = 0; i < 3; i++) {
        word += board[x][i];
    }
    if (word == "SUS") {
        if (symbol == 'S')
            count1++;
        else count2++;
    }
    word = "";
    for (int i = 0; i < 3; i++) {
        word += board[i][y];
    }
    if (word == "SUS") {
        if (symbol == 'S')
            count1++;
        else count2++;
    }
    word = "";
    if (x == y) {
        for (int i = 0; i < 3; i++) {
            word += board[i][i];
        }
    }
    if (word == "SUS") {
        if (symbol == 'S')
            count1++;
        else count2++;
    }
    word = "";
    if (x + y == 2) {
        for (int i = 0; i < 3; i++) {
            word += board[i][2 - i];
        }
    }
    if (word == "SUS") {
        if (symbol == 'S')
            count1++;
        else count2++;
    }
}