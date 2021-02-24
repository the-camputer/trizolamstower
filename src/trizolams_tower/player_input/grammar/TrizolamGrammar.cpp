#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"
#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include "bestinshow/engine/grammar/Symbol.h"
#include "bestinshow/engine/grammar/EarleyParser.h"
#include <iostream>
#include <memory>
#include <string>

Rule Command = 
{
    "command",
    {
        { { "personal-command", SYMBOL_TYPE::NONTERMINAL } },
        { { "interaction-command", SYMBOL_TYPE::NONTERMINAL } }
    }
};
Rule PersonalCommand =
{
    "personal-command",
    {
        { { "travel-command", SYMBOL_TYPE::NONTERMINAL } },
        { { "insight-command", SYMBOL_TYPE::NONTERMINAL } },
        { { "meta-command", SYMBOL_TYPE::NONTERMINAL } }
    }
};
Rule TravelCommand =
{
    "travel-command",
    {
        { { "direction", SYMBOL_TYPE::NONTERMINAL } },
        { { "movement-command", SYMBOL_TYPE::NONTERMINAL }, { "direction", SYMBOL_TYPE::NONTERMINAL } },
    }
};
Rule Direction =
{
    "direction",
    {
        { { "n(orth)?", SYMBOL_TYPE::TERMINAL } },
        { { "e(ast)?", SYMBOL_TYPE::TERMINAL } },
        { { "s(outh)?", SYMBOL_TYPE::TERMINAL } },
        { { "w(est)?", SYMBOL_TYPE::TERMINAL } },
    }
};
Rule MovementCommand =
{
    "movement-command",
    {
        { { "go", SYMBOL_TYPE::TERMINAL } },
        { { "travel", SYMBOL_TYPE::TERMINAL } },
        { { "walk", SYMBOL_TYPE::TERMINAL } }
    }
};



Grammar TrizolamGrammar::create_new_instance()
{
    Grammar *new_instance = new Grammar("trizolam-grammar");
    new_instance->add_rule(Command);
    new_instance->add_rule(PersonalCommand);
    new_instance->add_rule(TravelCommand);
    new_instance->add_rule(Direction);
    new_instance->add_rule(MovementCommand);

    return *new_instance;
}

std::unique_ptr<Grammar> TrizolamGrammar::m_instance;

Grammar& TrizolamGrammar::get_instance()
{
    if (!m_instance) {
        m_instance = std::make_unique<Grammar>(create_new_instance());
    }

    return *m_instance;
}

int main() {
    std::cout << "THING! " << std::endl;
    std::cout << TrizolamGrammar::get_instance() << std::endl;

    std::vector<std::string> sample_input = {"go", "west"};
    std::unique_ptr<ParseTable> sample_parse_table = EarleyParser::build_items(TrizolamGrammar::get_instance(), sample_input);
    RECOGNITION_STATUS result = EarleyParser::diagnose(*sample_parse_table, TrizolamGrammar::get_instance(), sample_input);

    std::cout << "TEST RESULT IS " << RECOGNITION_STATUS_NAMES[result] << std::endl;
}