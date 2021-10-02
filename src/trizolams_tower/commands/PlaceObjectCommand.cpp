#include "./PlaceObjectCommand.h"
#include <iostream>

PlaceObjectCommand::PlaceObjectCommand()
{
    payload_generator = [](std::vector<std::string> player_input)
    {
        player_input.erase(std::remove(player_input.begin(), player_input.end(), "the"), player_input.end());

        auto object = player_input[1];
        auto destination = player_input.end() - 1;

        return ActionPayload{{"object", object}, {"destination", *destination}};
    };
}

PayloadGenerator PlaceObjectCommand::get_payload_generator()
{
    return payload_generator;
}

bool PlaceObjectCommand::handle_command(GameManager &gm, SceneManager &sm, Rule::PlayerCommand &pc)
{
    // TODO: Implement this
    return false;
}