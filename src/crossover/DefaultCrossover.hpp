#include <utility>

#include "ICrossoverStrategy.hpp"
#include "../Probabilistic.hpp"

template <typename IndividualType = Individual>
class DefaultCrossover : public ICrossoverStrategy<IndividualType>
{
public:
    DefaultCrossover(const float &crossoverProb)
        : crossoverProbability(crossoverProb) {}

    DefaultCrossover(DefaultCrossover &&rhs) = default;
    virtual ~DefaultCrossover() = default;

    virtual void cross(std::vector<IndividualType> &matingPool) override;

private:
    void addPairToNewPopulation(std::vector<IndividualType> &newPopulation,
                                std::vector<IndividualType> &matingPool);
    std::pair<unsigned, unsigned> selectPair(std::vector<IndividualType> &matingPool);
    void crossPair(IndividualType &first, IndividualType &second);
    bool crossingTakesPlace();
    void removeUsed(std::vector<IndividualType> &matingPool,
                    std::pair<unsigned, unsigned> pair);

    const float crossoverProbability;
    Probabilistic probabilistic;
};

template <typename IndividualType>
void DefaultCrossover<IndividualType>::cross(std::vector<IndividualType> &matingPool)
{
    std::vector<IndividualType> newPopulation;
    while (matingPool.size() > 0)
        addPairToNewPopulation(newPopulation, matingPool);
    matingPool = std::move(newPopulation);
}

template <typename IndividualType>
void DefaultCrossover<IndividualType>::addPairToNewPopulation(std::vector<IndividualType> &newPopulation,
                                                              std::vector<IndividualType> &matingPool)
{
    auto pair = selectPair(matingPool);
    auto firstIndividual = matingPool[pair.first];
    auto secondIndividual = matingPool[pair.second];

    crossPair(firstIndividual, secondIndividual);
    newPopulation.push_back(firstIndividual);
    newPopulation.push_back(secondIndividual);

    removeUsed(matingPool, pair);
}

template <typename IndividualType>
std::pair<unsigned, unsigned> DefaultCrossover<IndividualType>::selectPair(std::vector<IndividualType> &matingPool)
{
    unsigned firstSelected = probabilistic.uniform_int(0, matingPool.size() - 1);
    unsigned secondSelected = firstSelected;
    while (secondSelected == firstSelected)
        secondSelected = probabilistic.uniform_int(0, matingPool.size() - 1);

    return std::make_pair<unsigned, unsigned>(std::move(firstSelected), std::move(secondSelected));
}

template <typename IndividualType>
void DefaultCrossover<IndividualType>::crossPair(IndividualType &first, IndividualType &second)
{
    if (crossingTakesPlace())
    {
        const auto crossingSpot = probabilistic.uniform_int(1, first.allelesSize() - 1);
        first.mate(second, crossingSpot);
    }
}

template <typename IndividualType>
bool DefaultCrossover<IndividualType>::crossingTakesPlace()
{
    return probabilistic.bernoulli(crossoverProbability);
}

template <typename IndividualType>
void DefaultCrossover<IndividualType>::removeUsed(std::vector<IndividualType> &matingPool,
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