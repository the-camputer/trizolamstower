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
        void add_rule(Rule& new_rule);
        std::vector<Rule*> get_rules();
        void set_name(std::string new_name);
        std::string get_name();
        void set_first_rule_name(std::string new_name);
        std::string get_first_rule_name();
};