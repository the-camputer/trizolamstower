#pragma once

#include <string>

class GameManager
{
private:
    std::string m_player_position;

public:
    // TODO: Should this be a singleton? Discuss as game progresses
    GameManager() = default;
    ~GameManager() = default;

    void set_player_position(std::string);
    std::string get_player_position();
};