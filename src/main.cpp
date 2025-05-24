#include <iostream>
#include <chrono>

#include "Board.hpp"
#include "Utils.h"

#define SAMPLE_NUMBER 100

int main(int argc, char const *argv[])
{
    newRandomSeed();
    Board b;

    int total_iteration = 0;
    std::chrono::duration<double, std::milli> total_duration(0);

    for (int i = 0; i < SAMPLE_NUMBER; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        int it_count = b.generate();
        auto end = std::chrono::high_resolution_clock::now();
        total_iteration += it_count;
        total_duration += end - start;
    }

    std::cout << "Sample count:     " << SAMPLE_NUMBER << std::endl;
    std::cout << "Total iterations: " << total_iteration << std::endl;
    std::cout << "Total duration:   " << total_duration.count() << "ms" << std::endl;
    std::cout << "Mean iterations:  " << total_iteration/SAMPLE_NUMBER << std::endl;
    std::cout << "Mean duration:    " << total_duration.count()/SAMPLE_NUMBER << "ms" << std::endl;

    return 0;
}
