#include "TravelCommand.h"
#include "MovementDirections.h"
#include <iostream>
#include <string>

PayloadGenerator TravelCommand::payload_generator = [](std::vector<std::string> player_input)
{
    auto get_direction = [](std::string direction_raw)
    {
        std::transform(direction_raw.begin(), direction_raw.end(), direction_raw.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });
        auto direction = direction_raw.at(0);
        auto result = MOVEMENT_DIRECTION::UNKOWN;
        switch (direction)
        {
        case 'n':
            result = MOVEMENT_DIRECTION::NORTH;
            break;
        case 'e':
            result = MOVEMENT_DIRECTION::EAST;
            break;
        case 's':
            result = MOVEMENT_DIRECTION::SOUTH;
            break;
        case 'w':
            result = MOVEMENT_DIRECTION::WEST;
            break;
        default:
            result = MOVEMENT_DIRECTION::UNKOWN;
            break;
        };

        return result;
    };

    MOVEMENT_DIRECTION direction_to_go;

    if (player_input.size() == 1)
    {
        direction_to_go = get_direction(player_input[0]);
    }
    else
    {
        direction_to_go = get_direction(player_input[1]);
    }

    return ActionPayload{{"direction", std::to_string(direction_to_go)}};
};

PayloadGenerator TravelCommand::get_payload_generator()
{
    return payload_generator;
}

bool TravelCommand::handle_command(GameManager &game_manager, SceneManager &scene_manager, Rule::PlayerCommand &command)
{
    bool scene_changed = false;
    MOVEMENT_DIRECTION travel_direction = (MOVEMENT_DIRECTION)std::stoi(command.payload["direction"]);
    auto new_scene = scene_manager.get_next_scene(game_manager.get_player_position(), travel_direction);

    if (!new_scene.blocked && new_scene.next_scene_name != "")
    {
        scene_changed = true;
        game_manager.set_player_position(new_scene.next_scene_name);
    }
    else if (new_scene.blocked)
    {
        std::cout
            << new_scene.blocked_reason
            << std::endl;
    }
    else
    {
        std::cout
            << "We stick to the paths here"
            << std::endl;
    }

    if (scene_changed)
    {
        std::cout
            << scene_manager.get_scene_description(game_manager.get_player_position())
            << std::endl;
    }

    return true;
}