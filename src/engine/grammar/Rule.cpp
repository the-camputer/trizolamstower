#include <bestinshow/engine/grammar/Rule.h>
#include <bestinshow/engine/grammar/Symbol.h>
#include <vector>
#include <string>


Rule::Rule() 
{
    productions = new ProductionList{};
}

Rule::Rule(const std::string name)
: rule_name { name } 
{
    productions = new ProductionList{};
}

Rule::Rule(const std::string name, ProductionList *productions)
: rule_name { name }
{
    this->productions = new ProductionList{};
    *(this->productions) = *productions;
}

Rule::Rule(const Rule& prev)
: rule_name { prev.rule_name }
{
    this->productions = new ProductionList{};
    *(this->productions) = *prev.productions;
}

Rule::~Rule()
{
    for (auto p = (*productions).begin(); p != (*productions).end(); p++)
    {
        delete *p;
    }

    delete productions;
}

std::string Rule::get_rule_name() const
{
    return rule_name;
}

void Rule::set_rule_name(std::string rule_name)
{
    this->rule_name = rule_name;
}

std::vector<Production*>* Rule::get_productions() const
{
    return this->productions;
}

void Rule::add_production(Production& production)
{
    if (!productions) {
        this->productions = new ProductionList{ &production };
    } else {
        this->productions->push_back(&production);
    }
}

std::ostream& operator<<(std::ostream& os, const Rule& v) 
{
    os << "<" << v.get_rule_name() << "> ::= ";

    auto production_list = v.get_productions();
    if (production_list) {
        for(auto p = (*production_list).begin(); p != (*production_list).end(); p++) {
            auto production = **p;
            std::for_each(production.begin(), production.end(), [&os] (Symbol s){
                if (s.terminal) {
                    os << "\"" << s.terminal_pattern << "\" ";
                } else {
                    os << "<" << s.nonterminal << ">";
                }
            });

            if (p != (*production_list).end() - 1) {
                os << " | ";
            }
        }
    }

    os << std::endl;

    return os;
}