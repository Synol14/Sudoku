#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "Chunk.h"

class Board
{
private:
    Chunk chunks[3][3];

public:
    /* Contructors */
    Board();

    /* Getters */
    /**
     * @brief Get the Frame by coordinates
     *
     * @param x (IN) The x coordinate of the frame
     * @param y (IN) The y coordinate of the frame
     * @return Frame
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