#pragma once
#include "BoardGame_Classes.h"

class obs_TicTacToe_board : public Board<char>{
private:
    char blank_symbol = '.';
    char obstacle_symbol = '#';
    vector<pair<int,int>> coordinates;
    int last_row_play;
    int last_col_play;
public:
    obs_TicTacToe_board();
    bool update_board(Move<char>* move);
    bool is_win(Player<char>* player);
    bool is_lose(Player<char>*) { return false; };
    bool is_draw(Player<char>* player);
    bool game_is_over(Player<char>* player);
    void random_obs();
    int check_win(int x, int y, int dr, int dc, char sym);
    bool isFull();
};

class obs_TicTacToe_UI : public UI<char> {
public:
    obs_TicTacToe_UI();
    ~obs_TicTacToe_UI() {};
    Player<char>* create_player(string& name, char symbol, PlayerType type);
    virtual Move<char>* get_move(Player<char>* player);
};