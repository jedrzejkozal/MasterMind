#pragma once
#include <memory>

#include "IMutationStrategy.hpp"
#include "Probabilistic.hpp"

class DefaultMutation : public IMutationStrategy
{
public:
    DefaultMutation(float mutationProb);

    virtual void mutate(IAlleles &individual) override;

protected:
    float mutationProbability;
    std::shared_ptr<Probabilistic> prob;
};