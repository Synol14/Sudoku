#include <set>
#include <map>
#include <iostream>

#include "Board.hpp"
#include "Utils.h"

/* Constructors */
Board::Board() {}

/* Getters */
Frame Board::getFrame(int x, int y)
{
    return this->frames[y][x];
}
int Board::getValue(int x, int y)
{
    return this->frames[y][x].getValue();
}

/* Setters */

/* Methods */
std::set<int> Board::getavailableNumbersInChunk(int x, int y)
{
    int chunk_x = x / CHUNK_SIZE;
    int chunk_y = y / CHUNK_SIZE;
    std::set<int> available_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            int val = this->frames[x+chunk_x*CHUNK_SIZE][y+chunk_y*CHUNK_SIZE].getValue();
            if (val > 0)
            {
                available_numbers.erase(val);
            }
        }
    }
    return available_numbers;
}
std::set<int> Board::getavailableNumbersInLine(int x)
{
    std::set<int> available_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (const auto& i : this->forbidden_columns[x])
    {
        available_numbers.erase(i);
    }
    return available_numbers;
}
std::set<int> Board::getavailableNumbersInColumn(int y)
{
    std::set<int> available_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (const auto& i : this->forbidden_lines[y])
    {
        available_numbers.erase(i);
    }
    return available_numbers;
}
std::set<int> Board::getavailableNumbersInFrame(int x, int y)
{
    std::set<int> available_numbers = getavailableNumbersInChunk(x, y);
    for (const auto& i : this->forbidden_columns[x])
    {
        available_numbers.erase(i);
    }
    for (const auto& i : this->forbidden_lines[y])
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
    std::string output = "╔═══════════╦═══════════╦═══════════╗\n";
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            if (x % CHUNK_SIZE == 0)
            {
                output += "║";
            }
            else
            {
                output += "│";
            }
            output += " ";
            int val = this->frames[x][y].getValue();
            if (val != 0)
            {
                output += std::to_string(this->frames[x][y].getValue());
            }
            else
            {
                output += " ";
            }
            output += " ";
            if (x == BOARD_SIZE-1)
            {
                output += "║\n";
            }
        }
        if (y == BOARD_SIZE-1)
        {
            output += "╚═══════════╩═══════════╩═══════════╝\n";
        }
        else
        {
            if ((y+1) % CHUNK_SIZE == 0)
            {
                output += "╠═══════════╬═══════════╬═══════════╣\n";
            }
            else
            {
                output += "║───┼───┼───║───┼───┼───║───┼───┼───║\n";
            }
        }
    }
    return output;
}

int Board::generate()
{
    int iteration_count = 0;

    /* Clear board if already generated */
    this->clear();

    /* --> HashMap (Coordinates, prev_values) */
    std::map<std::pair<int, int>, std::vector<int>> tested_values;
    /* tested_values map initialization */
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            tested_values.emplace(std::make_pair(x, y), std::vector<int>());
        }
    }

    /* Board generation */
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            // Get available numbers for this frame at this coordinates
            auto available_numbers = this->getavailableNumbersInFrame(x, y);
            // Get previous_values from HashMap at key = x,y
            auto previous_values = tested_values.at(std::make_pair(x, y));
            // If not empty then remove them from available_numbers
            if (!previous_values.empty()) 
            {
                for (auto &&pval : previous_values)
                {
                    available_numbers.erase(pval);
                }
            }
            /* No solution available */
            if (available_numbers.empty())
            {
                // Clear data in HashMap at key = x,y
                tested_values.at(std::make_pair(x, y)).clear();
                // Decrement coordinates
                getPreviousCoordinates(x, y);
                // Remove number of the previous frame from forbidden lists
                this->forbidden_columns[x].pop_back();
                this->forbidden_lines[y].pop_back();
                // Push_back new value in HashMap at key = x,y
                tested_values.at(std::make_pair(x, y)).push_back(this->frames[x][y].getValue());
                // Reset previous frame value
                this->frames[x][y].setValue(0);
                x--; // To prevent loop incrementation
            }
            /* Number placement */
            else
            {
                /* Random selection of a number from available_numbers */
                int index = getRandomNumber(available_numbers.size()-1);
                auto it = available_numbers.begin();
                std::advance(it, index);
                
                // Set current frame value
                this->frames[x][y].setValue(*it);
                // Add frame value to forbidden lists
                this->forbidden_columns[x].push_back(*it);
                this->forbidden_lines[y].push_back(*it);
            }

            /* Add an iteration to counter */
            iteration_count++;

#ifdef BOARD_DEBUG
            /* To display progress */
            system("clear");
            std::cout << this->toString() << std::endl;
            sleep(10);
#endif
        }
    }

    return iteration_count;
}


void Board::clear()
{
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            this->frames[x][y].setValue(0);
            this->frames[x][y].setUserValue(0);
            this->frames[x][y].display(false);
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        this->forbidden_lines[i].clear();
        this->forbidden_columns[i].clear();
    }
    
}