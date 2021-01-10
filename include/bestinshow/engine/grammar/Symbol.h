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

    friend inline bool operator==(const Symbol &s1, const Symbol &s2)
    {
        return s1.nonterminal == s2.nonterminal && s1.terminal_pattern == s2.terminal_pattern;
    }
};
