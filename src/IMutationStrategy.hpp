#pragma once

#include "Individual.hpp"

class IMutationStrategy
{
public:
    virtual void mutate(Individual &individual) = 0;
    virtual ~IMutationStrategy() = default;
};