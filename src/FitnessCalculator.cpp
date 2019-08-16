#include "FitnessCalculator.hpp"

void FitnessCalculator::updateFitness(std::vector<Individual> &population) const
{
    for (auto &individual : population)
        individual.fitness = fitnessFunction(individual);
    normalize(population);
}

void FitnessCalculator::normalize(std::vector<Individual> &population) const
{
    auto minFitness = findMinFitness(population);
    if (minFitness < 0.0)
        for (auto &i : population)
            i.fitness -= minFitness;
}

float FitnessCalculator::findMinFitness(std::vector<Individual> &population) const
{
    float minFitness = std::numeric_limits<float>::infinity();
    for (auto &i : population)
        if (i.fitness < minFitness)
            minFitness = i.fitness;
    return minFitness;
}