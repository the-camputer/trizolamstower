#pragma once

#include "./ICommand.h"

class PlaceObjectCommand : public ICommand
{
public:
    PlaceObjectCommand();
    ~PlaceObjectCommand() = default;
    bool handle_command(GameManager &, SceneManager &, Rule::PlayerCommand &) override;
    PayloadGenerator get_payload_generator() override;

private:
    PayloadGenerator payload_generator;
};
