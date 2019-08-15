#include <utility>

#include "DefaultCrossover.hpp"

void DefaultCrossover::cross(std::vector<Individual> &matingPool)
{
    std::vector<Individual> newPopulation;
    while (matingPool.size() > 0)
    {
        auto pair = selectPair(matingPool);
        auto firstIndividual = matingPool[pair.first];
        auto secondIndividual = matingPool[pair.second];

        crossPair(firstIndividual, secondIndividual);

        newPopulation.push_back(firstIndividual);
        newPopulation.push_back(secondIndividual);

        if (pair.first < pair.second)
        {
            matingPool.erase(matingPool.begin() + pair.first);
            matingPool.erase(matingPool.begin() + pair.second - 1);
        }
        else
        {
            matingPool.erase(matingPool.begin() + pair.second);
            matingPool.erase(matingPool.begin() + pair.first - 1);
        }
    }
    matingPool = std::move(newPopulation);
}

std::pair<unsigned, unsigned> DefaultCrossover::selectPair(std::vector<Individual> &matingPool)
{
    return std::make_pair<unsigned, unsigned>(0, 1);
}

void DefaultCrossover::crossPair(Individual &first, Individual &second)
{
    if (crossingTakesPlace())
    {
        const auto crossingSpot = probabilistic.uniform_int(0, first.alleles->size() - 1);
        first.mate(second, crossingSpot);
    }
}

bool DefaultCrossover::crossingTakesPlace()
{
    return probabilistic.bernoulli(crossoverProbability);
}