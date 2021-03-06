#include "bestinshow/engine/grammar/EarleyParser.h"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/split.hpp"
#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"
#include <iostream>
#include <memory>
#include <string>

int main()
{
    std::string player_input;
    Grammar grammar = TrizolamGrammar::get_instance();
    while (true)
    {
        std::cout << "What is your command? " << std::endl;
        std::getline(std::cin, player_input);

        if (player_input == "quit")
        {
            return 0;
        }

        std::cout << "Processing the following input: " << player_input << std::endl;

        std::vector<std::string> processable_input;
        boost::split(processable_input, player_input, boost::is_any_of(" "), boost::token_compress_on);

        std::cout << "Length of input in words is " << processable_input.size() << std::endl;

        std::cout << "Processing for grammatical completeness..." << std::endl;

        std::unique_ptr<ParseTable> parsed_input = EarleyParser::build_items(grammar, processable_input);

        RECOGNITION_STATUS parse_status = EarleyParser::diagnose(*parsed_input, grammar, processable_input);

        std::cout << "Result is: " << RECOGNITION_STATUS_NAMES[parse_status] << std::endl;
    }
}