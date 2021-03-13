#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"

#include <iostream>
#include <memory>
#include <string>

// #include "TrizolamGrammarRules.h"
#include "bestinshow/engine/grammar/Grammar.h"
// #include "bestinshow/engine/grammar/EarleyParser.h"
// #include <spdlog/spdlog.h>

const std::function<ActionPayload(std::vector<std::string>)> empty_payload_generator =
    [](std::vector<std::string> player_input) { return ActionPayload{}; };

Grammar TrizolamGrammar::create_new_instance()
{
    Grammar *new_instance =
        new Grammar("trizolam-grammar", {
                                            {"command",
                                             {
                                                 {
                                                     {"personal-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"interaction-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"personal-command",
                                             {
                                                 {
                                                     {"travel-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"insight-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"meta-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"travel-command",
                                             {
                                                 {
                                                     {"direction", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"movement-command", SYMBOL_TYPE::NONTERMINAL},
                                                     {"direction", SYMBOL_TYPE::NONTERMINAL},
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
                                            {"movement-command",
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
                                             }},
                                            {"insight-command",
                                             {
                                                 {
                                                     {"perception-command", SYMBOL_TYPE::NONTERMINAL},
                                                     {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                     {"scene-object", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"perception-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"perception-command",
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
                                            {"optional-article",
                                             {
                                                 {
                                                     {"the", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"", SYMBOL_TYPE::TERMINAL},
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
                                            {"meta-command",
                                             {
                                                 {
                                                     {"save-state-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                                 {
                                                     {"log-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"save-state-command",
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
                                             },
                                             empty_payload_generator},
                                            {"interaction-command",
                                             {
                                                 {
                                                     {"inventory-command", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"inventory-command",
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
                                            {"put-in-inventory-command",
                                             {
                                                 {
                                                     {"take-command", SYMBOL_TYPE::NONTERMINAL},
                                                     {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                     {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"remove-from-inventory-command",
                                             {
                                                 {
                                                     {"drop-command", SYMBOL_TYPE::NONTERMINAL},
                                                     {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                     {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"place-object-command",
                                             {
                                                 {
                                                     {"place-command", SYMBOL_TYPE::NONTERMINAL},
                                                     {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                     {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                     {"preposition", SYMBOL_TYPE::NONTERMINAL},
                                                     {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                     {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                                 },
                                             }},
                                            {"take-command",
                                             {
                                                 {
                                                     {"take", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"pick", SYMBOL_TYPE::TERMINAL},
                                                     {"up", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"drop-command",
                                             {
                                                 {
                                                     {"drop", SYMBOL_TYPE::TERMINAL},
                                                 },
                                                 {
                                                     {"toss", SYMBOL_TYPE::TERMINAL},
                                                 },
                                             }},
                                            {"place-command",
                                             {
                                                 {
                                                     {"drop-command", SYMBOL_TYPE::NONTERMINAL},
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
                                        });
    // new_instance->add_rule(TrizolamGrammarRules::Command);
    // new_instance->add_rule(TrizolamGrammarRules::PersonalCommand);
    // new_instance->add_rule(TrizolamGrammarRules::TravelCommand);
    // new_instance->add_rule(TrizolamGrammarRules::Direction);
    // new_instance->add_rule(TrizolamGrammarRules::MovementCommand);
    // new_instance->add_rule(TrizolamGrammarRules::InsightCommand);
    // new_instance->add_rule(TrizolamGrammarRules::PerceptionCommand);
    // new_instance->add_rule(TrizolamGrammarRules::OptionalArticle);
    // new_instance->add_rule(TrizolamGrammarRules::SceneObject);
    // new_instance->add_rule(TrizolamGrammarRules::InteractableObject);
    // new_instance->add_rule(TrizolamGrammarRules::BasicWord);
    // new_instance->add_rule(TrizolamGrammarRules::NoninteractableObject);
    // new_instance->add_rule(TrizolamGrammarRules::Scene);
    // new_instance->add_rule(TrizolamGrammarRules::PlayerCharacter);
    // new_instance->add_rule(TrizolamGrammarRules::MetaCommand);
    // new_instance->add_rule(TrizolamGrammarRules::SaveStateCommand);
    // new_instance->add_rule(TrizolamGrammarRules::SaveCommand);
    // new_instance->add_rule(TrizolamGrammarRules::LoadCommand);
    // new_instance->add_rule(TrizolamGrammarRules::ResetCommand);
    // new_instance->add_rule(TrizolamGrammarRules::LogCommand);
    // new_instance->add_rule(TrizolamGrammarRules::InventoryCommand);
    // new_instance->add_rule(TrizolamGrammarRules::PutInInventoryCommand);
    // new_instance->add_rule(TrizolamGrammarRules::RemoveFromInventoryCommand);
    // new_instance->add_rule(TrizolamGrammarRules::PlaceObjectCommand);
    // new_instance->add_rule(TrizolamGrammarRules::TakeCommand);
    // new_instance->add_rule(TrizolamGrammarRules::DropCommand);
    // new_instance->add_rule(TrizolamGrammarRules::PlaceCommand);
    // new_instance->add_rule(TrizolamGrammarRules::Preposition);
    // new_instance->add_rule(TrizolamGrammarRules::InteractionCommand);

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