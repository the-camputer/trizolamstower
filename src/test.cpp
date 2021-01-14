#include <iostream>
#include "bestinshow/engine/grammar/TestGrammar.h"

int main() {
    TestGrammar grammar{};
    std::cout << grammar.get_grammar();
}