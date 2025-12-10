#include <bits/stdc++.h>
#include "TicTacToe_5x5.h"


TicTacToe_5x5_board::TicTacToe_5x5_board() : Board(5, 5){
    for (auto& row : board)
        for (auto& cell : row) {
            cell = blank_symbol;
        }
}

bool TicTacToe_5x5_board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || symbol == 0)) {

        if (symbol == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else { // Apply move
            n_moves++;
            board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false;
}


void TicTacToe_5x5_board::consecutive_cells(char symbol) {
    // Horizontal
    for(int i=0;i<get_rows();i++) {
        int cnt = 0;
        for(int j=0;j<get_columns();j++) {
            if(get_cell(i,j) == symbol) {
                cnt++;
            }else {
                if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
                else cntO+= (cnt>=3) ? cnt-2 : 0;
                cnt=0;
            }
        }
        if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
        else cntO+= (cnt>=3) ? cnt-2 : 0;
    }
    // vertical
    for(int j=0;j<get_columns();j++) {
        int cnt = 0;
        for(int i=0;i<get_rows();i++) {
            if(get_cell(i,j) == symbol) {
                cnt++;
            }else {
                if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
                else cntO+= (cnt>=3) ? cnt-2 : 0;
                cnt=0;
            }
        }
        if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
        else cntO+= (cnt>=3) ? cnt-2 : 0;
    }
    // Main diagonals (top-left to bottom-right) starting from top row
    for(int start = 0 ;start<=2;start++) {
        int cnt=0;
        for(int i=0, j = start; i<get_rows() && j<get_columns();i++, j++) {
            if(get_cell(i,j) == symbol) {
                cnt++;
            }else {
                if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
                else cntO+= (cnt>=3) ? cnt-2 : 0;
                cnt=0;
            }
        }
        if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
        else cntO+= (cnt>=3) ? cnt-2 : 0;
    }

    // Main diagonals starting from left column (below top-left)
    for(int start = 1 ;start<=2;start++) {
        int cnt=0;
        for(int i=start, j = 0; i<get_rows() && j<get_columns();i++, j++) {
            if(get_cell(i,j) == symbol) {
                cnt++;
            }else {
                if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
                else cntO+= (cnt>=3) ? cnt-2 : 0;
                cnt=0;
            }
        }
        if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
        else cntO+= (cnt>=3) ? cnt-2 : 0;
    }
    // Anti-diagonals (top-right to bottom-left) starting from top row
    for(int start = 4 ;start>=2;start--) {
        int cnt=0;
        for(int i=0, j = start; i<get_rows() && j>=0 ;i++, j--) {
            if(get_cell(i,j) == symbol) {
                cnt++;
            }else {
                if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
                else cntO+= (cnt>=3) ? cnt-2 : 0;
                cnt=0;
            }
        }
        if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
        else cntO+= (cnt>=3) ? cnt-2 : 0;
    }

    // Anti-diagonals starting from right column (below top-right)
    for(int start = 1 ;start<=2;start++) {
        int cnt=0;
        for(int i=start, j = 4; i<get_rows() && j>=0 ;i++, j--) {
            if(get_cell(i,j) == symbol) {
                cnt++;
            }else {
                if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
                else cntO+= (cnt>=3) ? cnt-2 : 0;
                cnt=0;
            }
        }
        if(symbol == 'X') cntX+= (cnt>=3) ? cnt-2 : 0;
        else cntO+= (cnt>=3) ? cnt-2 : 0;
    }
}

bool TicTacToe_5x5_board::is_win(Player<char>* player) {
    if (names.size() <2) names.push_back(player->get_name());
    if (get_n_moves() == 24) {
      // The last move is for player 'O'.
        consecutive_cells('X');
        consecutive_cells('O');
        if (cntO > cntX) {
            cout<<"\n"<< names.front() <<" (X) has "<< cntX << " three-in-a-row sequence(s)";
            cout<<"\n"<< names.back() <<" (O) has "<< cntO << " three-in-a-row sequence(s)\n";
            return true;
        }
    };
    return false;
}

bool TicTacToe_5x5_board::is_lose(Player<char>* player) {
    if (get_n_moves() == 24) {
        // The last move is for player 'O'
        if(cntO < cntX) {
            cout<<"\n"<< names.front() <<" (X) has "<< cntX << " three-in-a-row sequence(s)";
            cout<<"\n"<< names.back() <<" (O) has "<< cntO << " three-in-a-row sequence(s)\n";
            return true;
        }
    }
    return false;
}

bool TicTacToe_5x5_board::is_draw(Player<char>* player) {
    if (get_n_moves() == 24) {
        if(cntO == cntX) {
            cout<<"\n"<< names.front() <<" (X) has "<< cntX << " three-in-a-row sequence(s)";
            cout<<"\n"<< names.back() <<" (O) has "<< cntO << " three-in-a-row sequence(s)\n";
            return true;
        }
    }
    return false;
}

bool TicTacToe_5x5_board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player) || is_lose(player);
}


TicTacToe_5x5_UI::TicTacToe_5x5_UI() : UI<char>("Welcome to 5x5 Tic-Tac-Toe Game", 5) {}

Player<char>* TicTacToe_5x5_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

Move<char>* TicTacToe_5x5_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\n"<< player->get_name() <<" (" << player->get_symbol() <<")" <<", please enter your move x and y (0 to 4): ";
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


