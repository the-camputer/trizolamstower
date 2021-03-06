#include "bestinshow/engine/grammar/ExampleGrammar.h"
#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include "bestinshow/engine/grammar/Symbol.h"
#include <string>

ExampleGrammar::ExampleGrammar() : grammar{Grammar{"exmaple-grammar"}}
{
    /** implements simple grammar of the form
     * <exmaple-grammar> ::= <sum>
     * <sum> ::= <sum> [+-] <product>|<product>
     * <product> ::= <product> [/*] <factor> |<factor>
     * <factor> ::= ( <sum> )|<number>
     * <number> ::= [0-9] <number>|[0-9]
     */
    Rule number_rule{
        "number",
        {{{"[0-9]", SYMBOL_TYPE::TERMINAL}, {"number", SYMBOL_TYPE::NONTERMINAL}}, {{"[0-9]", SYMBOL_TYPE::TERMINAL}}}};

    Rule factor_rule{
        "factor",
        {{{"\\(", SYMBOL_TYPE::TERMINAL}, {"sum", SYMBOL_TYPE::NONTERMINAL}, {"\\)", SYMBOL_TYPE::TERMINAL}},
         {{"number", SYMBOL_TYPE::NONTERMINAL}}}};

    Rule product_rule{
        "product",
        {{{"product", SYMBOL_TYPE::NONTERMINAL}, {"[*/]", SYMBOL_TYPE::TERMINAL}, {"factor", SYMBOL_TYPE::NONTERMINAL}},
         {{"factor", SYMBOL_TYPE::NONTERMINAL}}}};

    Rule sum_rule{
        "sum",
        {{{"sum", SYMBOL_TYPE::NONTERMINAL}, {"[+-]", SYMBOL_TYPE::TERMINAL}, {"product", SYMBOL_TYPE::NONTERMINAL}},
         {{"product", SYMBOL_TYPE::NONTERMINAL}}}};

    grammar.add_rule(sum_rule);
    grammar.add_rule(product_rule);
    grammar.add_rule(factor_rule);
    grammar.add_rule(number_rule);
}

Grammar ExampleGrammar::get_grammar()
{
    return grammar;
}