#pragma once

#include "Rule.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include <memory>
#include <string>
#include <vector>

using RuleList = std::vector<std::shared_ptr<Rule>>;

class Grammar
{
protected:
    std::string grammar_name = "";
    std::string first_rule_name = "";
    RuleList rules{};
    static bool compare_rule_ptr(std::shared_ptr<Rule>, std::shared_ptr<Rule>);

public:
    Grammar(const std::string grammar_name);
    Grammar(const std::string grammar_name, RuleList rules);
    Grammar();
    Grammar(const Grammar &prev);
    ~Grammar() = default;
    void add_rule(Rule &new_rule);
    void add_rule(Rule &&new_rule);
    void add_production(std::string, Production);
    RuleList get_rules() const;
    void set_name(std::string new_name);
    std::string get_name();
    void set_first_rule_name(std::string new_name);
    std::string get_first_rule_name();

    template <typename OStream>
    inline friend OStream &operator<<(OStream &ostream, const Grammar &v)
    {
        ostream << "<" << v.grammar_name << "> ::= ";
        if (v.rules.size() > 0)
        {
            ostream << "<" << v.first_rule_name << ">\n";
            for (auto rule : v.get_rules())
            {
                ostream << *rule;
            }
        }
        else
        {
            ostream << std::endl;
        }

        return ostream;
    }

    inline Rule operator[](int i)
    {
        return *get_rules().at(i);
    }

    // inline Rule *operator[](std::string rule_name)
    // {
    //     auto rules_list = get_rules();
    //     auto it = std::find_if(rules_list.begin(), rules_list.end(),
    //                            [&rule_name](const Rule &rule) { return rule.get_rule_name() == rule_name; });

    //     auto index = it - rules_list.begin();

    //     return &(get_rules().at(index));
    // }
};