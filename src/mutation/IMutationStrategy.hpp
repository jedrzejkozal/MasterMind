#pragma once

#include "../alleles/IAlleles.hpp"

class IMutationStrategy
{
public:
    virtual void mutate(IAlleles &individual) = 0;
    virtual ~IMutationStrategy() = default;
};