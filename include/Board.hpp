#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "Frame.hpp"

#define BOARD_SIZE 9
class Board
{
private:
    Frame frames[BOARD_SIZE][BOARD_SIZE];
    std::vector<Frame *> forbidden_lines[BOARD_SIZE];
    std::vector<Frame *> forbidden_columns[BOARD_SIZE];

public:
    /* Contructors */
    Board();

    /* Getters */
    /**
     * @brief Get the Frame by coordinates
     *
     * @param x (IN) The x coordinate of the frame
     * @param y (IN) The y coordinate of the frame
     * @return Frame *
     */
    Frame getFrame(int x, int y);
    /**
     * @brief Get the value by coordinates
     *
     * @param x (IN) The x coordinate of the frame
     * @param y (IN) The y coordinate of the frame
     * @return int
     */
    int getValue(int x, int y);

    /* Setters */

    /* Methods */
    /**
     * @brief Generate the board
     */
    void generate();
    
    /* Static Methods */
    static Board createEmptyBoard();
};