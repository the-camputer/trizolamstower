#pragma once

#include "ICommand.h"

class TravelCommand : public ICommand
{
public:
    TravelCommand();
    ~TravelCommand() = default;
    bool handle_command(GameManager &, SceneManager &, Rule::PlayerCommand &) override;
    PayloadGenerator get_payload_generator() override;

private:
    PayloadGenerator payload_generator;
};
