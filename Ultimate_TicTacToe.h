#ifndef _ULTIMATE_TICTACTOE_H
#define _ULTIMATE_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>

/*
 * Ultimate Tic-Tac-Toe implemented as a 9x9 underlying board (3x3 of 3x3 sub-boards).
 * - Underlying Board (Board<T>) size = 9 x 9 (rows, columns)
 * - A separate 3x3 `winners` grid tracks which player (if any) has claimed each small board.
 *
 * Move coordinates are global: row and column are in range [0..8].
 */

template <typename T>
class UltimateTicTacToe : public Board<T> {
public:
    UltimateTicTacToe(T empty_cell = static_cast<T>(' '))
        : Board<T>(9, 9), empty_marker(empty_cell) {

        for (int r = 0; r < this->rows; ++r)
            for (int c = 0; c < this->columns; ++c)
                this->board[r][c] = empty_marker;

        winners.assign(3, std::vector<T>(3, empty_marker));
    }

    virtual ~UltimateTicTacToe() {}


    virtual bool update_board(Move<T>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        T sym = move->get_symbol();

        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) return false;
        if (this->board[x][y] != empty_marker) return false;

        int br = x / 3;
        int bc = y / 3;


        if (winners[br][bc] != empty_marker) return false;


        this->board[x][y] = sym;
        ++this->n_moves;

        if (check_and_set_small_winner(br, bc)) {

        } else {

            if (small_board_full(br, bc)) {
                winners[br][bc] = draw_marker();
            }
        }

        return true;
    }


    virtual bool is_win(Player<T>* p) override {
        T s = p->get_symbol();
        return three_in_row_winners(s);
    }


    virtual bool is_lose(Player<T>* p) override {
        T opp = get_opponent_symbol(p);
        return three_in_row_winners(opp);
    }


    virtual bool is_draw(Player<T>*) override {

        if (three_in_row_winners(static_cast<T>('X'))) return false;
        if (three_in_row_winners(static_cast<T>('O'))) return false;


        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                if (winners[r][c] == empty_marker) return false;

        return true;
    }

    virtual bool game_is_over(Player<T>* p) override {
        return is_win(p) || is_lose(p) || is_draw(p);
    }

private:
    std::vector<std::vector<T>> winners;
    T empty_marker;
    T draw_marker() const { return static_cast<T>('D'); }

    bool check_and_set_small_winner(int br, int bc) {
        int base_r = br * 3;
        int base_c = bc * 3;

        for (int r = 0; r < 3; ++r) {
            T a = this->board[base_r + r][base_c + 0];
            if (a != empty_marker && a == this->board[base_r + r][base_c + 1] && a == this->board[base_r + r][base_c + 2]) {
                winners[br][bc] = a;
                return true;
            }
        }

        for (int c = 0; c < 3; ++c) {
            T a = this->board[base_r + 0][base_c + c];
            if (a != empty_marker && a == this->board[base_r + 1][base_c + c] && a == this->board[base_r + 2][base_c + c]) {
                winners[br][bc] = a;
                return true;
            }
        }

        T d1 = this->board[base_r + 0][base_c + 0];
        if (d1 != empty_marker && d1 == this->board[base_r + 1][base_c + 1] && d1 == this->board[base_r + 2][base_c + 2]) {
            winners[br][bc] = d1;
            return true;
        }
        T d2 = this->board[base_r + 0][base_c + 2];
        if (d2 != empty_marker && d2 == this->board[base_r + 1][base_c + 1] && d2 == this->board[base_r + 2][base_c + 0]) {
            winners[br][bc] = d2;
            return true;
        }

        return false;
    }

    bool small_board_full(int br, int bc) const {
        int base_r = br * 3;
        int base_c = bc * 3;
        for (int r = 0; r < 3; ++r)
            for (int c = 0; c < 3; ++c)
                if (this->board[base_r + r][base_c + c] == empty_marker)
                    return false;
        return true;
    }

    bool three_in_row_winners(T s) const {
        if (s == draw_marker() || s == empty_marker) return false;
        for (int r = 0; r < 3; ++r)

            if (winners[r][0] == s && winners[r][1] == s && winners[r][2] == s)
                return true;

       for (int c = 0; c < 3; ++c)
            if (winners[0][c] == s && winners[1][c] == s && winners[2][c] == s)
                return true;

        if (winners[0][0] == s && winners[1][1] == s && winners[2][2] == s) return true;
        if (winners[0][2] == s && winners[1][1] == s && winners[2][0] == s) return true;

        return false;
    }

    T get_opponent_symbol(Player<T>* p) const {
        T s = p->get_symbol();
        if (s == static_cast<T>('X')) return static_cast<T>('O');
        return static_cast<T>('X');
    }
};

#endif