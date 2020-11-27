#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include <string>
#include <vector>


Grammar::Grammar(const std::string grammar_name) : grammar_name { grammar_name } {
    rules = new std::vector<Rule*>{};
}

Grammar::Grammar(const Grammar &prev) {
    grammar_name = prev.grammar_name;
    first_rule_name = prev.first_rule_name;
    rules = prev.rules;
}

Grammar::Grammar() {
    rules = new std::vector<Rule*>{};
}

Grammar::~Grammar() {
    for(auto p = (*rules).begin(); p != (*rules).end(); p++) {
        delete *p;
    }

    delete rules;
}