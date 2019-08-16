#pragma once

#include "../../src/mutation/DefaultMutation.hpp"

class DefaultMutationTestable : public DefaultMutation
{
public:
    DefaultMutationTestable(std::shared_ptr<Probabilistic> p)
        : DefaultMutation(0.1)
    {
        prob = p;
    }
};
