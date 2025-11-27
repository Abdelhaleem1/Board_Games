#include "Inverse_XO_UI.h"
#include <iostream>
#include <cctype>
#include <limits>
#include <cstdlib>

using namespace std;

Inverse_XO_UI::Inverse_XO_UI() : UI<char> ("Inverse (Misere) Tic-Tac-Toe: Avoid creating three-in-a-row, you lose if you do.", 3) {}

Player<char>* Inverse_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "(Inverse) Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
         << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* Inverse_XO_UI::get_move(Player<char>* player) {
    Board<char>* board = player->get_board_ptr();
    int rows = board->get_rows();
    int cols = board->get_columns();

    if (player->get_type() == PlayerType::HUMAN) {
        while (true) {
            int x, y;
            cout << "\nEnter your move x y (0 to " << rows - 1 << "): ";
            if (!(cin >> x >> y)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Try again.\n";
                continue;
            }
            if (x < 0 || x >= rows || y < 0 || y >= cols) { cout << "Out of range. Try again.\n"; continue; }

            // accept both '.' and ' ' as "empty" because X_O_Board uses '.' while other boards may use ' '
            char cur = board->get_cell(x, y);
            if (cur != '.' && cur != static_cast<char>(' ')) { cout << "Cell occupied. Try again.\n"; continue; }

            if (would_lose_if_move(player, x, y)) {
                cout << "Warning: placing '" << player->get_symbol() << "' at (" << x << "," << y
                     << ") WILL create three-in-a-row and you will lose.\n";
                cout << "Make this move anyway? (y/n): ";
                char c; cin >> c;
                if (c == 'y' || c == 'Y') return new Move<char>(x, y, player->get_symbol());
                else { cout << "Choose a different move.\n"; continue; }
            }
            return new Move<char>(x, y, player->get_symbol());
        }
    }
    else { // COMPUTER: prefer safe moves when possible
        vector<pair<int,int>> all_moves;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                char cur = board->get_cell(i, j);
                if (cur == '.' || cur == static_cast<char>(' ')) all_moves.emplace_back(i, j);
            }

        vector<pair<int,int>> safe;
        for (auto &m : all_moves)
            if (!would_lose_if_move(player, m.first, m.second)) safe.push_back(m);

        if (!safe.empty()) {
            auto sel = safe[rand() % safe.size()];
            return new Move<char>(sel.first, sel.second, player->get_symbol());
        }
        if (!all_moves.empty()) {
            auto sel = all_moves[rand() % all_moves.size()];
            return new Move<char>(sel.first, sel.second, player->get_symbol());
        }
        // fallback (shouldn't happen)
        return new Move<char>(0, 0, player->get_symbol());
    }
}

bool Inverse_XO_UI::would_lose_if_move(Player<char>* player, int x, int y) const {
    Board<char>* board = player->get_board_ptr();
    char sym = player->get_symbol();

    // Helper returns the value of cell (r,c) assuming (x,y) would be sym
    auto cell = [&](int r, int c)->char {
        if (r == x && c == y) return sym;
        return board->get_cell(r, c);
    };

    int N = board->get_rows(); // 3 expected
    // rows
    for (int r = 0; r < N; ++r)
        if (cell(r, 0) == sym && cell(r, 1) == sym && cell(r, 2) == sym) return true;
    // cols
    for (int c = 0; c < N; ++c)
        if (cell(0, c) == sym && cell(1, c) == sym && cell(2, c) == sym) return true;
    // diags
    if (cell(0, 0) == sym && cell(1, 1) == sym && cell(2, 2) == sym) return true;
    if (cell(0, 2) == sym && cell(1, 1) == sym && cell(2, 0) == sym) return true;

    return false;
}