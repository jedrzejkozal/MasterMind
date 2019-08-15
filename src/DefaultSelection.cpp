#include <algorithm>

#include "DefaultSelection.hpp"

void DefaultSelection::select(std::vector<Individual> &population)
{
    auto cumulativeSelectionProb = calcCumulativeProb(population);
    auto matingPool = drawMatingPool(population, cumulativeSelectionProb);
    population = std::move(matingPool);
}

std::vector<float> DefaultSelection::calcCumulativeProb(const std::vector<Individual> &population)
{
    auto individualsFitness = calcIndividualFitness(population);
    auto fitnessSum = calcVectorSum(individualsFitness);
    auto SelectionProb = calcSelectionProb(individualsFitness, fitnessSum);
    return toCumulative(SelectionProb);
}

std::vector<float> DefaultSelection::calcIndividualFitness(const std::vector<Individual> &population)
{
    std::vector<float> fitness;
    for (auto &individual : population)
        fitness.push_back(fitnessFunction(individual));
    return fitness;
}

float DefaultSelection::calcVectorSum(const std::vector<float> &v)
{
    float sum = 0;
    for (auto &e : v)
        sum += e;
    return sum;
}

std::vector<float> DefaultSelection::calcSelectionProb(std::vector<float> &fitness, const float &sum)
{
    for (auto &f : fitness)
        f = f / sum;
    return fitness;
}

std::vector<float> DefaultSelection::toCumulative(std::vector<float> &SelectionProb)
{
    for (auto i = 1; i < SelectionProb.size(); i++)
        SelectionProb[i] += SelectionProb[i - 1];
    return SelectionProb;
}

std::vector<Individual> DefaultSelection::drawMatingPool(const std::vector<Individual> &population,
                                                         const std::vector<float> &cumulativeProb)
{
    std::vector<Individual> matingPool;

    for (auto i = 0; i < population.size(); i += 2)
    {
        auto firstIndividual = selectIndividual(population, cumulativeProb);
        auto secondIndividual = selectIndividual(population, cumulativeProb);
        matingPool.push_back(std::move(firstIndividual));
        matingPool.push_back(std::move(secondIndividual));
    }

    return matingPool;
}

Individual DefaultSelection::selectIndividual(const std::vector<Individual> &population,
                                              const std::vector<float> &cumulativeProb)
{
    auto rand = probabilistic.uniform_float(0, 1);
    auto it = std::find_if(cumulativeProb.begin(), cumulativeProb.end(), [rand](const float &p) { return (rand <= p ? true : false); });
    auto index = std::distance(cumulativeProb.begin(), it);
    if (it == cumulativeProb.end())
        index--;
    return Individual(population[index]);
}
