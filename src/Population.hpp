#pragma once

#include <functional>

#include "Individual.hpp"
#include "ICrossingStrategy.hpp"
#include "DefaultCrossing.hpp"
#include "IMutationStrategy.hpp"
#include "DefaultMutation.hpp"

class Population
{
public:
    Population(unsigned popSize,
               unsigned allelesSize,
               float mutationProb,
               float crossingProb,
               const std::function<float(const Individual &)> fitnessFunction,
               const ICrossingStrategy &&crossingStrategy = std::move(DefaultCrossing()),
               const IMutationStrategy &&mutationStrategy = std::move(DefaultMutation(0.5)));

private:
    void mutate();

    std::vector<Individual> population;
    std::unique_ptr<ICrossingStrategy> crossing;
    std::unique_ptr<IMutationStrategy> mutation;
};

Population::Population(unsigned popSize,
                       unsigned allelesSize,
                       float mutationProb,
                       float crossingProb,
                       const std::function<float(const Individual &)> fitnessFunction,
                       const ICrossingStrategy &&crossingStrategy,
                       const IMutationStrategy &&mutationStrategy)
    : population(popSize, Individual(allelesSize))
{
}

void Population::mutate()
{
    for (auto &i : population)
        i.mutate(*mutation.get());
}