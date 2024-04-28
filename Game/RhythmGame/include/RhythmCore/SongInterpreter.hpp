#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "LaneManager.hpp"
#include "Note/Note.hpp"
#include "../DataTypes.hpp"

/// @brief Interpreting lane lines from different song.txt files.
/// @param mLane LaneManager that holds all the lanes
/// @param line current file line
/// @param lane_num which lane is currently being processed
void process_line(std::shared_ptr<LaneManager> laneManager, std::string line, int lane_num) {
    std::cout << "HERE" << std::endl;
    std::stringstream ss(line);
    std::string outer_token;
    wrap_lane &current_lane = laneManager->getLaneByIndex(lane_num);

    // All of the notes are being put into the very first lane. There is an issue with switching lanes to inpuit into

    while (std::getline(ss, outer_token, ',')) {
        std::stringstream note(outer_token);
        std::string inner_token;
        std::getline(note, inner_token, ':');
        float start = std::stof(inner_token) * GameManager::pixels_per_tick;
        std::getline(note, inner_token, ':');
        float end = std::stof(inner_token) * GameManager::pixels_per_tick;
        current_lane->enqueue(start, end);
        std::shared_ptr<Note> last_note = current_lane->getBack();
        std::cout << last_note->getRStart() << ":" << last_note->getREnd() << std::endl;
    }
}


/// @brief
/// @param song_name
/// @return
std::shared_ptr<LaneManager> songInterpreter(std::string song_name, RectProps &props)
{
    std::ifstream input_stream("C:/Users/5418m/cppFolder/BeatTrials/Game/RhythmGame/NoteMainFrame/ParsedSongs/" + song_name + ".txt");
    if (input_stream.is_open()) {
        // reading the initial 2 lines for lanes and ticks/second
        std::string line = "";
        std::getline(input_stream, line);
        int laneCount = std::stoi(line);
        std::getline(input_stream, line);
        int ticks_per_second = std::stoi(line);
        std::cout << "calculation: " << GameManager::pixels_per_frame << std::endl;

        std::shared_ptr<LaneManager> laneManager;
        // e.what() says what and where went wrong, better for debugging
        try {
            laneManager = std::make_shared<LaneManager>(props, ticks_per_second);
        } catch (std::bad_alloc &e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            return nullptr; // return nullptr if the memory allocation fails
        }

        for (int lane_num = 0; std::getline(input_stream, line); lane_num++) {
            std::cout << "The lane: " << line << std::endl;
            process_line(laneManager, line, lane_num);
        }

        std::cout << "Size: " << laneManager->getManagedLanes().size() << "''" << std::endl;
        // system("pause");
        return laneManager;
    }
    else {
        return nullptr;
    }
}
