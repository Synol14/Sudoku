#include <set>
#include <map>
#include <iostream>

#include "Board.hpp"
#include "Utils.h"
#include "ANSI.h"

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
            Frame frame = this->frames[x + chunk_x * CHUNK_SIZE][y + chunk_y * CHUNK_SIZE];
            int val = frame.isFixed() ? frame.getValue() : frame.getUserValue();
            if (val > 0)
            {
                available_numbers.erase(val);
            }
        }
    }
    return available_numbers;
}
std::set<int> Board::getavailableNumbersInFrame(int x, int y)
{
    std::set<int> available_numbers = getavailableNumbersInChunk(x, y);
    for (const auto &i : this->forbidden_columns[x])
    {
        available_numbers.erase(i);
    }
    for (const auto &i : this->forbidden_lines[y])
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
        x = BOARD_SIZE - 1;
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
            auto f = this->frames[x][y];
            if (f.getValue() != 0 && f.isFixed())
            {
                output += ANSI_BOLD + std::to_string(f.getValue()) + ANSI_RESET;
            }
            else if (f.getUserValue() != 0 && !f.isFixed())
            {
                output += ANSI_ORANGE + std::to_string(f.getValue()) + ANSI_RESET;
            }
            else
            {
                output += " ";
            }
            output += " ";
            if (x == BOARD_SIZE - 1)
            {
                output += "║\n";
            }
        }
        if (y == BOARD_SIZE - 1)
        {
            output += "╚═══════════╩═══════════╩═══════════╝\n";
        }
        else
        {
            if ((y + 1) % CHUNK_SIZE == 0)
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

int Board::generateFull()
{
    int iteration_count = 0;

    /* Clear board if already generated */
    this->clear();

    /* --> Map (Coordinates, prev_values) */
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
            // Get previous_values from Map at key = x,y
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
                // Clear data in Map at key = x,y
                tested_values.at(std::make_pair(x, y)).clear();
                // Decrement coordinates
                getPreviousCoordinates(x, y);
                // Remove number of the previous frame from forbidden lists
                this->forbidden_columns[x].pop_back();
                this->forbidden_lines[y].pop_back();
                // Push_back new value in Map at key = x,y
                tested_values.at(std::make_pair(x, y)).push_back(this->frames[x][y].getValue());
                // Reset previous frame value
                this->frames[x][y].setValue(0);
                x--; // To prevent loop incrementation
            }
            /* Number placement */
            else
            {
                /* Random selection of a number from available_numbers */
                int index = getRandomNumber(available_numbers.size() - 1);
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

void Board::generatePlayableBoard(int level)
{
    /* Verifications */
    if (level < 0)
        level = 0;
    if (level > BOARD_SIZE * BOARD_SIZE)
        level = BOARD_SIZE * BOARD_SIZE;
    /* Hide frames */
    std::set<std::pair<int, int>> hiden;
    for (int i = 0; i < level; i++)
    {
        std::pair<int, int> coordinates;
        do
        {
            coordinates.first = getRandomNumber(BOARD_SIZE - 1);
            coordinates.second = getRandomNumber(BOARD_SIZE - 1);
        } while (hiden.find(coordinates) != hiden.end());

        auto &frame = this->frames[coordinates.first][coordinates.second];
        auto &f_col = this->forbidden_columns[coordinates.first];
        auto &f_raw = this->forbidden_lines[coordinates.second];
        f_col.erase(std::find(f_col.begin(), f_col.end(), frame.getValue()));
        f_raw.erase(std::find(f_raw.begin(), f_raw.end(), frame.getValue()));
        frame.fixed(false);
        hiden.emplace(coordinates);
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
            this->frames[x][y].fixed(true);
        }
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        this->forbidden_lines[i].clear();
        this->forbidden_columns[i].clear();
    }
}

int Board::solve()
{
    int iteration_count = 0;
    bool retry = false;

    /* --> Map (Coordinates, prev_values) */
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
            if (this->frames[x][y].isFixed())
            {
                if (retry)
                {
                    // Clear data in Map at key = x,y
                    tested_values.at(std::make_pair(x, y)).clear();
                    // Decrement coordinates
                    getPreviousCoordinates(x, y);
                    if (!this->frames[x][y].isFixed())
                    {
                        // Remove number of the previous frame from forbidden lists
                        this->forbidden_columns[x].pop_back();
                        this->forbidden_lines[y].pop_back();
                        // Push_back new value in Map at key = x,y
                        tested_values.at(std::make_pair(x, y)).push_back(this->frames[x][y].getUserValue());
                        // Reset previous frame value
                        this->frames[x][y].setUserValue(0);
                    }
                    retry = true; 
                    if (x == 0 && y == 0)
                        retry = false; // To prevent blocking at 0,0
                    x--; // To prevent loop incrementation
                }

                /* Add an iteration to counter */
                iteration_count++;
                continue;
            }
            // Get available numbers for this frame at this coordinates
            auto available_numbers = this->getavailableNumbersInFrame(x, y);
            // Get previous_values from Map at key = x,y
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
                // Clear data in Map at key = x,y
                tested_values.at(std::make_pair(x, y)).clear();
                // Decrement coordinates
                getPreviousCoordinates(x, y);
                if (!this->frames[x][y].isFixed())
                {
                    // Remove number of the previous frame from forbidden lists
                    this->forbidden_columns[x].pop_back();
                    this->forbidden_lines[y].pop_back();
                    // Push_back new value in Map at key = x,y
                    tested_values.at(std::make_pair(x, y)).push_back(this->frames[x][y].getUserValue());
                    // Reset previous frame value
                    this->frames[x][y].setUserValue(0);
                }
                retry = true; 
                x--; // To prevent loop incrementation
            }
            /* Number placement */
            else
            {
                /* Random selection of a number from available_numbers */
                int index = getRandomNumber(available_numbers.size() - 1);
                auto it = available_numbers.begin();
                std::advance(it, index);

                // Set current frame value
                this->frames[x][y].setUserValue(*it);
                // Add frame value to forbidden lists
                this->forbidden_columns[x].push_back(*it);
                this->forbidden_lines[y].push_back(*it);
                retry = false;
            }

            /* Add an iteration to counter */
            iteration_count++;

#ifdef BOARD_SOLVER_DEBUG
            /* To display progress */
            system("clear");
            std::cout << this->toString() << std::endl;
            sleep(10);
#endif
        }
    }

    return iteration_count;
}