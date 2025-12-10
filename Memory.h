#pragma once

#include "BoardGame_Classes.h"

using namespace std;

class Memory_Board : public Board<char> {
private:
    char blank_symbol = '.';
public:
    Memory_Board();
    bool update_board(Move<char>* move_ptr) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class Memory_UI : public UI<char> {
public:
    Memory_UI() : UI<char>("Weclome to Memory Tic-Tac-Toe Game", 3) {}
    ~Memory_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_board_matrix(const vector<vector<char>>& matrix) const;
};


