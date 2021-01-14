#include "bestinshow/engine/grammar/TestGrammar.h"
#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include "bestinshow/engine/grammar/Symbol.h"
#include <string>

TestGrammar::TestGrammar() : grammar { Grammar{"test-grammar"} } 
{
    /* implements simple grammar of the form
    * <test-grammar> ::= <sum>
    * <sum> ::= <sum> [+-] <product>|<product>
    * <product> ::= <product> [/*] <factor> |<factor>
    * <factor> ::= ( <sum> )|<number>
    * <number> ::= [0-9] <number>|[0-9]
    */
    Rule number_rule { "number", {
        { { "[0-9]", SymbolType::TERMINAL }, { "number", SymbolType::NONTERMINAL } },
        { { "[0-9]", SymbolType::TERMINAL } }
    } };
    
    Rule factor_rule { "factor", {
        { { "(", SymbolType::TERMINAL }, { "sum", SymbolType::NONTERMINAL }, { ")", SymbolType::TERMINAL } },
        { { "number", SymbolType::NONTERMINAL } }
    } };
    
    Rule product_rule { "product", {
        { { "product", SymbolType::NONTERMINAL }, { "[*/]", SymbolType::TERMINAL }, { "factor", SymbolType::NONTERMINAL } },
        { { "factor", SymbolType::NONTERMINAL } }
    } };

    Rule sum_rule { "sum", {
        { { "sum", SymbolType::NONTERMINAL }, { "[+-]", SymbolType::TERMINAL }, { "product", SymbolType::NONTERMINAL} },
        { { "product", SymbolType::NONTERMINAL } }
    } };

    grammar.add_rule(sum_rule);
    grammar.add_rule(product_rule);
    grammar.add_rule(factor_rule);
    grammar.add_rule(number_rule);
}

Grammar TestGrammar::get_grammar() { return grammar; }