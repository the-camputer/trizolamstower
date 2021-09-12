#include "trizolams_tower/managers/SceneManager.h"

#include <fstream>
#include <iostream>
#include <string>

SceneManager::SceneManager(std::string filename)
{
    std::ifstream fin(filename);
    YAML::Parser parser(fin);

    raw_scene_list = YAML::LoadAllFromFile(filename);
};

std::string SceneManager::construct_scenes()
{
    std::string first_scene_name;
    for (const auto &scene : raw_scene_list)
    {
        if (scene["Name"] == raw_scene_list[0]["Name"])
        {
            first_scene_name = scene["Name"].as<std::string>();
        }

        auto scene_name = scene["Name"].as<std::string>();
        auto scene_description = scene["Description"].as<std::string>();
        std::unordered_map<MOVEMENT_DIRECTION, std::string> scene_connections{
            {MOVEMENT_DIRECTION::NORTH, scene["Connections"]["North"].as<std::string>()},
            {MOVEMENT_DIRECTION::EAST, scene["Connections"]["East"].as<std::string>()},
            {MOVEMENT_DIRECTION::SOUTH, scene["Connections"]["South"].as<std::string>()},
            {MOVEMENT_DIRECTION::WEST, scene["Connections"]["West"].as<std::string>()},
        };

        m_scenes[scene_name] = Scene{scene_name, scene_description, scene_connections};
    }

    return first_scene_name;
}

std::string SceneManager::get_scene_description(std::string scene_name)
{
    return m_scenes[scene_name].scene_description;
};

std::string SceneManager::get_next_scene(std::string scene_name, MOVEMENT_DIRECTION direction)
{
    auto current_scene = m_scenes[scene_name];
    std::string next_scene_name;

    next_scene_name = current_scene.scene_connections[direction];

    return next_scene_name;
}