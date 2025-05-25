#include <chrono>
#include <fstream>
#include <filesystem>

#include "AI_Utils.hpp"

std::vector<int> getFullBoardToList(const Board &board)
{
    std::vector<int> board_list;
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            board_list.push_back(board.getValue(x, y));
        }
    }
    return board_list;
}

std::vector<int> getPlayableBoardToList(const Board &board)
{
    std::vector<int> board_list;
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            int value = board.getFrame(x, y).isFixed() ? board.getValue(x, y) : 0;
            board_list.push_back(value);
        }
    }
    return board_list;
}

void saveBoardInfiles(int index, int difficulty, const Board &b, bool date_dir)
{
    char date_str[100] = "";
    if (date_dir)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm *now_tm = std::localtime(&now_c);
        std::strftime(date_str, sizeof(date_str), "%Y-%m-%d_%H.%M.%S/", now_tm);
    }

    std::string full_filename = BOARD_OUTPUT_DIR + std::string(date_str) + BOARD_OUT_FULL_DIR + std::to_string(difficulty) + "/board_" + std::to_string(index) + ".txt";
    std::string playable_filename = BOARD_OUTPUT_DIR + std::string(date_str) + BOARD_OUT_PLAYABLE_DIR + std::to_string(difficulty) + "/board_" + std::to_string(index) + ".txt";

    std::filesystem::path full_file_path(full_filename);
    std::filesystem::path playable_file_path(playable_filename);

    if (!std::filesystem::exists(full_file_path.parent_path()))
    {
        std::filesystem::create_directories(full_file_path.parent_path());
    }
    if (!std::filesystem::exists(playable_file_path.parent_path()))
    {
        std::filesystem::create_directories(playable_file_path.parent_path());
    }

    std::ofstream full_file(full_filename, std::fstream::trunc);
    std::ofstream playable_file(playable_filename, std::fstream::trunc);

    if (full_file.is_open())
    {
        auto values = getFullBoardToList(b);
        for (size_t j = 0; j < values.size(); j++)
        {
            full_file << values[j];
            if (j < values.size() - 1)
                full_file << ";";
        }
        full_file << std::endl;
        full_file.close();
    }
    if (playable_file.is_open())
    {
        auto values = getPlayableBoardToList(b);
        for (size_t j = 0; j < values.size(); j++)
        {
            playable_file << values[j];
            if (j < values.size() - 1)
                playable_file << ";";
        }
        playable_file << std::endl;
        playable_file.close();
    }
}

void saveBoardInfiles(int index, Board &b)
{
    std::string full_filename = BOARD_OUTPUT_DIR BOARD_OUT_FULL_DIR "board_" + std::to_string(index) + ".txt";
    std::filesystem::path full_file_path(full_filename);

    if (!std::filesystem::exists(full_file_path.parent_path()))
    {
        std::filesystem::create_directories(full_file_path.parent_path());
    }
    std::ofstream full_file(full_filename, std::fstream::trunc);

    if (full_file.is_open())
    {
        full_file.clear();
        auto values = getFullBoardToList(b);
        for (size_t j = 0; j < values.size(); j++)
        {
            full_file << values[j];
            if (j < values.size() - 1)
                full_file << ";";
        }
        full_file << std::endl;
        full_file.close();
    }

    for (int difficulty = 30; difficulty <= 60; difficulty += 5)
    {
        b.generatePlayableBoard(difficulty);

        std::string playable_filename = BOARD_OUTPUT_DIR BOARD_OUT_PLAYABLE_DIR + std::to_string(difficulty) + "/board_" + std::to_string(index) + ".txt";
        std::filesystem::path playable_file_path(playable_filename);

        if (!std::filesystem::exists(playable_file_path.parent_path()))
        {
            std::filesystem::create_directories(playable_file_path.parent_path());
        }
        std::ofstream playable_file(playable_filename, std::fstream::trunc);

        if (playable_file.is_open())
        {
            playable_file.clear();
            auto values = getPlayableBoardToList(b);
            for (size_t j = 0; j < values.size(); j++)
            {
                playable_file << values[j];
                if (j < values.size() - 1)
                    playable_file << ";";
            }
            playable_file << std::endl;
            playable_file.close();
        }
    }
}