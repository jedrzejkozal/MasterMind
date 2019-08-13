#pragma once
#include <iostream>
#include <memory>

#include "IMutationStrategy.hpp"
#include "Probabilistic.hpp"

class DefaultMutation : public IMutationStrategy
{
public:
    DefaultMutation(float mutationProb)
        : mutationProbability(mutationProb)
    {
        prob = std::make_shared<const Probabilistic>();
    }

    virtual void mutate(IAlleles &individual) override;

    bool probTest()
    {
        std::cout << "probTest call" << std::endl;
        return prob->bernoulli(0.5);
    }

protected:
    float mutationProbability;
    std::shared_ptr<const Probabilistic> prob;
};

void DefaultMutation::mutate(IAlleles &alleles)
{
    auto iterators = alleles.iterators();
    auto begin = std::get<0>(iterators);
    auto end = std::get<1>(iterators);

    for (auto it = begin; it != end; it++)
        if (prob->bernoulli(mutationProbability))
            alleles.switch_allele_at(it);
}