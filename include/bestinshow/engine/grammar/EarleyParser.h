#pragma once
#include "Grammar.h"
#include "EarleyItem.h"
#include <string>

enum RECOGNITION_STATUS { COMPLETE, INCOMPLETE, PARTIAL_UNRECOGNIZED, WHOLE_UNRECOGNIZED };

class EarleyParser {
    public:
        static StateSet build_items(Grammar grammar, std::string input);
        static RECOGNITION_STATUS diagnose(StateSet state_set, Grammar grammar, std::string input);
    private:
        static void complete(StateSet state_set, int input_pos, int state_set_pos, Grammar grammar);
        static void scan(StateSet state_set, int input_pos, int state_set_pos, Symbol symbol, std::string input);
        static void predict(StateSet state_set, int input_pos, Symbol symbol, Grammar grammar);
        static bool has_partial_parse(StateSet state_set, int input_pos, Grammar grammar);
        static bool has_complete_parse(StateSet state_set, Grammar grammar);
        static bool last_partial_parse(StateSet state_set, Grammar grammar);
        static Symbol next_symbol(Grammar grammar, EarleyItem item);
        static std::string name(Grammar grammar, EarleyItem item);
};