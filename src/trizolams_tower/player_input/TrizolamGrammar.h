#pragma once
#include "bestinshow/engine/grammar/Grammar.h"
#include "../commands/CommandProcessor.h"
#include <memory>
#include <string>
#include <unordered_map>

// TODO: Consider changing up this impl to have get_instance return a TrizolamGrammar instance. Then call get_grammar on
// that to get the grammar. This will allow you to run add_object on the TrizolamGrammar instance without awkward
// references to the grammar floating around

// TODO: HEY YOU WHAT IF WE DIDN'T USE A SINGLETON AND JUST PASSED AROUND A POINTER INSTEAD?
class TrizolamGrammar
{
private:
  static Grammar create_new_instance();
  Grammar create_new_grammar();

  static std::unique_ptr<Grammar> m_instance;

  std::unique_ptr<Grammar> m_grammar;
  std::shared_ptr<CommandProcessor> m_command_processor;

  static std::unordered_map<std::string, std::vector<std::vector<std::string>>> m_terminal_phrases;

public:
  TrizolamGrammar(std::shared_ptr<CommandProcessor>);
  ~TrizolamGrammar() = default;
  // static Grammar &get_instance();
  Grammar &get_grammar();
  static void add_object(std::vector<std::string>);
};
