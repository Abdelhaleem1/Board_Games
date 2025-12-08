#pragma once

#include "BoardGame_Classes.h"

class TicTacToe_5x5_board : public Board<char>{
private:
    char blank_symbol = '.';
    int cntX = 0;
    int cntO = 0;
    vector<string> names;
public:
    TicTacToe_5x5_board();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>*) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    void consecutive_cells(char symbol);
};

class TicTacToe_5x5_UI : public UI<char> {
public:
    TicTacToe_5x5_UI();
    ~TicTacToe_5x5_UI() override = default;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};