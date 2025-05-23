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
std::set<int> Board::getAvaillableNumbersInChunk(int x, int y)
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
std::set<int> Board::getAvaillableNumbersInLine(int x)
{
    std::set<int> available_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (const auto& i : this->forbidden_columns[x])
    {
        available_numbers.erase(i);
    }
    return available_numbers;
}
std::set<int> Board::getAvaillableNumbersInColumn(int y)
{
    std::set<int> available_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (const auto& i : this->forbidden_lines[y])
    {
        available_numbers.erase(i);
    }
    return available_numbers;
}
std::set<int> Board::getAvaillableNumbersInFrame(int x, int y)
{
    std::set<int> available_numbers = getAvaillableNumbersInChunk(x, y);
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

void Board::generate()
{
    this->clear();
    /*
        #TODO:
        il faut stocker les previous values de toutes les cases modifiées 
            jusqu'à qu'elle soit "dépasser" (que la case d'avant soit modifiée)
        
        --> HashMap (Coordinates, prev_values)
    */
    std::map<std::pair<int, int>, std::vector<int>> tested_values;
    for (int x = 0; x < BOARD_SIZE; x++)
    {
        for (int y = 0; y < BOARD_SIZE; y++)
        {
            tested_values.emplace(std::make_pair(x, y), std::vector<int>());
        }
    }

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            auto available_numbers = this->getAvaillableNumbersInFrame(x, y);
            /* --> Get previous_values from HashMap at key = x,y */
            auto previous_values = tested_values.at(std::make_pair(x, y));
            if (!previous_values.empty()) 
            {
                for (auto &&pval : previous_values)
                {
                    available_numbers.erase(pval);
                }
            }
            if (available_numbers.empty())
            {
                /* --> Clear data in HashMap at key = x,y */
                tested_values.at(std::make_pair(x, y)).clear();

                getPreviousCoordinates(x, y);
                this->forbidden_columns[x].pop_back();
                this->forbidden_lines[y].pop_back();
                
                /* --> Push_back new value in HashMap at key = x,y */
                tested_values.at(std::make_pair(x, y)).push_back(this->frames[x][y].getValue());

                this->frames[x][y].setValue(0);
                x--; // To prevent loop incrementation
            }
            else
            {
                int index = getRandomNumber(available_numbers.size()-1);
                auto it = available_numbers.begin();
                std::advance(it, index);
                
                this->frames[x][y].setValue(*it);
                this->forbidden_columns[x].push_back(*it);
                this->forbidden_lines[y].push_back(*it);
            }
            system("clear");
            std::cout << this->toString() << std::endl;
            sleep(10);
        }
    }
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
}