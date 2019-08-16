#include <algorithm>

#include "DefaultSelection.hpp"

void DefaultSelection::select(std::vector<Individual> &population)
{
    auto cumulativeSelectionProb = calcCumulativeProb(population);
    auto matingPool = drawMatingPool(population, cumulativeSelectionProb);
    population = std::move(matingPool);
}

std::vector<float> DefaultSelection::calcCumulativeProb(const std::vector<Individual> &population) const
{
    auto individualsFitness = getIndividualsFitness(population);
    auto fitnessSum = calcVectorSum(individualsFitness);
    auto SelectionProb = calcSelectionProb(individualsFitness, fitnessSum);
    return toCumulative(SelectionProb);
}

std::vector<float> DefaultSelection::getIndividualsFitness(const std::vector<Individual> &population) const
{
    std::vector<float> fitness;
    for (auto &individual : population)
        fitness.push_back(individual.fitness);
    return fitness;
}

float DefaultSelection::calcVectorSum(const std::vector<float> &v) const noexcept
{
    float sum = 0.0;
    for (auto &e : v)
        sum += e;
    return sum + 0.000000000001;
}

std::vector<float> DefaultSelection::calcSelectionProb(std::vector<float> &fitness,
                                                       const float &sum) const noexcept
{
    for (auto &f : fitness)
        f = f / sum;
    return fitness;
}

std::vector<float> DefaultSelection::toCumulative(std::vector<float> &SelectionProb) const noexcept
{
    for (auto i = 1; i < SelectionProb.size(); i++)
        SelectionProb[i] += SelectionProb[i - 1];
    return SelectionProb;
}

std::vector<Individual> DefaultSelection::drawMatingPool(const std::vector<Individual> &population,
                                                         const std::vector<float> &cumulativeProb) const
{
    std::vector<Individual> matingPool;

    while (matingPool.size() < population.size())
    {
        auto individual = selectIndividual(population, cumulativeProb);
        matingPool.push_back(std::move(individual));
    }

    return matingPool;
}

Individual DefaultSelection::selectIndividual(const std::vector<Individual> &population,
                                              const std::vector<float> &cumulativeProb) const noexcept
{
    auto rand = probabilistic.uniform_float(0, 1);
    auto it = std::find_if(cumulativeProb.begin(),
                           cumulativeProb.end(),
                           [&rand](const float &p) {
                               return (rand <= p ? true : false);
                           });
    auto index = indexFromIterator(it, cumulativeProb);
    return Individual(population[index]);
}

unsigned DefaultSelection::indexFromIterator(const std::vector<float>::const_iterator &it,
                                             const std::vector<float> &container) const noexcept
{
    auto index = std::distance(container.begin(), it);
    if (it == container.end())
        index--;
    return index;
}