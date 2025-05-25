#include <iostream>
#include <chrono>

#include "Board.hpp"
#include "Utils.h"

#define SAMPLE_NUMBER       1000000
#define DIFICULTY_LEVEL     30

int main()
{
    newRandomSeed();
    Board b;

    int total_iteration = 0;
    int total_solver_iteration = 0;
    std::chrono::duration<double, std::milli> total_duration(0);
    std::chrono::duration<double, std::milli> total_solver_duration(0);

    for (int i = 0; i < SAMPLE_NUMBER; i++)
    {
        std::cout << "Sample " << i << ": " << std::flush;

        auto start = std::chrono::high_resolution_clock::now();
        int it_count = b.generateFull();
        auto end = std::chrono::high_resolution_clock::now();
        total_iteration += it_count;
        total_duration += end - start;

        b.generatePlayableBoard(DIFICULTY_LEVEL);

        start = std::chrono::high_resolution_clock::now();
        it_count = b.solve();
        end = std::chrono::high_resolution_clock::now();
        total_solver_iteration += it_count;
        total_solver_duration += end - start;

        std::cout << "done."<< std::endl;
    }

    system("clear");
    std::cout << "Sample count:     " << SAMPLE_NUMBER << std::endl;
    std::cout << "Dificulty level:  " << DIFICULTY_LEVEL << std::endl;
    std::cout << "============= Generator =============" << std::endl;
    std::cout << "Total iterations: " << total_iteration << std::endl;
    std::cout << "Total duration:   " << total_duration.count() << "ms" << std::endl;
    std::cout << "Mean iterations:  " << total_iteration/SAMPLE_NUMBER << std::endl;
    std::cout << "Mean duration:    " << total_duration.count()/SAMPLE_NUMBER << "ms" << std::endl;
    std::cout << "=============== Solver ==============" << std::endl;
    std::cout << "Total iterations: " << total_solver_iteration << std::endl;
    std::cout << "Total duration:   " << total_solver_duration.count() << "ms" << std::endl;
    std::cout << "Mean iterations:  " << total_solver_iteration/SAMPLE_NUMBER << std::endl;
    std::cout << "Mean duration:    " << total_solver_duration.count()/SAMPLE_NUMBER << "ms" << std::endl;

    return 0;
}
