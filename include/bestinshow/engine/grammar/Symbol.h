#pragma once

#include <string>
#include <regex>
#include <ostream>

enum SymbolType { TERMINAL, NONTERMINAL };

struct Symbol {
    std::string pattern;
    SymbolType type;

    friend inline std::ostream& operator<<(std::ostream& os, const Symbol& v)
    {
        if (v.type == SymbolType::NONTERMINAL) {
            os << "<" << v.pattern << ">";
        } else {
            os << v.pattern;
        }

        return os;
    }

    friend inline bool operator==(const Symbol &s1, const Symbol &s2)
    {
        return s1.pattern == s2.pattern && s1.type == s2.type;
    }
};
