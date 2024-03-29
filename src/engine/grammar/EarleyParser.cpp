#include "bestinshow/engine/grammar/EarleyParser.h"
#include "bestinshow/engine/grammar/EarleyItem.h"
#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include "bestinshow/engine/grammar/Symbol.h"
#include <algorithm>
#include <cctype>
#include <exception>
#include <iostream>
#include <memory>
#include <regex>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

Symbol EarleyParser::next_symbol(Grammar grammar, EarleyItem item)
{
    try
    {
        Symbol result = grammar[item.rule][item.production].at(item.next);
        return result;
    }
    catch (std::out_of_range &ignore)
    {
        return {"", SYMBOL_TYPE::EMPTY};
    }
}

bool EarleyParser::has_partial_parse(ParseTable parse_table, int input_pos, Grammar grammar)
{
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
    for (EarleyItem item : set)
    {
        Rule rule = grammar[item.rule];
        Production production = rule.get_productions().at(item.production);
        if (rule.get_rule_name() == grammar.get_first_rule_name() && (size_t)item.next >= production.size() &&
            item.start == 0)
        {
            return true;
        }
    }

    return false;
}

bool EarleyParser::has_complete_parse(ParseTable parse_table, Grammar grammar)
{
    // If a partial parse exists at the end of the parse table, then there exists a complete parse
    return has_partial_parse(parse_table, parse_table.size() - 1, grammar);
}

int EarleyParser::last_partial_parse(ParseTable parse_table, Grammar grammar)
{
    for (size_t i = parse_table.size() - 1; i > 0; i--)
    {
        if (has_partial_parse(parse_table, i, grammar))
        {
            return i;
        }
    }

    return -1;
}

RECOGNITION_STATUS EarleyParser::diagnose(ParseTable parse_table, Grammar grammar, std::vector<std::string> input)
{
    if (has_complete_parse(parse_table, grammar))
    {
        return RECOGNITION_STATUS::COMPLETE;
    }
    else
    {
        if (parse_table.size() >= input.size())
        {
            return RECOGNITION_STATUS::INCOMPLETE;
        }

        int lpp = last_partial_parse(parse_table, grammar);
        if (lpp != -1)
        {
            return RECOGNITION_STATUS::PARTIAL_FAILURE;
        }
        else
        {
            return RECOGNITION_STATUS::FAILURE;
        }
    }
}

void EarleyParser::add_to_set(StateSet &set, EarleyItem item, Grammar grammar)
{
    for (EarleyItem in_set : set)
    {
        if (item == in_set)
        {
            return;
        }
    }

    spdlog::debug("ADDING {} ({}) TO STATE SET", item, grammar[item.rule].get_rule_name());
    set.push_back(item);
}

void EarleyParser::complete(ParseTable &parse_table, int input_pos, int state_set_pos, Grammar grammar)
{
    EarleyItem item = parse_table[input_pos][state_set_pos];
    for (EarleyItem old_item : parse_table[item.start])
    {
        if (next_symbol(grammar, old_item).pattern == name(grammar, item))
        {
            add_to_set(parse_table[input_pos], {old_item.rule, old_item.production, old_item.start, old_item.next + 1},
                       grammar);
        }
    }
}

