#pragma once

#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"
#include <ostream>
#include <regex>
#include <string>

enum SYMBOL_TYPE
{
    TERMINAL,
    NONTERMINAL,
    EMPTY
};

struct Symbol
{
    std::string pattern;
    SYMBOL_TYPE type;

    template <typename OStream>
    friend inline OStream &operator<<(OStream &os, const Symbol &v)
    {
        if (v.type == SYMBOL_TYPE::NONTERMINAL)
        {
            os << "<" << v.pattern << ">";
        }
        else
        {
            os << v.pattern;
        }

        return os;
    }

    friend inline bool operator==(const Symbol &s1, const Symbol &s2)
    {
        return s1.pattern == s2.pattern && s1.type == s2.type;
    }
};
