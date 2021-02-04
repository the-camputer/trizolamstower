#include <iostream>
#include <string>
#include <memory>
#include "bestinshow/engine/grammar/ExampleGrammar.h"
#include "bestinshow/engine/grammar/EarleyParser.h"
#include "bestinshow/engine/grammar/EarleyItem.h"

int main() {
    ExampleGrammar grammar{};
    std::cout << grammar.get_grammar() << std::endl;

    std::string sample_input = "1+(2*3+4)";

    std::cout << "parsing the following input: " << sample_input << std::endl;

    std::unique_ptr<ParseTable> sample_parse_table = EarleyParser::build_items(grammar.get_grammar(), sample_input);

    try {
        RECOGNITION_STATUS result = EarleyParser::diagnose(*sample_parse_table, grammar.get_grammar(), sample_input);
        std::cout << "Result is " << RECOGNITION_STATUS_NAMES[result] << std::endl;
    } catch(std::domain_error& e) {
        std::cout << "Unable to parse: " << e.what() << std::endl;
    } catch(std::length_error& e) {
        std::cout << "Input is empty" << std::endl;
    } catch(std::exception& e) {
        std::cout << "didn't expect this: " << e.what() << std::endl;
    }
}