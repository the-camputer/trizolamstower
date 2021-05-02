#include "InputProcessor.h"
#include "bestinshow/engine/grammar/EarleyParser.h"
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

Rule::PlayerCommand InputProcessor::process(std::string player_input)
{
    // Remove special characters except spaces
    player_input.erase(std::remove_if(player_input.begin(), player_input.end(), InputProcessor::not_isalnum_or_space),
                       player_input.end());

    // std::cout << "RAW INPUT: " << player_input << std::endl;
    std::vector<std::string> processable_input;
    boost::split(processable_input, player_input, boost::is_any_of(" "), boost::token_compress_on);

    // std::cout << "SPLIT INPUT: " << boost::join(processable_input, ", ") << std::endl;

    std::unique_ptr<ParseTable> parsed_input = EarleyParser::build_items(grammar, processable_input);

    RECOGNITION_STATUS parse_status = EarleyParser::diagnose(*parsed_input, grammar, processable_input);

    std::cout << "Result is: " << RECOGNITION_STATUS_NAMES[parse_status] << std::endl;

    if (parse_status == RECOGNITION_STATUS::COMPLETE)
    {
        auto final_state_set = parsed_input->at(parsed_input->size() - 1);
        std::sort(final_state_set.begin(), final_state_set.end(),
                  [](const EarleyItem &lhs, const EarleyItem &rhs) { return lhs.rule < rhs.rule; });
        auto end_rule_earley_item = final_state_set.back();

        Rule recognized_rule = grammar[end_rule_earley_item.rule];
        std::string rule_name = recognized_rule.get_rule_name();
        return recognized_rule.generate_command(processable_input);
    }
    else
    {
        return Rule::PlayerCommand{"ERROR", ActionPayload{{"type", RECOGNITION_STATUS_NAMES[parse_status]}}};
    }
}

bool InputProcessor::not_isalnum_or_space(char c)
{
    return !std::isalnum(c) && !std::isspace(c);
}