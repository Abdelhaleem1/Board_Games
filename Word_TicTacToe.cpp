#include <bits/stdc++.h>
#include "Word_TicTacToe.h"

using namespace std;

word_XO_Board::word_XO_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
    loadWords();
}


bool word_XO_Board::update_board(Move<char>* move) {
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
        }

        return true;
    }
    return false;
}

bool word_XO_Board::is_win(Player<char>* player) {

    // Check rows and columns

    for (int i = 0; i < rows; ++i) {
        string row_word = { board[i][0], board[i][1], board[i][2] };
        string col_word = {board[0][i], board[1][i], board[2][i] };
        if((row_word.find(blank_symbol) == string::npos && checkinFile(row_word)) ||
           (col_word.find(blank_symbol) == string::npos && checkinFile(col_word)) ) {
            return true;
        }
    }

    string mainDiagonal = {board[0][0], board[1][1], board[2][2]};
    string subdiagonal = {board[0][2], board[1][1], board[2][0]};
    // Check diagonals
    if ((mainDiagonal.find(blank_symbol) == string::npos && checkinFile(mainDiagonal)) ||
           (subdiagonal.find(blank_symbol) == string::npos && checkinFile(subdiagonal)))
        return true;

    return false;
}



bool word_XO_Board::is_draw(Player<char>* player) {
    return (n_moves==9 && !is_win(player));
}

bool word_XO_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

void word_XO_Board::loadWords() {
    file.open("dic.txt");
    if (!file.is_open()) {
        throw runtime_error("dic.txt not found!");
    }
    string word;
    while (getline(file, word))
        words.insert(word);
    file.close();
}


bool word_XO_Board::checkinFile(string& target) {
    string rev = target;
    reverse(rev.begin(), rev.end());

    if (words.contains(target) || words.contains(rev))
        return true;
    return false;
}


//--------------------------------------- word_XO_UI Implementation


word_XO_UI::word_XO_UI() : UI<char>("Weclome to Word Tic-Tac-Toe Game", 3) {}

Player<char>* word_XO_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << "\n";

    return new Player<char>(name, symbol, type);
}

Player<char> **word_XO_UI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    vector<string> type_options = { "Human", "Computer" };

    string nameX = get_player_name("Player 1");
    PlayerType typeX = get_player_type_choice("Player 1", type_options);
    players[0] = create_player(nameX, static_cast<char>('-'), typeX);

    string nameO = get_player_name("Player 2");
    PlayerType typeO = get_player_type_choice("Player 2", type_options);
    players[1] = create_player(nameO, static_cast<char>('-'), typeO);

    return players;
}


Move<char>* word_XO_UI::get_move(Player<char>* player) {
    int x, y;
    char letter;
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n"<< player->get_name() <<", please enter your move x and y (0 to 2): ";
        while (true) {
            cin >> x >> y;
            if (cin.fail()){
                cout << "Invalid input! Please enter a number\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else break;
        }
        cout << "Enter a letter between (A-Z): ";
        string z;
        cin >> z;
        z[0] = toupper(z[0]);
        while (z[0] < 'A' || z[0] > 'Z' || z.size() != 1) {
            cout << "Please enter a valid input: ";
            cin >> z;
            z[0] = toupper(z[0]);
        }
        letter = z[0];
    }

    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % 3;
        y = rand() % 3;
        letter = 'A' + (rand() % 26);
    }
    return new Move<char>(x, y, letter);
}
