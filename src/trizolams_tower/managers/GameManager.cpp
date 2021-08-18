#include "GameManager.h"

void GameManager::set_player_position(int player_pos)
{
    player_position = player_pos;
}

int GameManager::get_player_position()
{
    return player_position;
}