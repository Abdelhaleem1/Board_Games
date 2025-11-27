//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "NUMERICAL_TIC_TAC_TOE.h"

using namespace std;

//--------------------------------------- X_O_Board Implementation

Numerical_XO_Board::Numerical_XO_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool Numerical_XO_Board::update_board(Move<char>* move) {
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

bool Numerical_XO_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();


    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if (((board[i][0] + board[i][1] + board[i][2] == 159) && board[i][0]!=blank_symbol
            && board[i][1]!=blank_symbol && board[i][2]!=blank_symbol) ||
            ((board[0][i] + board[1][i] + board[2][i] == 159) && board[0][i]!=blank_symbol
            && board[1][i]!=blank_symbol && board[2][i]!=blank_symbol)) {
            return true;
        }
    }

    // Check diagonals
    if (((board[0][0] + board[1][1] + board[2][2] == 159) && board[0][0]!=blank_symbol
        && board[1][1]!=blank_symbol && board[2][2]!=blank_symbol) ||
        ((board[0][2] + board[1][1] + board[2][0] == 159) && board[0][2] != blank_symbol
        && board[1][1] != blank_symbol && board[2][0] != blank_symbol))
        return true;

    return false;
}

bool Numerical_XO_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool Numerical_XO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

Numerical_XO_UI::Numerical_XO_UI() : UI<char>("Weclome to FCAI X-O Game by Dr El-Ramly", 3) {}

Player<char>* Numerical_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << "\n";

    return new Player<char>(name, symbol, type);
}

Player<char> **Numerical_XO_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameO = get_player_name("Player 1");
    PlayerType typeO = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(nameO, 'O', typeO);

    string nameX = get_player_name("Player 2");
    PlayerType typeX = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(nameX, 'X', typeX);

    return players;
}


Move<char>* Numerical_XO_UI::get_move(Player<char>* player) {
    int x, y, cnt = 0;
    char num;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
        cout << "\nPlease enter a number: ";
        cin >> num;
        for (auto i : nums) {
            if (i == num)
                cnt++;
        }
        if (player->get_symbol() == 'X') {
            while (!(num == '2' || num == '4' || num == '6' || num == '8') || cnt != 0) {
                cout << "\nPlease enter a valid number: ";
                cin >> num;
                cnt = 0;
                for (auto i : nums) {
                    if (i == num)
                        cnt++;
                }
            }
        }else {
            while (!(num == '1' || num == '3' || num == '5' || num == '7' || num == '9') || cnt != 0) {
                cout << "\nPlease enter a valid number: ";
                cin >> num;
                cnt = 0;
                for (auto i : nums) {
                    if (i == num)
                        cnt++;
                }
            }
        }
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
        if (player->get_symbol() == 'X') {
            char even[4] = {'2', '4', '6', '8'};
            num = even[rand() % 4];
            for (auto i : nums) {
                if (i == num)
                    cnt++;
            }
            while (cnt != 0) {
                num = even[rand() % 4];
                cnt = 0;
                for (auto i : nums) {
                    if (i == num)
                        cnt++;
                }
            }
        }else {
            char odd[5] = {'1', '3', '5', '7', '9'};
            num = odd[rand() % 5];
            for (auto i : nums) {
                if (i == num)
                    cnt++;
            }
            while (cnt != 0) {
                num = odd[rand() % 5];
                cnt = 0;
                for (auto i : nums) {
                    if (i == num)
                        cnt++;
                }
            }
        }
    }
    nums.push_back(num);
    return new Move<char>(x, y, num);
}
