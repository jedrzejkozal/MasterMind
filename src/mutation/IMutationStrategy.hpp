#pragma once

#include "../alleles/IAlleles.hpp"

class IMutationStrategy
{
public:
    virtual ~IMutationStrategy() = default;

    virtual void mutate(IAlleles &individual) = 0;
};