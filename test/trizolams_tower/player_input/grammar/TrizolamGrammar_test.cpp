#include "bestinshow/engine/grammar/EarleyParser.h"
#include "trizolams_tower/player_input/grammar/TrizolamGrammar.h"
#include <catch/catch.hpp>
#include <memory>
#include <string>
#include <vector>

TEST_CASE("TrizolamGrammar Instance Properties")
{
    REQUIRE(TrizolamGrammar::get_instance().get_name() == "trizolam-grammar");
    REQUIRE(TrizolamGrammar::get_instance().get_first_rule_name() == "input");
}

TEST_CASE("Command Tests")
{
    Grammar &grammar = TrizolamGrammar::get_instance();

    SECTION("PlaceObjectCommand")
    {
        std::vector<std::string> s_complete_opts_included = {"put", "the", "knife", "on", "the", "table"};
        auto complete_opts_included = EarleyParser::build_items(grammar, s_complete_opts_included);

        std::vector<std::string> s_complete_opts_not_included = {"drop", "coin", "in", "slot"};
        auto complete_opts_not_included = EarleyParser::build_items(grammar, s_complete_opts_not_included);

        std::vector<std::string> s_incomplete = {"lay", "table"};
        auto incomplete = EarleyParser::build_items(grammar, s_incomplete);

        REQUIRE(EarleyParser::diagnose(*complete_opts_included, grammar, s_complete_opts_included) ==
                RECOGNITION_STATUS::COMPLETE);

        REQUIRE(EarleyParser::diagnose(*complete_opts_not_included, grammar, s_complete_opts_not_included) ==
                RECOGNITION_STATUS::COMPLETE);

        REQUIRE(EarleyParser::diagnose(*incomplete, grammar, s_incomplete) == RECOGNITION_STATUS::INCOMPLETE);
    }

    SECTION("RemoveFromInventoryCommand")
    {
        std::vector<std::string> s_complete_opt_included = {"drop", "the", "hempen", "rope"};
        auto complete_opt_included = EarleyParser::build_items(grammar, s_complete_opt_included);

        std::vector<std::string> s_complete_opt_not_included = {"toss", "body"};
        auto complete_opt_not_include = EarleyParser::build_items(grammar, s_complete_opt_not_included);

        // TODO: How do we handle incompletes that are grammatically correct
        // std::vector<std::string> s_incomplete = {"drop", "the"};
        // auto incomplete = EarleyParser::build_items(grammar, s_incomplete);

        // REQUIRE(EarleyParser::diagnose(*complete_opt_included, grammar, s_complete_opt_included) ==
        //         RECOGNITION_STATUS::INCOMPLETE);

        // REQUIRE(EarleyParser::diagnose(*incomplete, grammar, s_incomplete) == RECOGNITION_STATUS::INCOMPLETE);
    }

    SECTION("PutInInventoryCommand")
    {
        std::vector<std::string> s_complete_opt_include = {"pick", "up", "body"};
        auto complete_opt_included = EarleyParser::build_items(grammar, s_complete_opt_include);

        std::vector<std::string> s_complete_opt_not_included = {"take", "pencil"};
        auto complete_opt_not_included = EarleyParser::build_items(grammar, s_complete_opt_not_included);
        // TODO: See handler for incompletes that are grammatically correct

        REQUIRE(EarleyParser::diagnose(*complete_opt_included, grammar, s_complete_opt_not_included) ==
                RECOGNITION_STATUS::COMPLETE);
        REQUIRE(EarleyParser::diagnose(*complete_opt_not_included, grammar, s_complete_opt_not_included) ==
                RECOGNITION_STATUS::COMPLETE);
    }

    SECTION("LogCommand")
    {
        std::vector<std::string> s_complete_full = {"show", "log"};
        auto complete_full = EarleyParser::build_items(grammar, s_complete_full);

        std::vector<std::string> s_complete_slim = {"log"};
        auto complete_slim = EarleyParser::build_items(grammar, s_complete_slim);

        std::vector<std::string> s_incomplete = {"show"};
        auto incomplete = EarleyParser::build_items(grammar, s_incomplete);

        REQUIRE(EarleyParser::diagnose(*complete_full, grammar, s_complete_full) == RECOGNITION_STATUS::COMPLETE);
        REQUIRE(EarleyParser::diagnose(*complete_slim, grammar, s_complete_slim) == RECOGNITION_STATUS::COMPLETE);
        REQUIRE(EarleyParser::diagnose(*incomplete, grammar, s_incomplete) == RECOGNITION_STATUS::INCOMPLETE);
    }

    SECTION("ResetCommand")
    {
        std::vector<std::string> s_complete_full = {"reset", "game"};
        auto complete_full = EarleyParser::build_items(grammar, s_complete_full);

        std::vector<std::string> s_complete_slim = {"reset"};
        auto complete_slim = EarleyParser::build_items(grammar, s_complete_slim);

        std::vector<std::string> s_incomplete = {"game"};
        auto incomplete = EarleyParser::build_items(grammar, s_incomplete);

        REQUIRE(EarleyParser::diagnose(*complete_full, grammar, s_complete_full) == RECOGNITION_STATUS::COMPLETE);
        REQUIRE(EarleyParser::diagnose(*complete_slim, grammar, s_complete_slim) == RECOGNITION_STATUS::COMPLETE);
        REQUIRE(EarleyParser::diagnose(*incomplete, grammar, s_incomplete) == RECOGNITION_STATUS::INCOMPLETE);
    }

    SECTION("LoadCommand")
    {
        std::vector<std::string> s_complete_full = {"load", "game"};
        auto complete_full = EarleyParser::build_items(grammar, s_complete_full);

        std::vector<std::string> s_complete_slim = {"load"};
        auto complete_slim = EarleyParser::build_items(grammar, s_complete_slim);

        REQUIRE(EarleyParser::diagnose(*complete_full, grammar, s_complete_full) == RECOGNITION_STATUS::COMPLETE);
        REQUIRE(EarleyParser::diagnose(*complete_slim, grammar, s_complete_slim) == RECOGNITION_STATUS::COMPLETE);
    }

    SECTION("SaveCommand")
    {
        std::vector<std::string> s_complete_full = {"save", "game"};
        auto complete_full = EarleyParser::build_items(grammar, s_complete_full);

        std::vector<std::string> s_complete_slim = {"save"};
        auto complete_slim = EarleyParser::build_items(grammar, s_complete_slim);

        REQUIRE(EarleyParser::diagnose(*complete_full, grammar, s_complete_full) == RECOGNITION_STATUS::COMPLETE);
        REQUIRE(EarleyParser::diagnose(*complete_slim, grammar, s_complete_slim) == RECOGNITION_STATUS::COMPLETE);
    }

    SECTION("MovementCommand & Direction")
    {
        std::vector<std::string> s_complete_full = {"go", "north"};
        auto complete_full = EarleyParser::build_items(grammar, s_complete_full);

        std::vector<std::string> s_complete_slim = {"go", "s"};
        auto complete_slim = EarleyParser::build_items(grammar, s_complete_slim);

        std::vector<std::string> s_direction_only = {"w"};
        auto direction_only = EarleyParser::build_items(grammar, s_direction_only);

        REQUIRE(EarleyParser::diagnose(*complete_full, grammar, s_complete_full) == RECOGNITION_STATUS::COMPLETE);
        REQUIRE(EarleyParser::diagnose(*complete_slim, grammar, s_complete_slim) == RECOGNITION_STATUS::COMPLETE);
        REQUIRE(EarleyParser::diagnose(*direction_only, grammar, s_direction_only) == RECOGNITION_STATUS::COMPLETE);
    }
}