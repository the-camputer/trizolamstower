#pragma once
#include <unordered_set>

struct EarleyItem {
    int rule;
    int start;
    int next;

    inline friend bool operator==(const EarleyItem &ei1, const EarleyItem &ei2) {
        return ei1.rule == ei2.rule && ei1.start == ei2.start && ei1.next == ei2.next;
    }
};

using StateSet = std::unordered_set<EarleyItem>;