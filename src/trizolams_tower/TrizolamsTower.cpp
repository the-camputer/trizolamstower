#include "bestinshow/engine/grammar/EarleyParser.h"
#include "bestinshow/engine/InputProcessor.h"
#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"
// #include "trizolams_tower/managers/GameManager.h"
// #include "trizolams_tower/managers/SceneManager.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/dll.hpp>
#include <iostream>
#include <memory>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <string>

/*
    initialize grammar - TrizolamGrammar
    initialize input proceesor - InputProcessor
    initialize scene management
    initialize state - GameManager
    display initial scene description
    while true:
        get input
        convert input to player command - InputProcessor
        execute command
        update state with results
*/

std::string get_input();

int main()
{
    spdlog::info("cwd: {}", boost::dll::program_location().parent_path());
    Grammar game_grammar = TrizolamGrammar::get_instance();
    InputProcessor input_processor{game_grammar};

    // GameManager game_manager{};
    // SceneManager scene_manager{""}

    // TODO: Replace with initial scene description
    std::cout << "Welcome to Trizolam's Tower!" << std::endl;
    while (true)
    {
        std::string player_input = get_input();

        if (player_input == "quit")
        {
            return 0;
        }

        auto command = input_processor.process(player_input);
        spdlog::info("{}", command);
    }
}

std::string get_input()
{
    std::string player_input;
    std::cout << "> ";
    std::getline(std::cin, player_input);

    return player_input;
}