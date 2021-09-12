#include <catch2/catch.hpp>
#include <boost/dll.hpp>
#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>

#include "trizolams_tower/managers/SceneManager.h"

const std::string test_scenes_file = "test_resources/TestScene.yml";
const std::string program_root = boost::dll::program_location().parent_path().parent_path().c_str();
const std::string test_scene_file_path = program_root + "/" + test_scenes_file;

TEST_CASE("SceneManager creates scene map without throwing an error")
{
    REQUIRE_NOTHROW(SceneManager{test_scene_file_path});
}

TEST_CASE("SceneManager creates scene map that mirrors configuration file")
{
    SceneManager test_scene_manager{test_scene_file_path};

    SECTION("via scene descriptions")
    {
        REQUIRE(test_scene_manager.get_scene_description("Start") == "Wow look a description\n");
        REQUIRE(test_scene_manager.get_scene_description("Next") == "Oh my goodness another description\n");
    }

    SECTION("via connection retrieval")
    {
        REQUIRE(test_scene_manager.get_next_scene("Start", MOVEMENT_DIRECTION::NORTH) == "Next");
        REQUIRE(test_scene_manager.get_next_scene("Next", MOVEMENT_DIRECTION::SOUTH) == "Start");
        REQUIRE(test_scene_manager.get_next_scene("Start", MOVEMENT_DIRECTION::EAST) == "null");
    }
}