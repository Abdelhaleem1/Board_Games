#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
#include <vector>
using namespace std;

class Numerical_XO_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Character used to represent an empty cell on the board.


public:

    Numerical_XO_Board();


    bool update_board(Move<char>* move);


    bool is_win(Player<char>* player);


    bool is_lose(Player<char>*) { return false; };


    bool is_draw(Player<char>* player);


    bool game_is_over(Player<char>* player);
};


class Numerical_XO_UI : public UI<char> {
public:

    vector<char> nums;

    Numerical_XO_UI();


    ~Numerical_XO_UI() {};


    Player<char>* create_player(string& name, char symbol, PlayerType type);


    virtual Move<char>* get_move(Player<char>* player);

    Player<char>** setup_players()override;

};
#endif //NUMERICAL_TIC_TAC_TOE_H