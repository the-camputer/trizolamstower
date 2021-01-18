#include "bestinshow/engine/grammar/EarleyParser.h"
#include "bestinshow/engine/grammar/EarleyItem.h"
#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include "bestinshow/engine/grammar/Symbol.h"
#include <string>
#include <regex>
#include <memory>

bool EarleyParser::has_partial_parse(ParseTable parse_table, int input_pos, Grammar grammar) {
    /*
     * 1) Grabs the StateSet from the ParseTable at the given input position
     * 2) check every EarleyItem in the set
     * 3)   Find the associated rule and production in the grammar
     * 4)   partial parse exists if:
     *         associated rule is first rule in the grammar
     *         'dot' in the Earley Item is after the end of the production (fully scanned)
     *         starting position of the Earley Item is starting poisition of the ParseTable
     */ 
    StateSet set = parse_table[input_pos];
    for(EarleyItem item : set) {
        Rule rule = grammar[item.rule];
        Production production = (*rule.get_productions())[item.production];
        if (rule.get_rule_name() == grammar.get_first_rule_name() &&
            item.next > production.size() &&
            item.start == 0) {
                return true;
            }
    }

    return false;
}

bool EarleyParser::has_complete_parse(ParseTable parse_table, Grammar grammar) {
    // If a partial parse exists at the end of the parse table, then there exists a complete parse
    return has_partial_parse(parse_table, parse_table.size(), grammar);
}

int EarleyParser::last_partial_parse(ParseTable parse_table, Grammar grammar) {
    for (size_t i = parse_table.size() - 1; i > 0; i--) {
        if (has_partial_parse(parse_table, i, grammar)) {
            return i;
        }
    }

    return -1;
}

RECOGNITION_STATUS EarleyParser::diagnose(ParseTable parse_table, Grammar grammar, std::string input) {
    if (has_complete_parse(parse_table, grammar)) {
        return RECOGNITION_STATUS::COMPLETE;
    } else {
        if (parse_table.size() >= input.size()) {
            return RECOGNITION_STATUS::INCOMPLETE;
        }

        int lpp = last_partial_parse(parse_table, grammar);
        if (lpp != -1) {
            return RECOGNITION_STATUS::PARTIAL_FAILURE;
        } else {
            return RECOGNITION_STATUS::FAILURE;
        }
    }
}

void EarleyParser::add_to_set(StateSet& set, EarleyItem item) {
    for(EarleyItem in_set : set) {
        if (item == in_set) {
            return;
        }
    }

    set.push_back(item);
}

void EarleyParser::complete(ParseTable& parse_table, int input_pos, int state_set_pos, Grammar grammar) {
    EarleyItem item = parse_table[input_pos][state_set_pos];
    for(EarleyItem old_item : parse_table[item.start]) {
        if(next_symbol(grammar, old_item).pattern == name(grammar, item)) {
            add_to_set(parse_table[input_pos], { old_item.rule, old_item.production, old_item.start, old_item.next+1 });
        }
    }
}

void EarleyParser::scan(ParseTable& parse_table, int input_pos, int state_set_pos, Symbol symbol, std::string input) {
    EarleyItem item = parse_table[input_pos][state_set_pos];
    if (std::regex_match(input.substr(input_pos, 1), std::regex(symbol.pattern))) {
        if (parse_table.size() == input_pos + 1) {
            parse_table.push_back({});
        }

        parse_table[input_pos+1].push_back({ item.rule, item.production, item.start, item.next + 1 });
    }
}

void EarleyParser::predict(ParseTable& parse_table, int input_pos, Symbol symbol, Grammar grammar) {
    RuleList rules = grammar.get_rules();
    for(size_t i = 0; i < rules.size(); i++) {
        if (rules[i].get_rule_name() == symbol.pattern) {
            add_to_set(parse_table[input_pos], { i, 0, input_pos, 0 });
        }
    }
}

std::unique_ptr<ParseTable> EarleyParser::build_items(Grammar grammar, std::string input) {
    std::unique_ptr<ParseTable> parse_table = std::make_unique<ParseTable>(new ParseTable{});

    parse_table->push_back({});
    RuleList rules = grammar.get_rules();
    Rule first_rule = grammar[0];
    ProductionList *first_rule_productions = first_rule.get_productions();
    for(size_t i = 0; i < first_rule_productions->size(); i++) {
        parse_table->at(0).push_back({ 0, i, 0, 0 });
    }

    
}