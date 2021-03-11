#include "PlayerCommandFactory.h"
#include "CommandTypes.h"
#include "PlayerCommand.h"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, std::string> test(std::vector<std::string> player_input);

PlayerCommandFactory::generator_map PlayerCommandFactory::m = {
    {COMMAND_TYPE::LOG, test},
};

PlayerCommand PlayerCommandFactory::generate_player_command(std::string command_name,
                                                            std::vector<std::string> player_input)
{
    PlayerCommand result;
    result.type = COMMAND_TYPE::LOG;
    // auto command_generator = PlayerCommandFactory::m.find(COMMAND_TYPE::LOG);
    // auto command = command_generator->second(player_input);
    result.payload = {};

    return result;
}

std::unordered_map<std::string, std::string> test(std::vector<std::string> player_input)
{
    return {};
}