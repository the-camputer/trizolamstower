#include "TrizolamGrammar.h"
#include "../commands/MovementDirections.h"
#include "bestinshow/engine/grammar/Grammar.h"
#include "../commands/TravelCommand.h"
#include <algorithm>
#include <boost/algorithm/string/join.hpp>
#include <iostream>
#include <memory>
#include <string>

// TODO: These seem really brittle. Figure out a better way to handle sifting through data
const std::function<ActionPayload(std::vector<std::string>)> inventory_command_payload_generator =
    [](std::vector<std::string> player_input)
{
    player_input.erase(std::remove(player_input.begin(), player_input.end(), "the"), player_input.end());
    std::vector<std::string> object_descr;
    std::string object = player_input.back();

    return ActionPayload{{"object", object}};
};

const std::function<ActionPayload(std::vector<std::string>)> place_command_payload_generator =
    [](std::vector<std::string> player_input)
{
    player_input.erase(std::remove(player_input.begin(), player_input.end(), "the"), player_input.end());

    auto object = player_input[1];
    auto destination = player_input.end() - 1;

    return ActionPayload{{"object", object}, {"destination", *destination}};
};

std::unique_ptr<Grammar> TrizolamGrammar::m_instance;

// TODO: Probably best to get rid of this and just have a static grammar so we can attach the Command-based payload generators properly
std::unordered_map<std::string, std::vector<std::vector<std::string>>> TrizolamGrammar::m_terminal_phrases{
    {"optional-article", {{"the"}, {""}}},
    {"direction", {{"n(orth)?"}, {"e(ast)?"}, {"s(outh)?"}, {"w(est)?"}}},
    {"movement", {{"go"}, {"travel"}, {"walk"}, {"move"}, {"run"}}},
    {"basic-object", {{"sword"}}},
    {"scene", {{"area"}, {"what", "is", "around"}, {"nearby"}}},
    {"player-character", {{"me"}, {"myself"}}},
    {"perception", {{"examine"}, {"look", "at"}, {"look", "around"}}},
    {"preposition", {{"on"}, {"in"}, {"inside"}, {"into"}}},
    {"take", {{"take"}, {"grab"}, {"pick", "up"}}},
    {"drop", {{"drop"}, {"toss"}, {"remove"}}},
    {"save-command", {{"save", "game"}, {"save"}}},
    {"load-command", {{"load", "game"}, {"load"}}},
    {"reset-command", {{"reset", "game"}, {"reset"}}},
    {"log-command", {{"show", "log"}, {"log"}}},

};

