#pragma once

#include <string>
#include <vector>
#include "Rule.h"

class Grammar {
    protected:
        std::string grammar_name = "";
        std::string first_rule_name = "";
        std::vector<Rule*> *rules = nullptr;

    public:
        Grammar(const std::string grammar_name);
        Grammar();
        Grammar(const Grammar &prev);
        ~Grammar();
};