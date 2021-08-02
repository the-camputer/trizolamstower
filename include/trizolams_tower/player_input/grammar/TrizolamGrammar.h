#pragma once
#include "bestinshow/engine/grammar/Grammar.h"
#include <memory>
#include <string>
#include <unordered_map>

// TODO: Consider changing up this impl to have get_instance return a TrizolamGrammar instance. Then call get_grammar on
// that to get the grammar. This will allow you to run add_object on the TrizolamGrammar instance without awkward
// references to the grammar floating around
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
  static void add_object(std::vector<std::string>);
};
