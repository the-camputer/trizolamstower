#pragma once
#include "bestinshow/engine/grammar/Rule.h"

class TrizolamGrammarRules
{
  public:
    static inline Rule Command = {
        "command",
        {{{"personal-command", SYMBOL_TYPE::NONTERMINAL}}, {{"interaction-command", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule PersonalCommand = {"personal-command",
                                          {{{"travel-command", SYMBOL_TYPE::NONTERMINAL}},
                                           {{"insight-command", SYMBOL_TYPE::NONTERMINAL}},
                                           {{"meta-command", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule TravelCommand = {
        "travel-command",
        {
            {{"direction", SYMBOL_TYPE::NONTERMINAL}},
            {{"movement-command", SYMBOL_TYPE::NONTERMINAL}, {"direction", SYMBOL_TYPE::NONTERMINAL}},
        }};

    static inline Rule Direction = {"direction",
                                    {
                                        {{"n(orth)?", SYMBOL_TYPE::TERMINAL}},
                                        {{"e(ast)?", SYMBOL_TYPE::TERMINAL}},
                                        {{"s(outh)?", SYMBOL_TYPE::TERMINAL}},
                                        {{"w(est)?", SYMBOL_TYPE::TERMINAL}},
                                    }};

    static inline Rule MovementCommand = {
        "movement-command",
        {{{"go", SYMBOL_TYPE::TERMINAL}}, {{"travel", SYMBOL_TYPE::TERMINAL}}, {{"walk", SYMBOL_TYPE::TERMINAL}}}};

    static inline Rule InsightCommand = {"insight-command",
                                         {{{"perception-command", SYMBOL_TYPE::NONTERMINAL},
                                           {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                           {"scene-object", SYMBOL_TYPE::NONTERMINAL}},
                                          {{"perception-command", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule PerceptionCommand = {"perception-command",
                                            {{{"examine", SYMBOL_TYPE::TERMINAL}},
                                             {{"look(\\s)?at", SYMBOL_TYPE::TERMINAL}},
                                             {{"look(\\s)?around", SYMBOL_TYPE::TERMINAL}}}};

    static inline Rule OptionalArticle = {"optional-article",
                                          {{{"the", SYMBOL_TYPE::TERMINAL}}, {{"", SYMBOL_TYPE::TERMINAL}}}};

    static inline Rule SceneObject = {
        "scene-object",
        {{{"interactable-object", SYMBOL_TYPE::NONTERMINAL}}, {{"noninteractable-object", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule InteractableObject = {"interactable-object",
                                             {
                                                 {{"glove", SYMBOL_TYPE::TERMINAL}}
                                                 // This will be filled in dynamically based on scene and configuration
                                             }};

    static inline Rule NoninteractableObject = {
        "noninteractable-object",
        {{{"scene", SYMBOL_TYPE::NONTERMINAL}}, {{"player-character", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule Scene = {"scene",
                                {{{"area", SYMBOL_TYPE::TERMINAL}},
                                 {{"what(\\s)?is(\\s)?around", SYMBOL_TYPE::TERMINAL}},
                                 {{"nearby", SYMBOL_TYPE::TERMINAL}}}

    };

    static inline Rule PlayerCharacter = {"player-character",
                                          {{{"myself", SYMBOL_TYPE::TERMINAL}}, {{"me", SYMBOL_TYPE::TERMINAL}}}};

    static inline Rule MetaCommand = {
        "meta-command",
        {{{"save-state-command", SYMBOL_TYPE::NONTERMINAL}}, {{"inventory-command", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule SaveStateCommand = {"save-state-command",
                                           {{{"save-command", SYMBOL_TYPE::NONTERMINAL}},
                                            {{"load-command", SYMBOL_TYPE::NONTERMINAL}},
                                            {{"reset-command", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule SaveCommand = {"save-command",
                                      {
                                          {{"save((\\s)?game)?", SYMBOL_TYPE::TERMINAL}},
                                      }};

    static inline Rule LoadCommand = {"load-command", {{{"load((\\s)?game)?", SYMBOL_TYPE::TERMINAL}}}};

    static inline Rule ResetCommand = {"reset-command", {{{"reset((\\s)?game)?", SYMBOL_TYPE::TERMINAL}}}};

    static inline Rule InventoryCommand = {"inventory-command",
                                           {{{"put-in-inventory-command", SYMBOL_TYPE::NONTERMINAL}},
                                            {{"remove-from-inventory-command", SYMBOL_TYPE::NONTERMINAL}},
                                            {{"place-object-command", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule PutInInventoryCommand = {"put-in-inventory-command",
                                                {{{"take-command", SYMBOL_TYPE::NONTERMINAL},
                                                  {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                  {"interactable-object", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule RemoveFromInventoryCommand = {"remove-from-inventory-command",
                                                     {{{"drop-command", SYMBOL_TYPE::NONTERMINAL},
                                                       {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                                       {"interactable-object", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule PlaceObjectCommand = {"place-object-command",
                                             {{{"place-command", SYMBOL_TYPE::NONTERMINAL},
                                               {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                               {"interactable-object", SYMBOL_TYPE::NONTERMINAL},
                                               {"preposition", SYMBOL_TYPE::NONTERMINAL},
                                               {"optional-article", SYMBOL_TYPE::NONTERMINAL},
                                               {"interactable-object", SYMBOL_TYPE::NONTERMINAL}}}};

    static inline Rule TakeCommand = {"take-command",
                                      {{{"take", SYMBOL_TYPE::TERMINAL}}, {{"pick(\\s)?up", SYMBOL_TYPE::TERMINAL}}}};

    static inline Rule DropCommand = {"drop-command",
                                      {{{"drop", SYMBOL_TYPE::TERMINAL}}, {{"toss", SYMBOL_TYPE::TERMINAL}}}};

    static inline Rule PlaceCommand = {"place-command",
                                       {{{"drop-command", SYMBOL_TYPE::NONTERMINAL}},
                                        {{"place", SYMBOL_TYPE::TERMINAL}},
                                        {{"put", SYMBOL_TYPE::TERMINAL}},
                                        {{"put", SYMBOL_TYPE::TERMINAL}},
                                        {{"lay", SYMBOL_TYPE::TERMINAL}},
                                        {{"set", SYMBOL_TYPE::TERMINAL}},
                                        {{"insert", SYMBOL_TYPE::TERMINAL}}}};

    static inline Rule Preposition = {"preposition",
                                      {{{"on", SYMBOL_TYPE::TERMINAL}},
                                       {{"in", SYMBOL_TYPE::TERMINAL}},
                                       {{"inside", SYMBOL_TYPE::TERMINAL}},
                                       {{"into", SYMBOL_TYPE::TERMINAL}}}};

    static inline Rule InteractionCommand = {"interaction-command",
                                             {
                                                 // This will be filled in dynamically based on scene and configuration
                                             }};
};