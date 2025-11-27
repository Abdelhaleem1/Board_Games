#ifndef _INVERSE_XO_UI_H
#define _INVERSE_XO_UI_H

#include "BoardGame_Classes.h"
// #include "..\..\..\Downloads\BoardGameFramework-v2.3\Inverse_TicTacToe.h"
#include <vector>

class Inverse_XO_UI : public UI<char> {
public:
    Inverse_XO_UI();
    ~Inverse_XO_UI() override {};

    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;

private:
    // Return true if placing player's symbol at (x,y) would produce a 3-in-row for that player
    bool would_lose_if_move(Player<char>* player, int x, int y) const;
};

#endif // _INVERSE_XO_UI_H

