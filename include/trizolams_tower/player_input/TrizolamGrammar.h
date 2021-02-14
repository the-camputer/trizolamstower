#pragma once
#include "bestinshow/engine/grammar/Grammar.h"

class TrizolamGrammar : public Grammar {
    private:
        static TrizolamGrammar m_instance;
        
    public:
        TrizolamGrammar();
        TrizolamGrammar(TrizolamGrammar& other) = delete;
        void operator=(const TrizolamGrammar&) = delete;
        ~TrizolamGrammar() = default;
        static TrizolamGrammar get_instance();
};
