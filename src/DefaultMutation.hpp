#pragma once
#include <iostream>
#include <memory>

#include "IMutationStrategy.hpp"
#include "Probabilistic.hpp"

class DefaultMutation : public IMutationStrategy
{
public:
    DefaultMutation()
    {
        prob = std::make_shared<const Probabilistic>();
    }

    virtual void mutate(Individual &individual) override;
    bool probTest()
    {
        std::cout << "probTest call" << std::endl;
        return prob->bernoulli(0.5);
    }

protected:
    std::shared_ptr<const Probabilistic> prob;
};

void DefaultMutation::mutate(Individual &individual)
{
}