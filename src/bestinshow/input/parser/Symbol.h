#pragma once

#include <string>
#include <regex>

struct Symbol {
    std::string nonterminal;
    std::regex terminal;
};
