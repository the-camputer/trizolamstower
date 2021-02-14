#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include "bestinshow/engine/grammar/Symbol.h"
#include <string>
#include <ostream>
#include <catch/catch.hpp>

TEST_CASE("Grammar Creation") {
    Grammar test_grammar { "test-grammar" };

    REQUIRE(test_grammar.get_name() == "test-grammar");

    test_grammar.set_first_rule_name("test-rule");

    REQUIRE(test_grammar.get_first_rule_name() == "test-rule");
}

TEST_CASE("Grammar Printing") {
    std::ostringstream os{};

    SECTION("Empty rule set prints just the grammar name as an initial rule") {
        Grammar test_grammar { "test-grammar" };

        os << test_grammar;

        REQUIRE(os.str() == "<test-grammar> ::= \n");
    }

    os.clear();

    SECTION("Nonempty rule set prints out all Symbols and Rules for the grammer") {
        using namespace std::string_literals;
        Grammar test_grammar { "test-grammar" }; 

        Rule test_rule{ "test-rule" };
        Production recursive_digits{};
        Production straight_digit{};
        Symbol test_rule_nonterminal {
            "test-rule", SYMBOL_TYPE::NONTERMINAL
        };
        Symbol digit_nonterminal {
            "digit", SYMBOL_TYPE::NONTERMINAL
        };

        recursive_digits.push_back(digit_nonterminal);
        recursive_digits.push_back(test_rule_nonterminal);
        test_rule.add_production(recursive_digits);
        straight_digit.push_back(digit_nonterminal);
        test_rule.add_production(straight_digit);

        Rule digit_rule{ "digit" };
        Production digit_production{};
        std::string terminal_regex_pattern = "[0-9]";
        Symbol digit_terminal {
            "[0-9]", SYMBOL_TYPE::TERMINAL
        };
        digit_production.push_back(digit_terminal);
        digit_rule.add_production(digit_production);

        test_grammar.add_rule(test_rule);
        test_grammar.add_rule(digit_rule);

        os << test_grammar;

        REQUIRE(os.str() == "<test-grammar> ::= <test-rule>\n<test-rule> ::= <digit><test-rule>|<digit>\n<digit> ::= [0-9]\n");
    }
}
