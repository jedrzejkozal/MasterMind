#include <algorithm>

#include "DefaultCrossing.hpp"

void DefaultCrossing::cross(std::vector<Individual> &population)
{
    auto cumulativeCrossingProb = calcCumulativeProb(population);
    auto newPopulation = drawNewPopulation(population, cumulativeCrossingProb);
    population = std::move(newPopulation);
}

std::vector<float> DefaultCrossing::calcCumulativeProb(const std::vector<Individual> &population)
{
    auto individualsFitness = calcIndividualFitness(population);
    auto fitnessSum = calcVectorSum(individualsFitness);
    auto crossingProb = calcCrossingProb(individualsFitness, fitnessSum);
    return toCumulative(crossingProb);
}

std::vector<float> DefaultCrossing::calcIndividualFitness(const std::vector<Individual> &population)
{
    std::vector<float> fitness;
    for (auto &individual : population)
        fitness.push_back(fitnessFunction(individual));
    return fitness;
}

float DefaultCrossing::calcVectorSum(const std::vector<float> &v)
{
    float sum = 0;
    for (auto &e : v)
        sum += e;
    return sum;
}

std::vector<float> DefaultCrossing::calcCrossingProb(std::vector<float> &fitness, const float &sum)
{
    for (auto &f : fitness)
        f = f / sum;
    return fitness;
}

std::vector<float> DefaultCrossing::toCumulative(std::vector<float> &crossingProb)
{
    for (auto i = 1; i < crossingProb.size(); i++)
        crossingProb[i] += crossingProb[i - 1];
    return crossingProb;
}

std::vector<Individual> DefaultCrossing::drawNewPopulation(const std::vector<Individual> &population,
                                                           const std::vector<float> &cumulativeProb)
{
    std::vector<Individual> newPopulation;

    for (auto i = 0; i < population.size(); i += 2)
    {
        auto firstIndividual = selectIndividual(population, cumulativeProb);
        auto secondIndividual = selectIndividual(population, cumulativeProb);
        crossPair(firstIndividual, secondIndividual);
        newPopulation.push_back(std::move(firstIndividual));
        newPopulation.push_back(std::move(secondIndividual));
    }

    return newPopulation;
}

Individual DefaultCrossing::selectIndividual(const std::vector<Individual> &population,
                                             const std::vector<float> &cumulativeProb)
{
    auto rand = prob.uniform_float(0, 1);
    auto it = std::find_if(cumulativeProb.begin(), cumulativeProb.end(), [rand](const float &p) { return (rand <= p ? true : false); });
    auto index = std::distance(cumulativeProb.begin(), it);
    if (it == cumulativeProb.end())
        index--;
    return Individual(population[index]);
}

void DefaultCrossing::crossPair(Individual &first, Individual &second)
{
    if (prob.bernoulli(crossingProbability))
    {
        const auto crossingSpot = prob.uniform_int(0, first.alleles->size() - 1);
        first.cross(second, crossingSpot);
    }
}
