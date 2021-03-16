#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"
#include "../commands/MovementDirections.h"
#include "bestinshow/engine/grammar/Grammar.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

const std::function<ActionPayload(std::vector<std::string>)> travel_command_payload_generator =
    [](std::vector<std::string> player_input) {
        auto get_direction = [](std::string direction_raw) {
            std::transform(direction_raw.begin(), direction_raw.end(), direction_raw.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            auto direction = direction_raw.at(0);
            auto result = MOVEMENT_DIRECTION::UNKOWN;
            switch (direction)
            {
            case 'n':
                result = MOVEMENT_DIRECTION::NORTH;
                break;
            case 'e':
                result = MOVEMENT_DIRECTION::EAST;
                break;
            case 's':
                result = MOVEMENT_DIRECTION::SOUTH;
                break;
            case 'w':
                result = MOVEMENT_DIRECTION::WEST;
                break;
            default:
                result = MOVEMENT_DIRECTION::UNKOWN;
                break;
            };

            return result;
        };

        MOVEMENT_DIRECTION direction_to_go;

        if (player_input.size() == 1)
        {
            direction_to_go = get_direction(player_input[0]);
        }
        else
        {
            direction_to_go = get_direction(player_input[1]);
        }

        return ActionPayload{{"direction", std::to_string(direction_to_go)}};
    };

Grammar TrizolamGrammar::create_new_instance()
{
    Grammar *new_instance =
        new Grammar("trizolam-grammar", {
                                            {"input",
                                             {
                                                 {
                                                     {"personal", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"interaction", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"optional-article",
                                             {
                                                 {
                                                     {"the", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"personal",
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
                                             }},
                                            {"direction",
                                             {
                                                 {
                                                     {"n(orth)?", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"e(ast)?", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"s(outh)?", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"w(est)?", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"movement",
                                             {
                                                 {
                                                     {"go", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"travel", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"walk", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"move", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"run", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"scene-object",
                                             {
                                                 {
                                                     {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"noninteractable-object", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"interactable-object",
                                             {
                                                 {
                                                     {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                     {"basic-word", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"basic-word", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"basic-word",
                                             {
                                                 {
                                                     {"\\w+", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"noninteractable-object",
                                             {
                                                 {
                                                     {"scene", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"player-character", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"scene",
                                             {
                                                 {
                                                     {"area", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"what", SYMBOL_TYPE::TERMINAL},
                                                     {"is", SYMBOL_TYPE::TERMINAL},
                                                     {"around", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"nearby", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"player-character",
                                             {
                                                 {
                                                     {"myself", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"me", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"perception",
                                             {
                                                 {
                                                     {"examine", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"look", SYMBOL_TYPE::TERMINAL},
                                                     {"at", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"look", SYMBOL_TYPE::TERMINAL},
                                                     {"around", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"insight-command",
                                             {
                                                 {
                                                     {"perception", SYMBOL_TYPE::NONTERMINAL},
                                                     {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                     {"scene-object", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"perception", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"meta",
                                             {
                                                 {
                                                     {"save-state", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"log-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"save-state",
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
                                             }},
                                            {"interaction",
                                             {
                                                 {
                                                     {"inventory", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"preposition",
                                             {
                                                 {
                                                     {"on", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"in", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"inside", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"into", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"inventory",
                                             {
                                                 {
                                                     {"put-in-inventory-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"remove-from-inventory-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"place-object-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"take",
                                             {
                                                 {
                                                     {"take", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"pick", SYMBOL_TYPE::TERMINAL},
                                                     {"up", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"drop",
                                             {
                                                 {
                                                     {"drop", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"toss", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"place",
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
                                             }},
                                            {"save-command",
                                             {
                                                 {
                                                     {"save", SYMBOL_TYPE::TERMINAL},
                                                     {"game", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"save", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"load-command",
                                             {
                                                 {
                                                     {"load", SYMBOL_TYPE::TERMINAL},
                                                     {"game", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"load", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"reset-command",
                                             {
                                                 {
                                                     {"reset", SYMBOL_TYPE::TERMINAL},
                                                     {"game", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"reset", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"log-command",
                                             {
                                                 {
                                                     {"show", SYMBOL_TYPE::TERMINAL},
                                                     {"log", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"log", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"travel-command",
                                             {
                                                 {
                                                     {"direction", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"movement", SYMBOL_TYPE::NONTERMINAL},
                                                     {"direction", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             },
                                             travel_command_payload_generator},
                                            {"place-object-command",
                                             {
                                                 {
                                                     {"place", SYMBOL_TYPE::NONTERMINAL},
                                                     {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                     {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                     {"preposition", SYMBOL_TYPE::NONTERMINAL},
                                                     {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                     {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"take", SYMBOL_TYPE::NONTERMINAL},
                                                     {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                     {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"remove-from-inventory-command",
                                             {
                                                 {
                                                     {"drop", SYMBOL_TYPE::NONTERMINAL},
                                                     {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                     {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                        });
    return *new_instance;
}

std::unique_ptr<Grammar> TrizolamGrammar::m_instance;

Grammar &TrizolamGrammar::get_instance()
{
    if (!m_instance)
    {
        m_instance = std::make_unique<Grammar>(create_new_instance());
    }

    return *m_instance;
}