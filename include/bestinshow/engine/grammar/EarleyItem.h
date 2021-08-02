#pragma once

#include <vector>

#include "spdlog/fmt/ostr.h"

struct EarleyItem
{
    int rule;
    int production;
    int start;
    int next;

    inline friend bool operator==(const EarleyItem &ei1, const EarleyItem &ei2)
    {
        return ei1.rule == ei2.rule && ei1.production == ei2.production && ei1.start == ei2.start &&
               ei1.next == ei2.next;
    }

    template <typename OStream>
    inline friend OStream &operator<<(OStream &ostream, const EarleyItem &v)
    {
        ostream << "{ rule: " << v.rule << ", production: " << v.production << ", start: " << v.start
                << ", next: " << v.next << "}";
        return ostream;
    }
};

using StateSet = std::vector<EarleyItem>;
using ParseTable = std::vector<StateSet>;