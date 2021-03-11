#pragma once

#include "CommandTypes.h"
#include <memory>
#include <string>
#include <unordered_map>

struct PlayerCommand
{
    COMMAND_TYPE type;
    std::unordered_map<std::string, std::string> payload;

    template <typename OStream> inline friend OStream &operator<<(OStream &ostream, const PlayerCommand &v)
    {
        ostream << "{ type: " << v.type << ", payload: { ";
        for (auto const &pair : v.payload)
        {
            ostream << pair.first << ": " << pair.second << ", ";
        }
        ostream << "} }";
        return ostream;
    }
};