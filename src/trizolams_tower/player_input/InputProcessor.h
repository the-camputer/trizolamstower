#pragma once

#include "ICommandPayload.h"
#include "PlayerCommand.h"
#include "bestinshow/engine/grammar/Grammar.h"
#include <string>

class InputProcessor
{
  public:
    InputProcessor();
    PlayerCommand<ICommandPayload> process(std::string);

  private:
    static bool not_isalnum_or_space(char c);
    Grammar grammar;
};