Grammar TrizolamGrammar::create_new_grammar()
{
    Grammar *new_instance =
        new Grammar(
            "trizolam-grammar",
            {
                std::make_shared<Rule>(new Rule{"input",
                                                {
                                                    {
                                                        {"personal", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"interaction", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                },
                                                -1}),
                std::make_shared<Rule>(new Rule{"personal",
                                                {
                                                    {
                                                        {"travel-command", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"insight-command", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"meta", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                }}),
                std::make_shared<Rule>(new Rule{"scene-object",
                                                {
                                                    {
                                                        {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"noninteractable-object", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                }}),
                std::make_shared<Rule>(new Rule{"interactable-object",
                                                {
                                                    {
                                                        {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                        {"basic-object", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"basic-object", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                }}),
                std::make_shared<Rule>(new Rule{"noninteractable-object",
                                                {
                                                    {
                                                        {"scene", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"player-character", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                }}),
                std::make_shared<Rule>(new Rule{"insight-command",
                                                {
                                                    {
                                                        {"perception", SYMBOL_TYPE::NONTERMINAL},
                                                        {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                        {"scene-object", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"perception", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                },
                                                1}),
                std::make_shared<Rule>(new Rule{"meta",
                                                {
                                                    {
                                                        {"save-state", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"log-command", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                }}),
                std::make_shared<Rule>(new Rule{"save-state",
                                                {
                                                    {
                                                        {"save-command", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"load-command", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"reset-command", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                }}),
                std::make_shared<Rule>(new Rule{"interaction",
                                                {
                                                    {
                                                        {"inventory", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                }}),
                std::make_shared<Rule>(new Rule{"inventory",
                                                {
                                                    {
                                                        {"open-inventory-command", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"put-in-inventory-command", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"remove-from-inventory-command", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"place-object-command", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                }}),
                std::make_shared<Rule>(new Rule{"place",
                                                {
                                                    {
                                                        {"drop", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"place", SYMBOL_TYPE::TERMINAL},
                                                    },
                                                    {
                                                        {"put", SYMBOL_TYPE::TERMINAL},
                                                    },
                                                    {
                                                        {"put", SYMBOL_TYPE::TERMINAL},
                                                    },
                                                    {
                                                        {"lay", SYMBOL_TYPE::TERMINAL},
                                                    },
                                                    {
                                                        {"set", SYMBOL_TYPE::TERMINAL},
                                                    },
                                                    {
                                                        {"insert", SYMBOL_TYPE::TERMINAL},
                                                    },
                                                }}),
                std::make_shared<Rule>(new Rule{"travel-command",
                                                {
                                                    {
                                                        {"direction", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                    {
                                                        {"movement", SYMBOL_TYPE::NONTERMINAL},
                                                        {"direction", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                },
                                                m_command_processor->get_payload_generator("travel-command"),
                                                1}),
                std::make_shared<Rule>(new Rule{"place-object-command",
                                                {
                                                    {
                                                        {"place", SYMBOL_TYPE::NONTERMINAL},
                                                        {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                        {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                        {"preposition", SYMBOL_TYPE::NONTERMINAL},
                                                        {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                        {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                },
                                                place_command_payload_generator,
                                                1}),
                std::make_shared<Rule>(new Rule{"open-inventory-command",
                                                {
                                                    {
                                                        {"open", SYMBOL_TYPE::TERMINAL},
                                                        {"inventory", SYMBOL_TYPE::TERMINAL},
                                                    },
                                                },
                                                1}),
                std::make_shared<Rule>(new Rule{"put-in-inventory-command",
                                                {
                                                    {
                                                        {"take", SYMBOL_TYPE::NONTERMINAL},
                                                        {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                        {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                },
                                                inventory_command_payload_generator,
                                                1}),
                std::make_shared<Rule>(new Rule{"remove-from-inventory-command",
                                                {
                                                    {
                                                        {"drop", SYMBOL_TYPE::NONTERMINAL},
                                                        {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                        {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                    },
                                                },
                                                inventory_command_payload_generator,
                                                1}),
            });

    for (auto &phrase_map : m_terminal_phrases)
    {
        Rule new_rule{phrase_map.first};
        ProductionList productions_list;
        for (auto &phrase : phrase_map.second)
        {
            Production new_production{};
            for (auto &symbol : phrase)
            {
                new_production.push_back({symbol, SYMBOL_TYPE::TERMINAL});
            }
            new_rule.add_production(new_production);
        }

        if (phrase_map.first.find("command") != std::string::npos)
        {
            new_rule.set_rule_weight(1);
        }

        new_instance->add_rule(new_rule);
    }

    return *new_instance;
}

// void TrizolamGrammar::add_object(std::vector<std::string> new_object)
// {
//     m_terminal_phrases["basic-object"].push_back(new_object);
//     Production obj_production{};
//     for (auto str : new_object)
//     {
//         obj_production.push_back({str, SYMBOL_TYPE::TERMINAL});
//     }
//     // Production obj_production = Production{{new_object, SYMBOL_TYPE::TERMINAL}};
//     get_grammar().add_production("basic-object", obj_production);
// }

TrizolamGrammar::TrizolamGrammar(std::shared_ptr<CommandProcessor> command_processor)
{
    m_command_processor = command_processor;
}

Grammar &TrizolamGrammar::get_grammar()
{
    if (!m_grammar)
    {
        m_grammar = std::make_unique<Grammar>(create_new_grammar());
    }

    return *m_grammar;
}