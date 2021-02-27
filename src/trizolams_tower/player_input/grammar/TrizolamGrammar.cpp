#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"
#include "TrizolamGrammarRules.h"
#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/EarleyParser.h"
#include <iostream>
#include <memory>
#include <string>

Grammar TrizolamGrammar::create_new_instance()
{
    Grammar *new_instance = new Grammar("trizolam-grammar");
    new_instance->add_rule(TrizolamGrammarRules::Command);
    new_instance->add_rule(TrizolamGrammarRules::PersonalCommand);
    new_instance->add_rule(TrizolamGrammarRules::TravelCommand);
    new_instance->add_rule(TrizolamGrammarRules::Direction);
    new_instance->add_rule(TrizolamGrammarRules::MovementCommand);
    new_instance->add_rule(TrizolamGrammarRules::InsightCommand);
    new_instance->add_rule(TrizolamGrammarRules::PerceptionCommand);
    new_instance->add_rule(TrizolamGrammarRules::OptionalArticle);
    new_instance->add_rule(TrizolamGrammarRules::SceneObject);
    new_instance->add_rule(TrizolamGrammarRules::InteractableObject);
    new_instance->add_rule(TrizolamGrammarRules::NoninteractableObject);
    new_instance->add_rule(TrizolamGrammarRules::Scene);
    new_instance->add_rule(TrizolamGrammarRules::PlayerCharacter);
    new_instance->add_rule(TrizolamGrammarRules::MetaCommand);
    new_instance->add_rule(TrizolamGrammarRules::SaveStateCommand);
    new_instance->add_rule(TrizolamGrammarRules::SaveCommand);
    new_instance->add_rule(TrizolamGrammarRules::LoadCommand);
    new_instance->add_rule(TrizolamGrammarRules::ResetCommand);
    new_instance->add_rule(TrizolamGrammarRules::InventoryCommand);
    new_instance->add_rule(TrizolamGrammarRules::TakeCommand);
    new_instance->add_rule(TrizolamGrammarRules::DropCommand);
    new_instance->add_rule(TrizolamGrammarRules::PlaceCommand);
    new_instance->add_rule(TrizolamGrammarRules::Preposition);
    new_instance->add_rule(TrizolamGrammarRules::InteractionCommand);

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