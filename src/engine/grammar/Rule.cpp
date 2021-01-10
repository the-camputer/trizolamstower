#include <bestinshow/engine/grammar/Rule.h>
#include <bestinshow/engine/grammar/Symbol.h>
#include <vector>
#include <string>
#include <memory>


Rule::Rule() 
{
    productions = std::make_unique<ProductionList>();
}

Rule::Rule(const std::string name)
: rule_name { name } 
{
    productions = std::make_unique<ProductionList>();
}

Rule::Rule(const std::string name, ProductionList *productions)
: rule_name { name }
{
    this->productions = std::make_unique<ProductionList>(*productions);
}

Rule::Rule(const Rule& prev)
: rule_name { prev.rule_name }
{
    this->productions = std::make_unique<ProductionList>(*prev.productions);
}

std::string Rule::get_rule_name() const
{
    return rule_name;
}

void Rule::set_rule_name(std::string rule_name)
{
    this->rule_name = rule_name;
}

ProductionList* Rule::get_productions() const
{
    return this->productions.get();
}

void Rule::add_production(Production& production)
{
    if (!productions) {
        this->productions = std::make_unique<ProductionList>();
    }

    this->productions->push_back(production);
}

std::ostream& operator<<(std::ostream& os, const Rule& v) 
{
    os << "<" << v.get_rule_name() << "> ::= ";

    auto ref_production_list = v.get_productions();
    if (ref_production_list) {
        auto production_list = *ref_production_list;
        for(Production p : production_list) {
            for(Symbol s : p) {
                os << s;
            }

            if (p != *(production_list.end() - 1)) {
                os << "|";
            }
        }
    }

    os << std::endl;

    return os;
}