#ifndef SUS_H
#define SUS_H

#include "BoardGame_Classes.h"

using namespace std;

class SUS_Board : public Board<char> {
private:
    char blank_symbol = '.';
    int last_row_play = 0;
    int last_col_play = 0;
    int count1 = 0;
    int count2 = 0;
public:
    SUS_Board();
    bool update_board(Move<char>* move_ptr) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    void condition(int x, int y, char symbol);
};

class SUS_UI : public UI<char> {
public:
    SUS_UI() : UI<char>("Weclome to SUS Game", 3) {}
    ~SUS_UI() {};
    Player<char>** setup_players() override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
};

#endif
