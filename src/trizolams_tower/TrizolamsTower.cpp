#include "bestinshow/engine/grammar/EarleyParser.h"
#include "player_input/InputProcessor.h"
#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <memory>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <string>

int main()
{
    std::string player_input;
    InputProcessor input_processor{};
    // spdlog::set_level(spdlog::level::debug);
    spdlog::info("TRIZOLAM GRAMMAR {}", input_processor.get_grammar());
    while (true)
    {
        std::cout << "What is your command? " << std::endl;
        std::getline(std::cin, player_input);

        if (player_input == "quit")
        {
            return 0;
        }

        std::cout << "Processing the following input: " << player_input << std::endl;

        auto command = input_processor.process(player_input);
        spdlog::info("WOW MUCH THING {}", command);
        // std::vector<std::string> processable_input;
        // boost::split(processable_input, player_input, boost::is_any_of(" "), boost::token_compress_on);

        // std::cout << "Length of input in words is " << processable_input.size() << std::endl;

        // std::cout << "Processing for grammatical completeness..." << std::endl;

        // std::unique_ptr<ParseTable> parsed_input = EarleyParser::build_items(grammar, processable_input);

        // RECOGNITION_STATUS parse_status = EarleyParser::diagnose(*parsed_input, grammar, processable_input);

        // std::cout << "Result is: " << RECOGNITION_STATUS_NAMES[parse_status] << std::endl;
    }
}