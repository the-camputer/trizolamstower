#pragma once

#include <string>

class GameManager
{
private:
    std::string m_player_position;

public:
    GameManager() = default;
    ~GameManager() = default;

    void set_player_position(std::string);
    std::string get_player_position();
};