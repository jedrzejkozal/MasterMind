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
               const ICrossingStrategy &&crossingStrategy = DefaultCrossing(),
               const IMutationStrategy &&mutationStrategy = DefaultMutation());

private:
    std::vector<Individual> population;
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