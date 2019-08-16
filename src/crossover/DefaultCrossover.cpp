#include <utility>

#include "DefaultCrossover.hpp"

void DefaultCrossover::cross(std::vector<Individual> &matingPool)
{
    std::vector<Individual> newPopulation;
    while (matingPool.size() > 0)
        addPairToNewPopulation(newPopulation, matingPool);
    matingPool = std::move(newPopulation);
}

void DefaultCrossover::addPairToNewPopulation(std::vector<Individual> &newPopulation,
                                              std::vector<Individual> &matingPool)
{
    auto pair = selectPair(matingPool);
    auto firstIndividual = matingPool[pair.first];
    auto secondIndividual = matingPool[pair.second];

    crossPair(firstIndividual, secondIndividual);
    newPopulation.push_back(firstIndividual);
    newPopulation.push_back(secondIndividual);

    removeUsed(matingPool, pair);
}

std::pair<unsigned, unsigned> DefaultCrossover::selectPair(std::vector<Individual> &matingPool)
{
    unsigned firstSelected = probabilistic.uniform_int(0, matingPool.size() - 1);
    unsigned secondSelected = firstSelected;
    while (secondSelected == firstSelected)
        secondSelected = probabilistic.uniform_int(0, matingPool.size() - 1);

    return std::make_pair<unsigned, unsigned>(std::move(firstSelected), std::move(secondSelected));
}

void DefaultCrossover::crossPair(Individual &first, Individual &second)
{
    if (crossingTakesPlace())
    {
        const auto crossingSpot = probabilistic.uniform_int(1, first.alleles->size() - 1);
        first.mate(second, crossingSpot);
    }
}

bool DefaultCrossover::crossingTakesPlace()
{
    return probabilistic.bernoulli(crossoverProbability);
}

void DefaultCrossover::removeUsed(std::vector<Individual> &matingPool,
                                  std::pair<unsigned, unsigned> pair)
{
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