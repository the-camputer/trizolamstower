#include "bestinshow/engine/grammar/Grammar.h"
#include "bestinshow/engine/grammar/Rule.h"
#include "bestinshow/engine/grammar/Symbol.h"
#include <string>
#include <ostream>
#include <catch2/catch.hpp>

TEST_CASE("Grammar Creation") {
    Grammar test_grammar { "test-grammar" };

    REQUIRE(test_grammar.get_name() == "test-grammar");

    test_grammar.set_first_rule_name("test-rule");

    REQUIRE(test_grammar.get_first_rule_name() == "test-rule");
}
