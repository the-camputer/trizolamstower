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
        // std::cout << " CONNECTIONS: " << scene["Connections"]["North"].as<std::string>() << std::endl;
        std::unordered_map<MOVEMENT_DIRECTION, SceneManager::SceneConnection> scene_connections{};

        for (auto conn = scene["Connections"].begin(); conn != scene["Connections"].end(); conn++)
        {
            auto direction_name = conn->first.as<std::string>();
            SceneManager::SceneConnection null_conn_obj = SceneConnection{};
            if (conn->second["Name"].as<std::string>() != "null")
            {
                auto next_scene_name = conn->second["Name"].as<std::string>();
                auto blocked_status = conn->second["Blocked"].as<bool>();
                auto blocked_reason = blocked_status ? conn->second["Reason"].as<std::string>() : "";

                SceneManager::SceneConnection conn_obj = {next_scene_name, blocked_status, blocked_reason};

                if (direction_name == "North")
                {
                    scene_connections[MOVEMENT_DIRECTION::NORTH] = conn_obj;
                }
                else if (direction_name == "East")
                {
                    scene_connections[MOVEMENT_DIRECTION::EAST] = conn_obj;
                }
                else if (direction_name == "South")
                {
                    scene_connections[MOVEMENT_DIRECTION::SOUTH] = conn_obj;
                }
                else if (direction_name == "WEST")
                {
                    scene_connections[MOVEMENT_DIRECTION::WEST] = conn_obj;
                }
            }
            else
            {
                if (direction_name == "North")
                {
                    scene_connections[MOVEMENT_DIRECTION::NORTH] = null_conn_obj;
                }
                else if (direction_name == "East")
                {
                    scene_connections[MOVEMENT_DIRECTION::EAST] = null_conn_obj;
                }
                else if (direction_name == "South")
                {
                    scene_connections[MOVEMENT_DIRECTION::SOUTH] = null_conn_obj;
                }
                else if (direction_name == "WEST")
                {
                    scene_connections[MOVEMENT_DIRECTION::WEST] = null_conn_obj;
                }
            }
        }
        m_scenes[scene_name] = Scene{scene_name, scene_description, scene_connections};
    }

    return first_scene_name;
}

std::string SceneManager::get_scene_description(std::string scene_name)
{
    return m_scenes[scene_name].scene_description;
};

SceneManager::SceneConnection SceneManager::get_next_scene(std::string scene_name, MOVEMENT_DIRECTION direction)
{
    return m_scenes[scene_name].scene_connections[direction];
}