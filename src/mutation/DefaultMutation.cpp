#include "DefaultMutation.hpp"

DefaultMutation::DefaultMutation(float mutationProb)
    : mutationProbability(mutationProb)
{
    prob = std::make_shared<Probabilistic>();
}

void DefaultMutation::mutate(IAlleles &alleles)
{
    auto iterators = alleles.iterators();
    auto begin = std::get<0>(iterators);
    auto end = std::get<1>(iterators);

    for (auto it = begin; it != end; it++)
        if (prob->bernoulli(mutationProbability))
            alleles.switch_allele_at(it);
}