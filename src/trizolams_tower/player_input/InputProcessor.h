#pragma once

#include "bestinshow/engine/grammar/Grammar.h"
#include <string>

class InputProcessor
{
  public:
    InputProcessor();
    Rule::PlayerCommand process(std::string);
    Grammar get_grammar();

  private:
    static bool not_isalnum_or_space(char c);
    Grammar grammar;
};