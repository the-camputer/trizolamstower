#pragma once

#include <string>

#define stringify(name) #name
enum COMMAND_TYPE
{
    PLACE_OBJECT,
    REMOVE_FROM_INVENTORY,
    PUT_IN_INVENTORY,
    LOG,
    RESET,
    LOAD,
    SAVE,
    MOVEMENT,
    // TODO: Add interatction commands as they get created
};

inline const char *COMMAND_TYPE_NAMES[] = {
    stringify(COMMAND_TYPE::PLACE_OBJECT),
    stringify(COMMAND_TYPE::REMOVE_FROM_INVENTORY),
    stringify(COMMAND_TYPE::PUT_IN_INVENTORY),
    stringify(COMMAND_TYPE::LOG),
    stringify(COMMAND_TYPE::RESET),
    stringify(COMMAND_TYPE::LOAD),
    stringify(COMMAND_TYPE::SAVE),
    stringify(COMMAND_TYPE::MOVEMENT),
};