void EarleyParser::scan(ParseTable &parse_table, int input_pos, int state_set_pos, Symbol symbol,
                        std::vector<std::string> &input)
{
    EarleyItem item = parse_table[input_pos][state_set_pos];
    bool should_scan = (size_t)item.start <= input.size() - 1 && (size_t)input_pos <= input.size() - 1;
    if (should_scan)
    {
        if (!symbol.pattern.empty())
        {
            spdlog::debug("SCANNING {} WITH TERMINAL PATTERN {}", input[input_pos], symbol);
            if (std::regex_match(input[input_pos], std::regex(symbol.pattern)))
            {
                spdlog::debug("MATCH FOUND: {}", input[input_pos]);
                if (parse_table.size() == (size_t)(input_pos + 1))
                {
                    parse_table.push_back({});
                }

                parse_table[input_pos + 1].push_back({item.rule, item.production, item.start, item.next + 1});
            }
            else
            {
                spdlog::debug("SCAN FAILED TO MATCH");
            }
        }
        else
        {
            spdlog::debug("EMPTY PATTERN FOUND. ASSUMING OPTIONAL");
            if (parse_table.size() == (size_t)(input_pos + 1))
            {
                parse_table.push_back({});
            }

            parse_table[input_pos].push_back({item.rule, item.production, item.start, item.next + 1});
        }
    }
    else
    {
        spdlog::debug("SCAN DETECTED NEXT EXPECTED SYMBOL PAST END OF INPUT");
    }
}

void EarleyParser::predict(ParseTable &parse_table, int input_pos, Symbol symbol, Grammar grammar)
{
    RuleList rules = grammar.get_rules();
    for (size_t i = 0; i < rules.size(); i++)
    {
        if (rules[i]->get_rule_name() == symbol.pattern)
        {
            for (size_t ii = 0; ii < rules[i]->get_productions().size(); ii++)
            {
                add_to_set(parse_table[input_pos], {(int)i, (int)ii, input_pos, 0}, grammar);
            }
        }
    }
}

std::unique_ptr<ParseTable> EarleyParser::build_items(Grammar grammar, std::vector<std::string> input)
{

    if (input.size() == 0)
    {
        throw std::length_error("input is empty");
    }

    auto parse_table = std::make_unique<ParseTable>();
    parse_table->push_back({});

    RuleList rules = grammar.get_rules();
    Rule first_rule = *rules[0];
    ProductionList first_rule_productions = first_rule.get_productions();
    for (size_t i = 0; i < first_rule_productions.size(); i++)
    {
        parse_table->at(0).push_back({0, (int)i, 0, 0});
    }

    for (size_t i = 0; i < parse_table->size(); i++)
    {
        for (size_t ii = 0; ii < parse_table->at(i).size(); ii++)
        {
            Symbol symbol = next_symbol(grammar, parse_table->at(i).at(ii));
            // spdlog::debug("NEXT SYMBOL IS {}", symbol);
            // std::cout << "NEXT SYMBOL IS " << symbol << std::endl;
            if (symbol.type == SYMBOL_TYPE::EMPTY)
            {
                spdlog::debug("RUNNING COMPLETION FOR {}", parse_table->at(i).at(ii));
                // std::cout << "RUNNING COMPLETE" << std::endl;
                complete(*parse_table, i, ii, grammar);
            }
            else if (symbol.type == SYMBOL_TYPE::TERMINAL)
            {
                spdlog::debug("RUNNING SCAN FOR {}", parse_table->at(i).at(ii));
                // std::cout << "RUNNING SCAN" << std::endl;
                try
                {
                    scan(*parse_table, i, ii, symbol, input);
                }
                catch (std::exception &ignore)
                {
                    return parse_table;
                }
            }
            else if (symbol.type == SYMBOL_TYPE::NONTERMINAL)
            {
                spdlog::debug("RUNNING PREDICT FOR {}", parse_table->at(i).at(ii));
                // std::cout << "RUNNING PREDICT" << std::endl;
                predict(*parse_table, i, symbol, grammar);
            }
            else
            {
                throw std::domain_error("Illegal rule in grammar");
            }
        }

        spdlog::debug("FINAL STATE SET FOR S[{}]", i);
        // std::cout << "STATE SET FOR S[" << i << "] ENDS WITH" << std::endl;
        for (size_t ii = 0; ii < parse_table->at(i).size(); ii++)
        {
            spdlog::debug("{}", parse_table->at(i).at(ii));
            // std::cout << parse_table->at(i).at(ii) << std::endl;
        }
        spdlog::debug("\n");
    }
    return parse_table;
}