#include <set>

#include "Board.hpp"
#include "Utils.h"

/* Constructors */
Board::Board() {}

/* Getters */
Frame* Board::getFrame(int x, int y)
{
    return this->frames[y][x];
}
int Board::getValue(int x, int y)
{
    return this->frames[y][x]->getValue();
}

/* Setters */

/* Methods */
bool Board::canPlaceNumberInChunk(int x, int y, int a)
{
    auto s = getAvaillableNumbersInChunk(x, y);
    return std::find(s.begin(), s.end(), a) != s.end();
}
bool Board::canPlaceNumberInLine(int x, int a)
{
    auto s = getAvaillableNumbersInLine(x);
    return std::find(s.begin(), s.end(), a) != s.end();
}
bool Board::canPlaceNumberInColumn(int y, int a)
{
    auto s = getAvaillableNumbersInColumn(y);
    return std::find(s.begin(), s.end(), a) != s.end();
}
std::set<int> Board::getAvaillableNumbersInChunk(int x, int y)
{
    int chunk_x = x / CHUNK_SIZE;
    int chunk_y = y / CHUNK_SIZE;
    std::set<int> available_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            int val = this->frames[x+chunk_x][y+chunk_y]->getValue();
            if (val > 0)
            {
                available_numbers.erase(val);
            }
        }
    }
    return available_numbers;
}
std::set<int> Board::getAvaillableNumbersInLine(int x)
{
    std::set<int> available_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (const auto& i : this->forbidden_lines[x])
    {
        available_numbers.erase(i);
    }
    return available_numbers;
}
std::set<int> Board::getAvaillableNumbersInColumn(int y)
{
    std::set<int> available_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (const auto& i : this->forbidden_columns[y])
    {
        available_numbers.erase(i);
    }
    return available_numbers;
}
std::set<int> Board::getAvaillableNumbersInFrame(int x, int y)
{
    std::set<int> available_numbers = getAvaillableNumbersInChunk(x, y);
    for (const auto& i : this->forbidden_lines[x])
    {
        available_numbers.erase(i);
    }
    for (const auto& i : this->forbidden_columns[y])
    {
        available_numbers.erase(i);
    }
    return available_numbers;
}
void Board::getPreviousCoordinates(int &x, int &y)
{
    x--;
    if (x < 0)
    {
        x = BOARD_SIZE-1;
        y--;
        if (y < 0) 
        {
            x = 0;
            y = 0;
        }
    }
}
std::string Board::toString()
{
    
}

void Board::generate()
{
    this->clear();
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            auto available_numbers = this->getAvaillableNumbersInFrame(x, y);
            if (available_numbers.empty())
            {
                getPreviousCoordinates(x, y);
                this->forbidden_lines[x].pop_back();
                this->forbidden_columns[y].pop_back();
            }
            else
            {
                bool placed = false;
                while (!placed && !available_numbers.empty())
                {
                    int index = getRandomNumber(available_numbers.size()-1);
                    auto it = available_numbers.begin();
                    std::advance(it, index);
                    
                    this->frames[x][y]->setValue(*it);
                    this->forbidden_lines[x].push_back(*it);
                    this->forbidden_columns[y].push_back(*it);
                }
            }
        }
    }
}


void Board::clear()
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            this->frames[x][y]->setValue(0);
            this->frames[x][y]->setUserValue(0);
            this->frames[x][y]->display(false);
        }
    }
}