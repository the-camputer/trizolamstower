#include "bestinshow/engine/grammar/Rule.h"
#include "bestinshow/engine/grammar/Symbol.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

Rule::Rule(const std::string name) : rule_name{name}, rule_weight{0}
{
}

Rule::Rule(const std::string name, ProductionList productions)
    : rule_name{name}, productions{productions}, rule_weight{0}
{
}

Rule::Rule(const std::string name, ProductionList productions, int rule_weight)
    : rule_name{name}, productions{productions}, rule_weight{rule_weight}
{
}

Rule::Rule(const std::string name, ProductionList productions,
           std::function<ActionPayload(std::vector<std::string>)> generator, int rule_weight)
    : rule_name{name}, productions{productions}, payload_generator{generator}, rule_weight{rule_weight}
{
}

Rule::Rule(const Rule &prev)
    : rule_name{prev.rule_name}, productions{prev.productions}, payload_generator{prev.payload_generator},
      rule_weight{prev.rule_weight}
{
}

std::string Rule::get_rule_name() const
{
    return rule_name;
}

void Rule::set_rule_name(std::string rule_name)
{
    this->rule_name = rule_name;
}

ProductionList Rule::get_productions() const
{
    return productions;
}

void Rule::add_production(Production &production)
{
    productions.push_back(production);
}

std::function<ActionPayload(std::vector<std::string>)> Rule::get_payload_generator()
{
    return this->payload_generator;
}

void Rule::set_payload_generator(std::function<ActionPayload(std::vector<std::string>)> generator)
{
    payload_generator = generator;
}

Rule::PlayerCommand Rule::generate_command(std::vector<std::string> input)
{
    auto func = get_payload_generator();
    ActionPayload payload = func(input);
    return PlayerCommand{rule_name, payload};
}

void Rule::set_rule_weight(int rule_weight)
{
    this->rule_weight = rule_weight;
}

int Rule::get_rule_weight() const
{
    return this->rule_weight;
}
