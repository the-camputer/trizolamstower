#pragma once
#include <vector>

struct EarleyItem {
    int rule;
    int production;
    int start;
    int next;

    inline friend bool operator==(const EarleyItem &ei1, const EarleyItem &ei2) {
        return ei1.rule == ei2.rule && ei1.production == ei2.production &&  ei1.start == ei2.start && ei1.next == ei2.next;
    }

    inline friend std::ostream& operator<<(std::ostream& ostream, const EarleyItem& v) {
        ostream << "{ rule: " << v.rule << ", production: " << v.production << ", start: " << v.start << ", next: " << v.next << "}";
        return ostream;
    }
};

using StateSet = std::vector<EarleyItem>;
using ParseTable = std::vector<StateSet>;