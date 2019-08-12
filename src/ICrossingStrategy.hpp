#pragma once

#include <vector>

#include "Individual.hpp"

class ICrossingStrategy
{
public:
    virtual void cross(std::vector<Individual> population) = 0;
};