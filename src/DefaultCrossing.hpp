#pragma once

#include "ICrossingStrategy.hpp"

class DefaultCrossing : public ICrossingStrategy
{
public:
    virtual void cross(std::vector<Individual> population) override;
};

void DefaultCrossing::cross(std::vector<Individual> population)
{
}