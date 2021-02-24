#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include <string>
#include <vector>
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

Grammar::Grammar(const std::string grammar_name) : grammar_name { grammar_name } {}

Grammar::Grammar(const Grammar &prev) {
    grammar_name = prev.grammar_name;
    first_rule_name = prev.first_rule_name;
    rules = std::make_unique<RuleList>(*prev.rules);
}

Grammar::Grammar() {}

void Grammar::add_rule(Rule& new_rule)
{
    if (!rules) {
        rules = std::make_unique<RuleList>();
        first_rule_name = new_rule.get_rule_name();
    }

    rules->push_back(new_rule);
}

void Grammar::add_rule(Rule&& new_rule)
{
    if (!rules) {
        rules = std::make_unique<RuleList>();
        first_rule_name = new_rule.get_rule_name();
    }

    rules->push_back(new_rule);
}

RuleList Grammar::get_rules() const
{
    return *rules;
}

void Grammar::set_name(std::string new_name)
{
    grammar_name = new_name;
}

std::string Grammar::get_name()
{
    return grammar_name;
}

void Grammar::set_first_rule_name(std::string new_name)
{
    first_rule_name = new_name;
}

std::string Grammar::get_first_rule_name()
{
    return first_rule_name;
}