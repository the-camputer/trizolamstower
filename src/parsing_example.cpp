#include <iostream>
#include "bestinshow/engine/grammar/ExampleGrammar.h"

int main() {
    ExampleGrammar grammar{};
    std::cout << grammar.get_grammar();
}