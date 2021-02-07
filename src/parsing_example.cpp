#include <iostream>
#include <string>
#include <memory>
#include "bestinshow/engine/grammar/ExampleGrammar.h"
#include "bestinshow/engine/grammar/EarleyParser.h"
#include "bestinshow/engine/grammar/EarleyItem.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

int main(int argc, char *argv[]) {
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

    try {
        std::unique_ptr<ParseTable> sample_parse_table = EarleyParser::build_items(grammar.get_grammar(), sample_input);
        RECOGNITION_STATUS result = EarleyParser::diagnose(*sample_parse_table, grammar.get_grammar(), sample_input);
        spdlog::info("Result is {}", RECOGNITION_STATUS_NAMES[result]);
    } catch(std::domain_error& e) {
        spdlog::error("Unable to parse: {}", e.what());
        return -2;
    } catch(std::length_error& e) {
        spdlog::warn("Input is empty");
        return -3;
    } catch(std::exception& e) {
        spdlog::error("Encounted unexpected error: {}", e.what());
        return -1;
    }
}