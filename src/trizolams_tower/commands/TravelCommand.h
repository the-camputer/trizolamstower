#pragma once

#include "ICommand.h"
#include "../managers/GameManager.h"
#include "bestinshow/engine/grammar/Rule.h"
#include "trizolams_tower/managers/SceneManager.h"

class TravelCommand : public ICommand
{
public:
    static bool handle_command(GameManager &, SceneManager &, Rule::PlayerCommand &);
    static PayloadGenerator get_payload_generator();

private:
    static PayloadGenerator payload_generator;
};
