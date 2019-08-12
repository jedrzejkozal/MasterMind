#pragma once

#include "IMutationStrategy.hpp"

class DefaultMutation : public IMutationStrategy
{
public:
    virtual void mutate(Individual &individual) override;
};

void DefaultMutation::mutate(Individual &individual)
{
}