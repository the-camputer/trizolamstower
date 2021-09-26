#include "bestinshow/engine/grammar/EarleyParser.h"
#include "bestinshow/engine/InputProcessor.h"
#include "trizolams_tower/player_input/TrizolamGrammar.h"
#include "./managers/GameManager.h"
#include "trizolams_tower/managers/SceneManager.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
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

const std::string scenes_file = "resources/Scenes.yml";
const std::string program_root = boost::dll::program_location().parent_path().parent_path().c_str();
const std::string scenes_file_path = program_root + "/" + scenes_file;

std::string get_input();

int main()
{
    const std::string program_root = boost::dll::program_location().parent_path().parent_path().c_str();
    Grammar game_grammar = TrizolamGrammar::get_instance();
    InputProcessor input_processor{game_grammar};

    GameManager game_manager{};
    SceneManager scene_manager{scenes_file_path};

    std::string starting_pos = scene_manager.construct_scenes();

    game_manager.set_player_position(starting_pos);

    std::cout
        << "Welcome to Trizolam's Tower!\n"
        << std::endl;
    std::cout
        << scene_manager.get_scene_description(game_manager.get_player_position())
        << std::endl;

    while (true)
    {
        std::string player_input = get_input();

        if (player_input == "quit")
        {
            return 0;
        }

        auto command = input_processor.process(player_input);

        if (command.type == "travel-command")
        {
            bool scene_changed = false;
            MOVEMENT_DIRECTION travel_direction = (MOVEMENT_DIRECTION)std::stoi(command.payload["direction"]);
            auto new_scene = scene_manager.get_next_scene(game_manager.get_player_position(), travel_direction);

            if (!new_scene.blocked && new_scene.next_scene_name != "")
            {
                scene_changed = true;
                game_manager.set_player_position(new_scene.next_scene_name);
            }
            else if (new_scene.blocked)
            {
                std::cout
                    << new_scene.blocked_reason
                    << std::endl;
            }
            else
            {
                std::cout
                    << "We stick to the paths here"
                    << std::endl;
            }

            if (scene_changed)
            {
                std::cout
                    << scene_manager.get_scene_description(game_manager.get_player_position())
                    << std::endl;
            }
        }
        else if (command.type == "insight-command")
        {
            std::cout
                << scene_manager.get_scene_description(game_manager.get_player_position())
                << std::endl;
        }
        else
        {
            spdlog::info("{}", command);
        }
    }
}

std::string get_input()
{
    std::string player_input;
    std::cout << "> ";
    std::getline(std::cin, player_input);
    boost::algorithm::trim(player_input);

    return player_input;
}