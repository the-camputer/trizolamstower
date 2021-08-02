#include "Grammar.h"

class ExampleGrammar
{
private:
  Grammar grammar;

public:
  ExampleGrammar();
  ~ExampleGrammar() = default;
  Grammar get_grammar();
};