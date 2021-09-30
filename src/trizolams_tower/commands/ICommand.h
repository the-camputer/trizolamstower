#pragma once

#include "../managers/GameManager.h"
#include "../managers/SceneManager.h"
#include "bestinshow/engine/grammar/Rule.h"

class ICommand
{
public:
    virtual ~ICommand();
    virtual bool handle_command(GameManager &, SceneManager &, Rule::PlayerCommand &) = 0;
    virtual PayloadGenerator get_payload_generator() = 0;

private:
    PayloadGenerator payload_generator;
};
