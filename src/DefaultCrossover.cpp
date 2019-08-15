#include <utility>

#include "DefaultCrossover.hpp"

void DefaultCrossover::cross(std::vector<Individual> &matingPool)
{
    // crossPair(firstIndividual, secondIndividual);
}

void DefaultCrossover::crossPair(Individual &first, Individual &second)
{
    if (probabilistic.bernoulli(crossoverProbability))
    {
        const auto crossingSpot = probabilistic.uniform_int(0, first.alleles->size() - 1);
        first.mate(second, crossingSpot);
    }
}