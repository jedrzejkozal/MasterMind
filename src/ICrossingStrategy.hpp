#pragma once

#include <vector>

#include "Individual.hpp"

class ICrossingStrategy
{
public:
    ICrossingStrategy(const std::function<float(const Individual &)> fitFunc)
        : fitnessFunction(fitFunc)
    {
    }

    ICrossingStrategy(ICrossingStrategy &&rhs)
    {
        fitnessFunction = std::move(rhs.fitnessFunction);
    }

    virtual void cross(std::vector<Individual> &population) = 0;
    virtual ~ICrossingStrategy() = default;

protected:
    std::function<float(const Individual &)> fitnessFunction;
};