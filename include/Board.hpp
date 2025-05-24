#pragma once

#include <algorithm>
#include <vector>
#include <set>
#include <iostream>

#include "Frame.hpp"

#define CHUNK_SIZE 3
#define BOARD_SIZE CHUNK_SIZE*CHUNK_SIZE

// #define BOARD_DEBUG

class Board
{
private:
    Frame frames[BOARD_SIZE][BOARD_SIZE];
    std::vector<int> forbidden_lines[BOARD_SIZE];
    std::vector<int> forbidden_columns[BOARD_SIZE];

private:
    std::set<int> getavailableNumbersInChunk(int x, int y);
    std::set<int> getavailableNumbersInLine(int x);
    std::set<int> getavailableNumbersInColumn(int y);
    std::set<int> getavailableNumbersInFrame(int x, int y);
    void getPreviousCoordinates(int &x, int &y);

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
    std::string toString();

    /* Setters */

    /* Methods */
    /**
     * @brief Generate a board
     * 
     * @return int Iterations count
     */
    int generate();
    /**
     * @brief Clear and reset board
     */
    void clear();
};