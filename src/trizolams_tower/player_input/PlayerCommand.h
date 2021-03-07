#pragma once

#include "CommandTypes.h"
#include "ICommandPayload.h"

template <typename T, typename std::enable_if<std::is_base_of<ICommandPayload, T>::value>::type * = nullptr>
struct PlayerCommand
{
    COMMAND_TYPE type;
    T payload;
};