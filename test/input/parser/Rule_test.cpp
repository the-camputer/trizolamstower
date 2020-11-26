#include <catch2/catch.hpp>
#include <string>
#include "bestinshow/input/parser/Rule.h"

TEST_CASE("Rule Creation") {
    Rule test_rule { "test_rule" };

    REQUIRE(test_rule.get_rule_name() == "test_rule");
}