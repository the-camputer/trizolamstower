#pragma once

#include "Rule.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <string>
#include <vector>

using RuleList = std::vector<Rule>;

class Grammar
{
  protected:
    std::string grammar_name = "";
    std::string first_rule_name = "";
    RuleList rules{};

  public:
    Grammar(const std::string grammar_name);
    Grammar(const std::string grammar_name, RuleList rules);
    Grammar();
    Grammar(const Grammar &prev);
    ~Grammar() = default;
    void add_rule(Rule &new_rule);
    void add_rule(Rule &&new_rule);
    RuleList get_rules() const;
    void set_name(std::string new_name);
    std::string get_name();
    void set_first_rule_name(std::string new_name);
    std::string get_first_rule_name();

    template <typename OStream> inline friend OStream &operator<<(OStream &ostream, const Grammar &v)
    {
        ostream << "<" << v.grammar_name << "> ::= ";
        if (v.rules.size() > 0)
        {
            ostream << "<" << v.first_rule_name << ">\n";
            for (Rule rule : v.get_rules())
            {
                ostream << rule;
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
        return get_rules().at(i);
    }
};