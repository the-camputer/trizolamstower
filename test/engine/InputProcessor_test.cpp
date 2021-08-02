#include "bestinshow/engine/InputProcessor.h"
#include "bestinshow/engine/grammar/Grammar.h"
#include <catch2/catch.hpp>
#include <memory>
#include <string>
#include <vector>

TEST_CASE("Input Processing")
{
    const std::function<ActionPayload(std::vector<std::string>)> custom_payload_generator =
        [](std::vector<std::string> player_inpit)
    {
        return ActionPayload{{"test", "passed"}, {"dev", "happy"}};
    };

    Grammar test_grammar = Grammar{
        "test-grammar",
        {
            std::make_shared<Rule>(new Rule{"input",
                                            {
                                                {{"test-command", SYMBOL_TYPE::NONTERMINAL}},
                                                {{"test-with-custom-generator-command", SYMBOL_TYPE::NONTERMINAL}},
                                            },
                                            -1}),
            std::make_shared<Rule>(new Rule{"test-command",
                                            {
                                                {{"test", SYMBOL_TYPE::TERMINAL},
                                                 {"this", SYMBOL_TYPE::TERMINAL}},
                                            },
                                            1}),
            std::make_shared<Rule>(new Rule{"test-with-custom-generator-command",
                                            {
                                                {{"try", SYMBOL_TYPE::TERMINAL},
                                                 {"this", SYMBOL_TYPE::TERMINAL},
                                                 {"on", SYMBOL_TYPE::TERMINAL},
                                                 {"for", SYMBOL_TYPE::TERMINAL},
                                                 {"size", SYMBOL_TYPE::TERMINAL}},
                                            },
                                            custom_payload_generator,
                                            1}),
        }};
    InputProcessor processor{test_grammar};

    REQUIRE(processor.get_grammar().get_name() == "test-grammar");

    SECTION("Processing complete commands")
    {
        std::string s_complete = "test this";

        auto processed = processor.process(s_complete);

        REQUIRE(processed.type == "test-command");
    }

    SECTION("Processing incomplete commands")
    {
        std::string s_incomplete = "test";

        auto processed = processor.process(s_incomplete);

        REQUIRE(processed.type == "ERROR");
        REQUIRE(processed.payload["type"] == "INCOMPLETE");
    }

    SECTION("Processing with custom payload generators")
    {
        std::string s_complete = "try this on for size";
        auto processed = processor.process(s_complete);

        REQUIRE(processed.type == "test-with-custom-generator-command");
        REQUIRE(processed.payload["test"] == "passed");
        REQUIRE(processed.payload["dev"] == "happy");
    }
}