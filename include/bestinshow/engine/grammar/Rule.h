#pragma once

#include "Symbol.h"
#include "spdlog/fmt/ostr.h"
#include <functional>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

using Production = std::vector<Symbol>;
using ProductionList = std::vector<Production>;
using ActionPayload = std::unordered_map<std::string, std::string>;

class Rule
{
  protected:
    std::string rule_name = "";
    ProductionList productions{};
    std::function<ActionPayload(std::vector<std::string>)> payload_generator =
        [](std::vector<std::string> player_input) { return ActionPayload{}; };
    int rule_weight;

  public:
    struct PlayerCommand
    {
        std::string type;
        ActionPayload payload;

        template <typename OStream> inline friend OStream &operator<<(OStream &ostream, const PlayerCommand &v)
        {
            ostream << "{ type: " << v.type << ", payload: { ";
            for (auto const &pair : v.payload)
            {
                ostream << pair.first << ": " << pair.second << ", ";
            }
            ostream << "} }";
            return ostream;
        }
    };
    Rule() = default;
    Rule(const std::string name);
    Rule(const std::string name, ProductionList productions);
    Rule(const std::string name, ProductionList productions, int rule_weight);
    Rule(const std::string, ProductionList, std::function<ActionPayload(std::vector<std::string>)>, int rule_weight);
    Rule(const Rule &prev);
    ~Rule() = default;

    std::string get_rule_name() const;
    void set_rule_name(std::string rule_name);
    ProductionList get_productions() const;
    void add_production(Production &production);
    std::function<ActionPayload(std::vector<std::string>)> get_payload_generator();
    void set_payload_generator(std::function<ActionPayload(std::vector<std::string>)>);
    PlayerCommand generate_command(std::vector<std::string>);
    void set_rule_weight(int weight);
    int get_rule_weight() const;
    template <typename OStream> friend OStream &operator<<(OStream &os, const Rule &v)
    {
        os << "(" << v.get_rule_weight() << ") "
           << "<" << v.get_rule_name() << "> ::= ";

        auto production_list = v.get_productions();
        if (production_list.size() > 0)
        {
            for (Production p : production_list)
            {
                for (Symbol s : p)
                {
                    os << s;
                }

                if (p != *(production_list.end() - 1))
                {
                    os << "|";
                }
            }
        }

        os << std::endl;

        return os;
    }

    inline Production &operator[](int i)
    {
        return productions.at(i);
    }

    // TODO: For some reason the sorting is just always backwards. Fix that
    inline bool operator<(const Rule &other) const
    {
        // spdlog::info("HELLO?! {}, {}", rule_weight, other.rule_weight);
        return rule_weight < other.rule_weight;
    }
};