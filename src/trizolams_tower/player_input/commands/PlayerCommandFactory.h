#pragma once

#include "CommandTypes.h"
#include "PlayerCommand.h"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class PlayerCommandFactory
{
  public:
    static PlayerCommand generate_player_command(std::string, std::vector<std::string>);

  private:
    using generator_map =
        std::unordered_map<COMMAND_TYPE,
                           std::function<std::unordered_map<std::string, std::string>(const std::vector<std::string>)>>;
    PlayerCommandFactory();
    static generator_map m;
};