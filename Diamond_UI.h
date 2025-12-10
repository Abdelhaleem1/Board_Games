#ifndef _DIAMOND_UI_H
#define _DIAMOND_UI_H

#include "BoardGame_Classes.h"
#include "Diamond_TicTacToe.h"
#include <limits>
#include <iostream>
#include <iomanip>
#include <cmath>

class Diamond_UI : public UI<char> {
public:
    Diamond_UI() : UI<char>("Diamond Tic-Tac-Toe", 3) {}
    ~Diamond_UI() override {}

    void display_board_matrix(const std::vector<std::vector<char>>& matrix) const override {
        if (matrix.empty() || matrix[0].empty()) return;

        int rows = static_cast<int>(matrix.size());
        int cols = static_cast<int>(matrix[0].size());
        int center_r = rows / 2;
        int center_c = cols / 2;

        std::cout << "\n    ";
        for (int c = 0; c < cols; ++c)
            std::cout << std::setw(cell_width + 1) << c;
        std::cout << "\n";

        for (int r = 0; r < rows; ++r) {
            int rowIndent = std::abs(center_r - r);
            std::cout << std::setw(3) << r << " ";
            for (int s = 0; s < rowIndent; ++s)
                std::cout << std::setw(cell_width + 1) << ' ';


            for (int c = 0; c < cols; ++c) {
                bool valid = (std::abs(center_r - r) + std::abs(center_c - c)) <= center_r;
                if (valid)
                    std::cout << std::setw(cell_width) << matrix[r][c] << ' ';
                else
                    std::cout << std::setw(cell_width) << ' ' << ' ';
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    Move<char>* get_move(Player<char>* player) override {
        int x = 0, y = 0;
        while (true) {
            std::cout << player->get_name() << " (" << player->get_symbol() << ") enter move (row col): ";
            if (!(std::cin >> x >> y)) {

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter two integers.\n";
                continue;
            }
            return new Move<char>(x, y, player->get_symbol());
        }
    }
};

#endif