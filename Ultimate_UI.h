#ifndef _ULTIMATE_UI_H
#define _ULTIMATE_UI_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <limits>

/*
 * Simple UI for Ultimate Tic-Tac-Toe:
 * - Displays the 9x9 underlying board with heavier separators every 3 cells.
 * - Accepts global coordinates in range [0..8].
 */

class Ultimate_UI : public UI<char> {
public:
    Ultimate_UI() : UI<char>("Ultimate Tic-Tac-Toe", 1) {}
    ~Ultimate_UI() override {}

    void display_board_matrix(const std::vector<std::vector<char>>& matrix) const override {
        if (matrix.empty() || matrix[0].empty()) return;
        int rows = static_cast<int>(matrix.size());
        int cols = static_cast<int>(matrix[0].size());

        std::cout << "\n    ";
        for (int c = 0; c < cols; ++c) {
            std::cout << std::setw(2) << c << ((c % 3 == 2 && c != cols - 1) ? " |" : " ");
        }
        std::cout << "\n";

        for (int r = 0; r < rows; ++r) {
            std::cout << std::setw(3) << r << " ";
            for (int c = 0; c < cols; ++c) {
                char ch = matrix[r][c];
                if (ch == static_cast<char>(' ')) ch = '.';
                std::cout << " " << ch << ((c % 3 == 2 && c != cols - 1) ? " |" : " ");
            }
            std::cout << "\n";
            if (r % 3 == 2 && r != rows - 1) {
                std::cout << "    " << std::string(cols * 3 + 4, '-') << "\n";
            }
        }
        std::cout << std::endl;
    }

    Move<char>* get_move(Player<char>* player) override {
        int x = 0, y = 0;
        while (true) {
            std::cout << player->get_name() << " (" << player->get_symbol() << ") enter move (row col) [0-8]: ";
            if (!(std::cin >> x >> y)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter two integers in range 0..8.\n";
                continue;
            }
            if (x < 0 || x > 8 || y < 0 || y > 8) {
                std::cout << "Coordinates out of range. Use values 0..8.\n";
                continue;
            }
            return new Move<char>(x, y, player->get_symbol());
        }
    }
};

#endif