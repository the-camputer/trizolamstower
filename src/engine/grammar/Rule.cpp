#include "bestinshow/engine/grammar/Rule.h"
#include "bestinshow/engine/grammar/Symbol.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <string>
#include <vector>

Rule::Rule(const std::string name) : rule_name{name}
{
}

Rule::Rule(const std::string name, ProductionList productions) : rule_name{name}, productions{productions}
{
}

Rule::Rule(const std::string name, ProductionList productions,
           std::function<ActionPayload(std::vector<std::string>)> generator)
    : rule_name{name}, productions{productions}, payload_generator{generator}
{
}

Rule::Rule(const Rule &prev) : rule_name{prev.rule_name}
{
    this->productions = prev.productions;
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
void Rule::set_payload_generator(ActionPayload generator(std::vector<std::string>))
{
    payload_generator = generator;
}