#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include <string>
#include <vector>


Grammar::Grammar(const std::string grammar_name) : grammar_name { grammar_name } {}

Grammar::Grammar(const Grammar &prev) {
    grammar_name = prev.grammar_name;
    first_rule_name = prev.first_rule_name;
    rules = prev.rules;
}

Grammar::Grammar() {}

Grammar::~Grammar() {
    if (rules != nullptr) {
        for(auto p = (*rules).begin(); p != (*rules).end(); p++) {
            delete *p;
        }

        delete rules;
    }
}

void Grammar::add_rule(Rule& new_rule)
{
    if (!rules) {
        rules = new std::vector<Rule*> { &new_rule };
        first_rule_name = new_rule.get_rule_name();
    } else {
        rules->push_back(&new_rule);
    }
}

std::vector<Rule*> Grammar::get_rules() const
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

std::ostream& operator<<(std::ostream& os, const Grammar& v)
{
    os << "<" << v.grammar_name << "> ::= ";
    if (v.rules != nullptr) {
        os << "<" << v.first_rule_name << ">\n";
        for(Rule *rule : v.get_rules()) {
            os << *rule;
        }
    } else {
        os << std::endl;
    }

    return os;
}