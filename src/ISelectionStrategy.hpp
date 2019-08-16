#pragma once

#include <vector>

#include "Individual.hpp"

class ISelectionStrategy
{
public:
    virtual ~ISelectionStrategy() = default;

    virtual void select(std::vector<Individual> &population) = 0;
};