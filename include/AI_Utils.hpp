#pragma once

#include <vector>

#include "Board.hpp"

#define BOARD_OUTPUT_DIR        "labels/"
#define BOARD_OUT_FULL_DIR      "full/"
#define BOARD_OUT_PLAYABLE_DIR  "playable/"

std::vector<int> getFullBoardToList(const Board &board);
std::vector<int> getPlayableBoardToList(const Board &board);

/**
 * @brief Save a board into two file, one for full board and another for playable board with different levels
 * 
 * @param index (IN) Board index
 * @param b (IN) Board oject
 */
void saveBoardInfiles(int index, Board &b);