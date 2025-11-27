#ifndef TIC_TAC_TOE_4X4_H
#define TIC_TAC_TOE_4X4_H

#include "BoardGame_Classes.h"


using namespace std;
class XO_4x4_Board : public Board<char> {
private:
    char blank_symbol = '.';
    char mark = 1;
    int xold = 4, yold = 4;
public:
    XO_4x4_Board();

    bool update_board(Move<char>* move);


    bool is_win(Player<char>* player);


    bool is_lose(Player<char>*) { return false; };


    bool is_draw(Player<char>* player);


    bool game_is_over(Player<char>* player);
};

class XO_4x4_UI : public UI<char> {
public:

    XO_4x4_UI();


    ~XO_4x4_UI() {};


    Player<char>* create_player(string& name, char symbol, PlayerType type);


    virtual Move<char>* get_move(Player<char>* player);
};

#endif
