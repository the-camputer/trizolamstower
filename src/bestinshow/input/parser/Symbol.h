#pragma once

#include <string>
#include <regex>

struct Symbol {
    std::string nonterminal;
    std::string terminal_pattern;
    std::regex *terminal = nullptr;
};
