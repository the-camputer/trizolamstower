#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <algorithm>
#include <string>
#include <vector>

// Grammar::~Grammar()
// {
//     for (auto rule : rules)
//     {
//         delete rule;
//     }
// }

bool Grammar::compare_rule_ptr(std::shared_ptr<Rule> a, std::shared_ptr<Rule> b)
{
    return *a < *b;
}

Grammar::Grammar(const std::string grammar_name) : grammar_name{grammar_name}
{
}

Grammar::Grammar(const std::string grammar_name, RuleList rules) : grammar_name{grammar_name}, rules{rules}
{
    // for (auto &rule : rules)
    // {
    //     this->rules.push_back(std::move(rule));
    // }

    first_rule_name = rules[0]->get_rule_name();
    std::sort(this->rules.begin(), this->rules.end(), compare_rule_ptr);
}

Grammar::Grammar(const Grammar &prev)
{
    grammar_name = prev.grammar_name;
    first_rule_name = prev.first_rule_name;
    rules = prev.rules;
    // for (auto &rule : prev.rules)
    // {
    //     this->rules.push_back(std::move(rule));
    // }
    // std::sort(this->rules.begin(), this->rules.end());
}

Grammar::Grammar()
{
}

void Grammar::add_rule(Rule &new_rule)
{
    if (first_rule_name.empty())
    {
        first_rule_name = new_rule.get_rule_name();
        rules.push_back(std::make_shared<Rule>(new Rule{new_rule}));
    }
    else
    {
        int highest_weight = rules.back()->get_rule_weight();
        if (new_rule.get_rule_weight() >= highest_weight)
        {
            rules.push_back(std::make_shared<Rule>(new Rule{new_rule}));
        }
        else
        {
            auto iter = rules.rbegin();
            while (iter != rules.rend())
            {
                if ((*iter)->get_rule_weight() == new_rule.get_rule_weight() || iter.base() == rules.begin())
                {
                    rules.insert(iter.base(), std::make_shared<Rule>(new Rule{new_rule}));
                    break;
                }
                iter++;
            }
        }
    }
}

void Grammar::add_rule(Rule &&new_rule)
{
    if (first_rule_name.empty())
    {
        first_rule_name = new_rule.get_rule_name();
        rules.push_back(std::make_shared<Rule>(new Rule{new_rule}));
    }
    else
    {
        int highest_weight = rules.back()->get_rule_weight();
        if (new_rule.get_rule_weight() >= highest_weight)
        {
            rules.push_back(std::make_shared<Rule>(new Rule{new_rule}));
        }
        else
        {
            auto iter = rules.rbegin();
            while (iter != rules.rend())
            {
                if ((*iter)->get_rule_weight() == new_rule.get_rule_weight() || iter.base() == rules.begin())
                {
                    rules.insert(iter.base(), std::make_shared<Rule>(new Rule{new_rule}));
                    break;
                }
                iter++;
            }
        }
    }
}

RuleList Grammar::get_rules() const
{
    return rules;
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

void Grammar::add_production(std::string rule_name, Production production)
{
    auto rules_list = get_rules();
    for (auto &rule : rules_list)
    {
        if (rule->get_rule_name() == rule_name)
        {
            rule->add_production(production);
        }
    }
    // auto it = std::find_if(rules_list.begin(), rules_list.end(),
    //                        [&rule_name](const Rule *rule) { return rule->get_rule_name() == rule_name; });

    // (*it)->add_production(production);
}