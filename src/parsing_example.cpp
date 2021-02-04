#include <iostream>
#include <string>
#include <memory>
#include "bestinshow/engine/grammar/ExampleGrammar.h"
#include "bestinshow/engine/grammar/EarleyParser.h"
#include "bestinshow/engine/grammar/EarleyItem.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

int main(int argc, char *argv[]) {
    spdlog::info("Hello World: {}", argv[2]);
    if (argc == 3 && strcmp(argv[2], "debug") == 0) {
        spdlog::set_level(spdlog::level::debug);
    } else {
        spdlog::set_level(spdlog::level::info);
    }

    ExampleGrammar grammar{};
    spdlog::info("{}", grammar.get_grammar());
    // std::cout << grammar.get_grammar() << std::endl;

    std::string sample_input = argv[1];

    spdlog::info("parsing the following input: {}", sample_input);

    std::unique_ptr<ParseTable> sample_parse_table = EarleyParser::build_items(grammar.get_grammar(), sample_input);

    try {
        RECOGNITION_STATUS result = EarleyParser::diagnose(*sample_parse_table, grammar.get_grammar(), sample_input);
        spdlog::info("Result is {}", RECOGNITION_STATUS_NAMES[result]);
        // std::cout << "Result is " << RECOGNITION_STATUS_NAMES[result] << std::endl;
    } catch(std::domain_error& e) {
        // std::cout << "Unable to parse: " << e.what() << std::endl;
    } catch(std::length_error& e) {
        // std::cout << "Input is empty" << std::endl;
    } catch(std::exception& e) {
        // std::cout << "didn't expect this: " << e.what() << std::endl;
    }
}