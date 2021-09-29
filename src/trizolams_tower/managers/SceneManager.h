#pragma once

#include <yaml-cpp/yaml.h>
#include "../commands/MovementDirections.h"
#include <unordered_map>
#include <string>

class SceneManager
{

public:
    struct SceneConnection
    {
        std::string next_scene_name;
        bool blocked;
        std::string blocked_reason;
    };

    struct Scene
    {
        std::string scene_name;
        std::string scene_description;
        std::unordered_map<MOVEMENT_DIRECTION, SceneConnection> scene_connections;
    };

    SceneManager(std::string);
    std::string get_scene_description(std::string);
    SceneConnection get_next_scene(std::string, MOVEMENT_DIRECTION);
    std::string construct_scenes();

private:
    std::unordered_map<std::string, SceneManager::Scene> m_scenes;
    std::vector<YAML::Node> raw_scene_list;
};
