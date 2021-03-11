#include "InputProcessor.h"
#include "bestinshow/engine/grammar/EarleyParser.h"
#include "commands/PlayerCommand.h"
#include "commands/PlayerCommandFactory.h"
#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"
#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iostream>
#include <memory>

InputProcessor::InputProcessor() : grammar(TrizolamGrammar::get_instance())
{
}

PlayerCommand InputProcessor::process(std::string player_input)
{
    // Remove special characters except spaces
    player_input.erase(std::remove_if(player_input.begin(), player_input.end(), InputProcessor::not_isalnum_or_space),
                       player_input.end());

    std::cout << "RAW INPUT: " << player_input << std::endl;
    std::vector<std::string> processable_input;
    boost::split(processable_input, player_input, boost::is_any_of(" "), boost::token_compress_on);

    std::cout << "SPLIT INPUT: " << boost::join(processable_input, ", ") << std::endl;

    std::unique_ptr<ParseTable> parsed_input = EarleyParser::build_items(grammar, processable_input);

    RECOGNITION_STATUS parse_status = EarleyParser::diagnose(*parsed_input, grammar, processable_input);

    std::cout << "Result is: " << RECOGNITION_STATUS_NAMES[parse_status] << std::endl;

    if (parse_status == RECOGNITION_STATUS::COMPLETE)
    {
        auto input_length = processable_input.size();
        auto final_state_set = parsed_input->at(input_length - 1);
        auto end_rule_earley_item =
            std::find_if(final_state_set.begin(), final_state_set.end(),
                         [&input_length](const EarleyItem &s) { return s.next == (int)input_length; });

        std::string rule_name = grammar[end_rule_earley_item->rule].get_rule_name();
        auto result = PlayerCommandFactory::generate_player_command(rule_name, processable_input);
        return result;
    }

    return PlayerCommand(); // TODO: Create CommandPayloads and process based on parse table
}

bool InputProcessor::not_isalnum_or_space(char c)
{
    return !std::isalnum(c) && !std::isspace(c);
}