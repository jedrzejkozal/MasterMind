#pragma once

#include <vector>

#include "Individual.hpp"

class ISelectionStrategy
{
public:
    ISelectionStrategy(const std::function<float(const Individual &)> fitFunc)
        : fitnessFunction(fitFunc)
    {
    }

    ISelectionStrategy(ISelectionStrategy &&rhs)
    {
        fitnessFunction = std::move(rhs.fitnessFunction);
    }

    virtual void select(std::vector<Individual> &population) = 0;
    virtual ~ISelectionStrategy() = default;

protected:
    std::function<float(const Individual &)> fitnessFunction;
};