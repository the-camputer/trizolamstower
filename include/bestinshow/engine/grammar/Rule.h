#pragma once

#include "Symbol.h"
#include <algorithm>
#include <vector>
#include <string>
#include <ostream>
#include <memory>


using Production = std::vector<Symbol>;
using ProductionList = std::vector<Production>;

class Rule {
    private:
        std::string rule_name = "";
        std::unique_ptr<ProductionList> productions = nullptr;
    public:
        Rule();
        Rule(const std::string name);
        Rule(const std::string name, ProductionList productions);
        Rule(const Rule& prev);
        ~Rule() = default;

        std::string get_rule_name() const;
        void set_rule_name(std::string rule_name);
        ProductionList* get_productions() const;
        void add_production(Production& production);
        friend std::ostream& operator<<(std::ostream& os, const Rule& v);
};