#pragma once

#include "Symbol.h"
#include "spdlog/fmt/ostr.h"
#include <algorithm>
#include <vector>
#include <string>
#include <ostream>
#include <memory>


using Production = std::vector<Symbol>;
using ProductionList = std::vector<Production>;

class Rule {
    protected:
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
        template<typename OStream>
        friend OStream& operator<<(OStream& os, const Rule& v)
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
        
        inline Production& operator[](int i) {
            return (*productions).at(i);
        }
};