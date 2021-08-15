#include "bestinshow/engine/grammar/EarleyParser.h"
#include "bestinshow/engine/InputProcessor.h"
#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <memory>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <string>

/*
    initialize grammar - TrizolamGrammar
    initialize input proceesor - InputProcessor
    initialize scene management
    initialize state
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
    Grammar game_grammar = TrizolamGrammar::get_instance();
    InputProcessor input_processor{game_grammar};

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