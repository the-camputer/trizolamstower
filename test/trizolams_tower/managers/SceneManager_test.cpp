#include <catch2/catch.hpp>
#include <boost/dll.hpp>
#include <string>
#include <spdlog/spdlog.h>
#include <iostream>

#include "trizolams_tower/managers/SceneManager.h"

const std::string test_scenes_file = "test_resources/TestScene.yml";

TEST_CASE("SceneManager creates node list from file")
{
    std::string program_root = boost::dll::program_location().parent_path().parent_path().c_str();

    std::string test_scene_file_path = program_root + "/" + test_scenes_file;

    spdlog::info("FILE! {}", test_scene_file_path);

    REQUIRE_NOTHROW(SceneManager{test_scene_file_path});
}