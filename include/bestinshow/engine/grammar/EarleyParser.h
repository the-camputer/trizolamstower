#pragma once
#include "Grammar.h"
#include "EarleyItem.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <memory>

#define stringify( name ) # name
enum RECOGNITION_STATUS { 
    COMPLETE = 0, // Wholely valid input
    INCOMPLETE, // parsed wholely, but no partial success found at end of parse table
    PARTIAL_FAILURE, // parsing stopped part of the way through
    FAILURE // No partial successes found in parse table
};

inline const char* RECOGNITION_STATUS_NAMES[] =
{
    stringify(RECOGNITION_STATUS::COMPLETE),
    stringify(RECOGNITION_STATUS::INCOMPLETE),
    stringify(RECOGNITION_STATUS::PARTIAL_FAILURE),
    stringify(RECOGNITION_STATUS::FAILURE)
};

class EarleyParser {
    public:
        static std::unique_ptr<ParseTable> build_items(Grammar grammar, std::string input);

        /**
         * @brief Analyzes the given parse table for validity of input against the grammar
         * 
         * @param parse_table The ParseTable generated by the given input
         * @param grammar The Grammar used to parse the given input
         * @param input 
         * @return RECOGNITION_STATUS Synbolizes the state of the ParseTable in regard to validity
         */
        static RECOGNITION_STATUS diagnose(ParseTable parse_table, Grammar grammar, std::string input);
    private:
        static void complete(ParseTable& parse_table, int input_pos, int state_set_pos, Grammar grammar);
        static void scan(ParseTable& parse_table, int input_pos, int state_set_pos, Symbol symbol, std::string input);
        static void predict(ParseTable& parse_table, int input_pos, Symbol symbol, Grammar grammar);

        /**
         * @brief Checks to see if there exists a partial parse in the given ParseTable
         * 
         * @param[in] parse_table The parse table to check through for a successful partial parse
         * @param[in] input_pos at what point in the ParseTable to begin checking
         * @param[in] grammar source for rules to evaluate against the ParseTable 
         * @return true if ParseTable contains a partial parse at the given position
         * @return false if ParseTable does not contain a partial parse at the given position
         */
        static bool has_partial_parse(ParseTable parse_table, int input_pos, Grammar grammar);

        /**
         * @brief Checks to see if the ParseTable represenets a completed parse, i.e. that the associated input is valid
         * 
         * @param[in] parse_table The ParseTable that respresents a parsed input
         * @param[in] grammar The Grammar against which the input was parsed
         * @return true If the ParseTable represents a valid input
         * @return false If the ParseTable does not represent a valid input
         */
        static bool has_complete_parse(ParseTable parse_table, Grammar grammar);

        /**
         * @brief Retrieves the position for the last known partial parse from the given ParseTable
         * 
         * @param parse_table The ParseTable to search through
         * @param grammar The Grammar the ParseTable was built against
         * @return position in the ParseTable where the last partial parse exists, or -1 if none exists
         */
        static int last_partial_parse(ParseTable parse_table, Grammar grammar);

        /**
         * @brief Adds EarleyItem to the StateSet if item does not already exist in the set
         * 
         * @param set The StateSet to add the EarleyItem to
         * @param item The item to potentiallly add to the StateSet
         */
        static void add_to_set(StateSet& set, EarleyItem item);

        /**
         * @brief Retrieves the symbol next in line for the EarleyItem, i.e. what's 'right' of the dot
         * 
         * @param grammar 
         * @param item 
         * @return Symbol 
         */
        static inline Symbol next_symbol(Grammar grammar, EarleyItem item) {
            try {
                return grammar[item.rule][item.production].at(item.next);
            } catch(std::out_of_range& ignore) {
                return { "", SYMBOL_TYPE::EMPTY };
            }
        }

        /**
         * @brief Gets the name of the rule associated with the given EarleyItem
         * 
         * @param grammar
         * @param item
         * @return std::string Name of the associated rule
         */
        static inline std::string name(Grammar grammar, EarleyItem item) {
            return grammar[item.rule].get_rule_name();
        }
};