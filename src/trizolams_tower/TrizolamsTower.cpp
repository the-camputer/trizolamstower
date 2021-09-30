#include "bestinshow/engine/grammar/EarleyParser.h"
#include "bestinshow/engine/InputProcessor.h"
#include "player_input/TrizolamGrammar.h"
#include "managers/GameManager.h"
#include "managers/SceneManager.h"
#include "commands/TravelCommand.h"
#include "commands/CommandProcessor.h"
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
    initialize scene management - SceneManager
    initialize state - GameManager
    display initial scene description
    while true:
        get input
        convert input to player command - InputProcessor
        execute command - CommandProcessor
*/

const std::string scenes_file = "resources/Scenes.yml";
const std::string program_root = boost::dll::program_location().parent_path().parent_path().c_str();
const std::string scenes_file_path = program_root + "/" + scenes_file;

std::string get_input();

int main()
{
    const std::string program_root = boost::dll::program_location().parent_path().parent_path().c_str();
    SceneManager scene_manager{scenes_file_path};
    GameManager game_manager{};

    std::string starting_pos = scene_manager.construct_scenes();
    game_manager.set_player_position(starting_pos);

    std::shared_ptr<SceneManager> scene_manager_ptr = std::make_shared<SceneManager>(scene_manager);
    std::shared_ptr<GameManager> game_manager_ptr = std::make_shared<GameManager>(game_manager);

    CommandProcessor command_processor{game_manager_ptr, scene_manager_ptr};
    std::shared_ptr<CommandProcessor> command_processor_ptr = std::make_shared<CommandProcessor>(command_processor);

    TrizolamGrammar trizolam_grammar{command_processor_ptr};

    InputProcessor input_processor{trizolam_grammar.get_grammar()};

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

        // TODO: Want to replace this if block with a CommandProcessor
        if (command.type == "travel-command")
        {
            command_processor.process_command(command);
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