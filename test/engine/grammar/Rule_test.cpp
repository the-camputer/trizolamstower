#include <catch2/catch.hpp>
#include <string>
#include <ostream>
#include "bestinshow/engine/grammar/Rule.h"

TEST_CASE("Rule Creation") {
    Rule test_rule { "test-rule" };

    REQUIRE(test_rule.get_rule_name() == "test-rule");
}

TEST_CASE("Printing") {
    std::ostringstream os{};

    SECTION("empty productions prints just the name in BNF format") {
        Rule test_rule{ "test-rule" };
        os << test_rule;
        REQUIRE(os.str() == "<test-rule> ::= \n");
    }

    os.clear();

    SECTION("Nonterminals are printed out in angled brackets") {
        Rule test_rule{ "test-rule" };
        Production *new_production = new Production();
        Symbol new_nonterminal {nonterminal: "linked-rule"};
        new_production->push_back(new_nonterminal);
        test_rule.add_production(*new_production);

        os << test_rule;

        REQUIRE(os.str() == "<test-rule> ::= <linked-rule>\n");
    }

    os.clear();

    SECTION("Terminals are printed as their regex patters") {
        Rule test_rule{ "test-rule" };
        Production *new_production = new Production();
        std::string terminal_regex_pattern = "[a-zA-Z0-9]";
        std::regex *reg = new std::regex(terminal_regex_pattern);
        Symbol new_terminal {
            nonterminal: "",
            terminal_pattern: terminal_regex_pattern, 
            terminal: reg
        };

        new_production->push_back(new_terminal);
        test_rule.add_production(*new_production);

        os << test_rule;

        REQUIRE(os.str() == "<test-rule> ::= \"[a-zA-Z0-9]\" \n");

        delete reg;
    }

    os.clear();
}