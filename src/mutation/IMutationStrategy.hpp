#pragma once

#include "../IAlleles.hpp"

class IMutationStrategy
{
public:
    virtual void mutate(IAlleles &individual) = 0;
    virtual ~IMutationStrategy() = default;
};