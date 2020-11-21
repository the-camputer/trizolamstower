#pragma once

#include "Production.h"
#include <vector>
#include <string>

struct Rule {
    std::string rule_name;
    std::vector<Production> productions;
};