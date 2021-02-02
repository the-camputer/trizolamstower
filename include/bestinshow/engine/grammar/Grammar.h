#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Rule.h"

using RuleList = std::vector<Rule>;

class Grammar {
    protected:
        std::string grammar_name = "";
        std::string first_rule_name = "";
        std::unique_ptr<RuleList> rules = nullptr;

    public:
        Grammar(const std::string grammar_name);
        Grammar();
        Grammar(const Grammar &prev);
        ~Grammar() = default;
        void add_rule(Rule& new_rule);
        RuleList get_rules() const;
        void set_name(std::string new_name);
        std::string get_name();
        void set_first_rule_name(std::string new_name);
        std::string get_first_rule_name();

        friend std::ostream& operator<<(std::ostream& ostream, const Grammar& v);
        inline Rule operator[](int i)
        {
            return get_rules().at(i);
        }
};