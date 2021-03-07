#include "InputProcessor.h"
#include "ICommandPayload.h"
#include "PlayerCommand.h"
#include "bestinshow/engine/grammar/EarleyParser.h"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/split.hpp"
#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <memory>

InputProcessor::InputProcessor() : grammar(TrizolamGrammar::get_instance())
{
}

PlayerCommand<ICommandPayload> InputProcessor::process(std::string player_input)
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

    return PlayerCommand<ICommandPayload>(); // TODO: Create CommandPayloads and process based on parse table
}

bool InputProcessor::not_isalnum_or_space(char c)
{
    return !std::isalnum(c) && !std::isspace(c);
}