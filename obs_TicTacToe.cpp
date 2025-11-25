#include <bits/stdc++.h>
#include "obs_TicTacToe.h"


obs_TicTacToe_board::obs_TicTacToe_board() : Board(6, 6), last_col_play(0), last_row_play(0) {
    for (int i=0;i<6;i++) {
        for (int j=0;j<6;j++) {
            coordinates.emplace_back(i,j);
        }
    }
    for (auto& row : board)
        for (auto& cell : row) {
            cell = blank_symbol;
        }
}

bool obs_TicTacToe_board::update_board(Move<char>* move) {
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
        else { // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
            auto it = find(coordinates.begin(), coordinates.end(), make_pair(x, y));
            if (it != coordinates.end()) coordinates.erase(it);
            random_obs();
            last_row_play =x;
            last_col_play =y;
        }

        return true;
    }
    return false;
}

void obs_TicTacToe_board::random_obs() {
    for(int i=0;i<2;i++) {
        if (coordinates.empty()) break;
        int rand_coordinate = (rand() % coordinates.size());
        board[coordinates[rand_coordinate].first][coordinates[rand_coordinate].second] = obstacle_symbol;
        coordinates.erase(coordinates.begin() + rand_coordinate);
    }
}

int obs_TicTacToe_board::check_win(int x, int y, int dr, int dc, char sym) {
    int count = 0;
    int r = x + dr;
    int c = y + dc;
    while (r >= 0 && r < 6 && c >= 0 && c < 6 && board[r][c] == sym) {
        count++;
        r += dr;
        c += dc;
    }
    return count;
}



bool obs_TicTacToe_board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();
    int x = last_row_play;
    int y = last_col_play;
    if (check_win(x, y, 0, -1, sym) + check_win(x, y, 0, 1, sym) + 1 >= 4)
        return true;
    if (check_win(x, y, -1, 0, sym) + check_win(x, y, 1, 0, sym) + 1 >= 4)
        return true;
    if (check_win(x, y, -1, -1, sym) + check_win(x, y, 1, 1, sym) + 1 >= 4)
    return true;
    if (check_win(x, y, -1, 1, sym) + check_win(x, y, 1, -1, sym) + 1 >= 4)
        return true;
    return false;
}

bool obs_TicTacToe_board::isFull() {
    for (auto& row : board)
        for (auto& cell : row) {
            if(cell == blank_symbol) {
                return false;
            }
        }
    return true;
}

bool obs_TicTacToe_board::is_draw(Player<char>* player) {
    return (isFull() && !is_win(player));
}

bool obs_TicTacToe_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}




obs_TicTacToe_UI::obs_TicTacToe_UI() : UI<char>("Weclome to Obstacles Tic-Tac-Toe Game", 6) {}

Player<char>* obs_TicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* obs_TicTacToe_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n"<< player->get_name() <<"(" << player->get_symbol() <<")" <<", please enter your move x and y (0 to 2): ";
        while (true) {
            cin >> x >> y;
            if (cin.fail()){
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