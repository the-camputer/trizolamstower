#pragma once
#include "bestinshow/engine/grammar/Grammar.h"
#include <memory>
#include <string>
#include <unordered_map>

class TrizolamGrammar
{
  private:
    TrizolamGrammar();
    static Grammar create_new_instance();

    static std::unique_ptr<Grammar> m_instance;
    static std::unordered_map<std::string, std::vector<std::vector<std::string>>> m_terminal_phrases;

  public:
    ~TrizolamGrammar() = default;
    static Grammar &get_instance();
};
