#pragma once
#include <memory>

#include "IMutationStrategy.hpp"
#include "../Probabilistic.hpp"

class DefaultMutation : public IMutationStrategy
{
public:
    DefaultMutation(float mutationProb);

    virtual void mutate(IAlleles &alleles) override;

protected:
    const float mutationProbability;
    std::shared_ptr<Probabilistic> prob;
};