#pragma once

#include "BoardGame_Classes.h"

using namespace std;

class CONNECT_Board : public Board<char> {
private:
    char blank_symbol = '.';

public:
    CONNECT_Board();
    bool update_board(Move<char>* move_ptr) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

class CONNECT_UI : public UI<char> {
public:
    CONNECT_UI() : UI<char>("Weclome to Connect 4 Game", 3) {}
    ~CONNECT_UI() {};
    Player<char>** setup_players() override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

