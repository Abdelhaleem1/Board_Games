#ifndef _INVERSE_TICTACTOE_H
#define _INVERSE_TICTACTOE_H

#include "BoardGame_Classes.h"

/**
 * @brief Inverse (Misère) Tic-Tac-Toe.
 *
 * Rules implemented:
 * - Standard 3x3 board.
 * - A player loses if they complete a line (row, column, diagonal) of three of their own marks.
 * - If the board fills with no player having three-in-a-row, the game is a draw.
 *
 * Mapping to framework:
 * - `is_lose(Player*)` returns true when that player's symbol has a three-in-a-row (they lose).
 * - `is_win(Player*)` returns true when the opponent has a three-in-a-row (opponent wins).
 */
template <typename T>
class InverseTicTacToe : public Board<T> {
public:
    InverseTicTacToe(T empty_cell = static_cast<T>(' '))
        : Board<T>(3, 3), empty_marker(empty_cell) {
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                this->board[r][c] = empty_marker;
    }

    virtual ~InverseTicTacToe() {}


    virtual bool update_board(Move<T>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        T sym = move->get_symbol();

        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) return false;
        if (this->board[x][y] != empty_marker) return false;

        this->board[x][y] = sym;
        ++this->n_moves;
        return true;
    }


    virtual bool is_win(Player<T>* p) override {
        T opp = get_opponent_symbol(p);
        return symbol_has_three_in_row(opp);
    }


    virtual bool is_lose(Player<T>* p) override {
        T s = p->get_symbol();
        return symbol_has_three_in_row(s);
    }


    virtual bool is_draw(Player<T>*) override {
        if (symbol_has_three_in_row(static_cast<T>('X'))) return false;
        if (symbol_has_three_in_row(static_cast<T>('O'))) return false;
        return this->n_moves >= this->rows * this->columns;
    }

    virtual bool game_is_over(Player<T>* p) override {
        return is_win(p) || is_lose(p) || is_draw(p);
    }

private:
    T empty_marker;

    bool symbol_has_three_in_row(T sym) const {
        if (sym == empty_marker) return false;

        for (int r = 0; r < 3; ++r)
            if (this->board[r][0] == sym && this->board[r][1] == sym && this->board[r][2] == sym)
                return true;

        for (int c = 0; c < 3; ++c)
            if (this->board[0][c] == sym && this->board[1][c] == sym && this->board[2][c] == sym)
                return true;

        if (this->board[0][0] == sym && this->board[1][1] == sym && this->board[2][2] == sym) return true;
        if (this->board[0][2] == sym && this->board[1][1] == sym && this->board[2][0] == sym) return true;

        return false;
    }


    T get_opponent_symbol(Player<T>* p) const {
        T s = p->get_symbol();

        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c) {
                T cand = this->board[r][c];
                if (cand != s && cand != empty_marker) return cand;
            }

        if (s == static_cast<T>('X')) return static_cast<T>('O');
        return static_cast<T>('X');
    }
};

#endif
