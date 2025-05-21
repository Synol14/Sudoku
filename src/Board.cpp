#include <set>

#include "Board.hpp"

/* Constructors */
Board::Board() {}

/* Getters */
Frame Board::getFrame(int x, int y)
{
    return this->frames[x][y];
}
int Board::getValue(int x, int y)
{
    return this->frames[x][y].getValue();
}

/* Setters */

/* Methods */
void Board::generate()
{
    bool finished = false;
    int x = 0, y = 0;
    int chunk_id = 0;
    
    std::set<int> available_numbers_in_chunk = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    while (!finished)
    {
        
    }
}

/* Static Methods */
Board Board::createEmptyBoard()
{

}