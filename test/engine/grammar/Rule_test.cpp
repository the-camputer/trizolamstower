#include "bestinshow/engine/grammar/Rule.h"
#include <catch2/catch.hpp>
#include <ostream>
#include <string>

TEST_CASE("Rule Creation")
{
    Rule test_rule{"test-rule"};

    REQUIRE(test_rule.get_rule_name() == "test-rule");
}

TEST_CASE("Rule Printing")
{
    std::ostringstream os{};

    SECTION("empty productions prints just the name in BNF format with weight")
    {
        Rule test_rule{"test-rule"};
        os << test_rule;
        REQUIRE(os.str() == "(0) <test-rule> ::= \n");
    }

    os.clear();

    SECTION("Nonterminals are printed out in angled brackets")
    {
        Rule test_rule{"test-rule", {{{"linked-rule", SYMBOL_TYPE::NONTERMINAL}}}};
        // Production *new_production = new Production();
        // Symbol new_nonterminal {nonterminal: "linked-rule"};
        // new_production->push_back(new_nonterminal);
        // test_rule.add_production(*new_production);

        os << test_rule;

        REQUIRE(os.str() == "(0) <test-rule> ::= <linked-rule>\n");
    }

    os.clear();

    SECTION("Terminals are printed as their regex patters")
    {
        Rule test_rule{"test-rule"};
        Production *new_production = new Production();
        std::string terminal_regex_pattern = "[a-zA-Z0-9]";
        Symbol new_terminal{"[a-zA-Z0-9]", SYMBOL_TYPE::TERMINAL};

        new_production->push_back(new_terminal);
        test_rule.add_production(*new_production);

        os << test_rule;

        REQUIRE(os.str() == "(0) <test-rule> ::= [a-zA-Z0-9]\n");
    }

    os.clear();

    SECTION("Production lists are separated by pipes")
    {
        Rule test_rule{"test-rule"};
        Production *recursive_digits = new Production();
        Production *straight_digit = new Production();
        Symbol digit_nonterminal{"digit", SYMBOL_TYPE::NONTERMINAL};
        Symbol test_rule_nonterminal{"test-rule", SYMBOL_TYPE::NONTERMINAL};

        recursive_digits->push_back(digit_nonterminal);
        recursive_digits->push_back(test_rule_nonterminal);
        test_rule.add_production(*recursive_digits);
        straight_digit->push_back(digit_nonterminal);
        test_rule.add_production(*straight_digit);

        os << test_rule;

        REQUIRE(os.str() == "(0) <test-rule> ::= <digit><test-rule>|<digit>\n");
    }

    os.clear();
}