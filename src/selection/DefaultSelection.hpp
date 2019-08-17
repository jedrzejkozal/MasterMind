#pragma once

#include <algorithm>

#include "ISelectionStrategy.hpp"
#include "../Probabilistic.hpp"

template <typename IndividualType = Individual>
class DefaultSelection : public ISelectionStrategy<IndividualType>
{
public:
    DefaultSelection() = default;
    DefaultSelection(DefaultSelection &&rhs);

    virtual void select(std::vector<IndividualType> &population) override;

private:
    std::vector<float> calcCumulativeProb(const std::vector<IndividualType> &population) const;
    std::vector<IndividualType> drawMatingPool(const std::vector<IndividualType> &population,
                                               const std::vector<float> &cumulativeProb) const;

    std::vector<float> getIndividualsFitness(const std::vector<IndividualType> &population) const;
    float calcVectorSum(const std::vector<float> &v) const noexcept;
    std::vector<float> calcSelectionProb(std::vector<float> &fitness, float &sum) const noexcept;
    std::vector<float> toCumulative(std::vector<float> &SelectionProb) const noexcept;

    IndividualType selectIndividual(const std::vector<IndividualType> &population,
                                    const std::vector<float> &cumulativeProb) const noexcept;
    unsigned indexFromIterator(const std::vector<float>::const_iterator &it,
                               const std::vector<float> &container) const noexcept;
    void crossPair(IndividualType &first, IndividualType &second);

    const Probabilistic probabilistic;
};

template <typename IndividualType>
DefaultSelection<IndividualType>::DefaultSelection(DefaultSelection &&rhs)
    : probabilistic(const_cast<Probabilistic &&>(std::move(rhs.probabilistic))) {}

template <typename IndividualType>
void DefaultSelection<IndividualType>::select(std::vector<IndividualType> &population)
{
    auto cumulativeSelectionProb = calcCumulativeProb(population);
    auto matingPool = drawMatingPool(population, cumulativeSelectionProb);
    population = std::move(matingPool);
}

template <typename IndividualType>
std::vector<float> DefaultSelection<IndividualType>::calcCumulativeProb(const std::vector<IndividualType> &population) const
{
    auto individualsFitness = getIndividualsFitness(population);
    auto fitnessSum = calcVectorSum(individualsFitness);
    auto SelectionProb = calcSelectionProb(individualsFitness, fitnessSum);
    return toCumulative(SelectionProb);
}

template <typename IndividualType>
std::vector<float> DefaultSelection<IndividualType>::getIndividualsFitness(const std::vector<IndividualType> &population) const
{
    std::vector<float> fitness;
    for (auto &individual : population)
        fitness.push_back(individual.fitness);
    return fitness;
}

template <typename IndividualType>
float DefaultSelection<IndividualType>::calcVectorSum(const std::vector<float> &vec) const noexcept
{
    float sum = 0.0;
    for (auto &elem : vec)
        sum += elem;
    return sum;
}

template <typename IndividualType>
std::vector<float> DefaultSelection<IndividualType>::calcSelectionProb(std::vector<float> &fitness,
                                                                       float &sum) const noexcept
{
    sum += 0.000000000001;
    for (auto &fit : fitness)
        fit = fit / sum;
    return fitness;
}

template <typename IndividualType>
std::vector<float> DefaultSelection<IndividualType>::toCumulative(std::vector<float> &SelectionProb) const noexcept
{
    for (auto i = 1; i < SelectionProb.size(); i++)
        SelectionProb[i] += SelectionProb[i - 1];
    return SelectionProb;
}

template <typename IndividualType>
std::vector<IndividualType> DefaultSelection<IndividualType>::drawMatingPool(const std::vector<IndividualType> &population,
                                                                             const std::vector<float> &cumulativeProb) const
{
    std::vector<IndividualType> matingPool;

    while (matingPool.size() < population.size())
    {
        auto individual = selectIndividual(population, cumulativeProb);
        matingPool.push_back(std::move(individual));
    }

    return matingPool;
}

template <typename IndividualType>
IndividualType DefaultSelection<IndividualType>::selectIndividual(const std::vector<IndividualType> &population,
                                                                  const std::vector<float> &cumulativeProb) const noexcept
{
    auto rand = probabilistic.uniform_float(0, 1);
    auto it = std::find_if(cumulativeProb.begin(),
                           cumulativeProb.end(),
                           [&rand](const float &p) {
                               return (rand <= p ? true : false);
                           });
    auto index = indexFromIterator(it, cumulativeProb);
    return IndividualType(population[index]);
}

template <typename IndividualType>
unsigned DefaultSelection<IndividualType>::indexFromIterator(const std::vector<float>::const_iterator &it,
                                                             const std::vector<float> &container) const noexcept
{
    auto index = std::distance(container.begin(), it);
    if (it == container.end())
        index--;
    return index;
}