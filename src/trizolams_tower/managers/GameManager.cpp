#include "GameManager.h"

void GameManager::set_player_position(std::string player_pos)
{
    m_player_position = player_pos;
}

std::string GameManager::get_player_position()
{
    return m_player_position;
}