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