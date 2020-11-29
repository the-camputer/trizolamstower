#pragma once

#include <string>
#include <regex>
#include <ostream>

struct Symbol {
    std::string nonterminal;
    std::string terminal_pattern;

    friend inline std::ostream& operator<<(std::ostream& os, const Symbol& v)
    {
        if (v.nonterminal != "") {
            os << "<" << v.nonterminal << ">";
        } else {
            os << "\"" << v.terminal_pattern << "\"";
        }

        return os;
    }
};
