#pragma once
#include "bestinshow/engine/grammar/Grammar.h"
#include <memory>

class TrizolamGrammar {
    private:
        TrizolamGrammar();
        static Grammar create_new_instance();

        static std::unique_ptr<Grammar> m_instance;
        
    public:
        ~TrizolamGrammar() = default;
        static Grammar& get_instance();
        static void add_interactable_object(Production);
        static void add_interation_command(Production);
        static bool interactable_exists(Production);
        static bool interaction_command_exists(Production);
};
