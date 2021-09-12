#include <yaml-cpp/yaml.h>
#include "../player_input/commands/MovementDirections.h"
#include <unordered_map>
#include <string>

class SceneManager
{

public:
    struct Scene
    {
        std::string scene_name;
        std::string scene_description;
        std::unordered_map<MOVEMENT_DIRECTION, std::string> scene_connections;
    };

    SceneManager(std::string);
    std::string get_scene_description(std::string);
    std::string get_next_scene(std::string, MOVEMENT_DIRECTION);
    std::string construct_scenes();

private:
    std::unordered_map<std::string, SceneManager::Scene> m_scenes;
    std::vector<YAML::Node> raw_scene_list;
};
