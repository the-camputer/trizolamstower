#pragma once

#include "bestinshow/engine/grammar/Grammar.h"
#include "commands/PlayerCommand.h"
#include <string>

class InputProcessor
{
  public:
    InputProcessor();
    PlayerCommand process(std::string);

  private:
    static bool not_isalnum_or_space(char c);
    Grammar grammar;
};