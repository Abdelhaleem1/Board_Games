#ifndef _DIAMOND_TICTACTOE_H
#define _DIAMOND_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
#include <cmath>

/**
 * @brief Diamond Tic-Tac-Toe played on a 5x5 grid where valid cells form a diamond:
 *        abs(r - 2) + abs(c - 2) <= 2
 *
 * Winning condition:
 * - A player wins if they simultaneously have at least one full line of length 3
 *   and at least one full line of length 4, and the two lines are in different
 *   directions (horizontal, vertical, main-diagonal, anti-diagonal). The lines
 *   may share a single common cell.
 */
template <typename T>
class DiamondTicTacToe : public Board<T> {
public:
    DiamondTicTacToe(T empty_cell = static_cast<T>(' '))
        Board<T>(5, 5), empty_marker(empty_cell) {
            valid_cell_count = 0;
            for (int r = 0; r < this->rows; ++r) {
                for (int c = 0; c < this->columns; ++c) {
                    this->board[r][c] = empty_marker;
                    if (is_valid_cell(r, c)) {
                    ++valid_cell_count;
                    }
                }
        }
        precompute_lines();
    }

    virtual ~DiamondTicTacToe() {}

    virtual bool update_board(Move<T>* move) override {
        int x = move->get_x();
        int y = move->get_y();
        T sym = move->get_symbol();

        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) return false;
        if (!is_valid_cell(x, y)) return false;
        if (this->board[x][y] != empty_marker) return false;

        this->board[x][y] = sym;
        ++this->n_moves;
        return true;
    }

    virtual bool is_win(Player<T>* p) override {
        T sym = p->get_symbol();
        std::vector<int> three_dirs;
        std::vector<int> four_dirs;

        for (size_t i = 0; i < lines3.size(); ++i) {
            if (line_all_symbol(lines3[i].coords, sym)) three_dirs.push_back(lines3[i].dir);
        }
        for (size_t i = 0; i < lines4.size(); ++i) {
            if (line_all_symbol(lines4[i].coords, sym)) four_dirs.push_back(lines4[i].dir);
        }

        for (int d3 : three_dirs)
            for (int d4 : four_dirs)
                if (d3 != d4) return true;

        return false;
    }

    virtual bool is_lose(Player<T>*) override {
        return false;
    }

    virtual bool is_draw(Player<T>*) override {
        if (this->n_moves < valid_cell_count) return false;
        if (symbol_has_win(static_cast<T>('X'))) return false;
        if (symbol_has_win(static_cast<T>('O'))) return false;
        return true;
    }

    virtual bool game_is_over(Player<T>* p) override {
        return is_win(p) || is_lose(p) || is_draw(p);
    }

private:
    // Direction identifiers
    // 0 = horizontal, 1 = vertical, 2 = main diagonal (TL-BR), 3 = anti diagonal (TR-BL)
    struct LineInfo { std::vector<std::pair<int,int>> coords; int dir; };

    T empty_marker;
    int valid_cell_count;
    std::vector<LineInfo> lines3;
    std::vector<LineInfo> lines4;

    bool is_valid_cell(int r, int c) const {
        // Diamond condition centered at (2,2) with radius 2
        return (std::abs(r - 2) + std::abs(c - 2)) <= 2;
    }

    void precompute_lines() {
        // directions as (dr, dc) with dir id
        const std::vector<std::pair<int,int>> dirs = {
            {0, 1},  // horizontal -> dir 0
            {1, 0},  // vertical   -> dir 1
            {1, 1},  // main diag  -> dir 2
            {1, -1}  // anti diag  -> dir 3
        };

        for (int r = 0; r < this->rows; ++r) {
            for (int c = 0; c < this->columns; ++c) {
                if (!is_valid_cell(r, c)) continue;
                for (int d = 0; d < (int)dirs.size(); ++d) {
                    std::vector<std::pair<int,int>> coords3;
                    bool ok3 = true;
                    for (int k = 0; k < 3; ++k) {
                        int rr = r + k * dirs[d].first;
                        int cc = c + k * dirs[d].second;
                        if (rr < 0 || rr >= this->rows || cc < 0 || cc >= this->columns || !is_valid_cell(rr, cc)) {
                            ok3 = false;
                            break;
                        }
                        coords3.emplace_back(rr, cc);
                    }
                    if (ok3) lines3.push_back({coords3, d});

                    std::vector<std::pair<int,int>> coords4;
                    bool ok4 = true;
                    for (int k = 0; k < 4; ++k) {
                        int rr = r + k * dirs[d].first;
                        int cc = c + k * dirs[d].second;
                        if (rr < 0 || rr >= this->rows || cc < 0 || cc >= this->columns || !is_valid_cell(rr, cc)) {
                            ok4 = false;
                            break;
                        }
                        coords4.emplace_back(rr, cc);
                    }
                    if (ok4) lines4.push_back({coords4, d});
                }
            }
        }
        deduplicate_lines(lines3);
        deduplicate_lines(lines4);
    }

    static void deduplicate_lines(std::vector<LineInfo>& lines) {
        std::vector<LineInfo> out;
        for (auto& li : lines) {
            bool found = false;
            for (auto& ex : out) {
                if (ex.coords == li.coords && ex.dir == li.dir) { found = true; break; }
            }
            if (!found) out.push_back(li);
        }
        lines.swap(out);
    }

    bool line_all_symbol(const std::vector<std::pair<int,int>>& coords, T sym) const {
        for (auto &p : coords) {
            if (this->board[p.first][p.second] != sym) return false;
        }
        return true;
    }

    bool symbol_has_win(T sym) const {

        std::vector<int> three_dirs;
        std::vector<int> four_dirs;

        for (const auto &li : lines3) {
            if (line_all_symbol(li.coords, sym)) three_dirs.push_back(li.dir);
        }
        for (const auto &li : lines4) {
            if (line_all_symbol(li.coords, sym)) four_dirs.push_back(li.dir);
        }
        for (int d3 : three_dirs)
            for (int d4 : four_dirs)
                if (d3 != d4) return true;
        return false;
    }
};

#endif