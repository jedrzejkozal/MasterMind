#pragma once

#include <vector>

#include "individual/Individual.hpp"

template <typename IndividualType = Individual>
class FitnessCalculator
{
public:
    FitnessCalculator(const std::function<float(const IndividualType &)> &&fitnessFunc);

    void updateFitness(std::vector<IndividualType> &population) const;

private:
    void normalize(std::vector<IndividualType> &population) const;
    float findMinFitness(std::vector<IndividualType> &population) const;

    const std::function<float(const IndividualType &)> fitnessFunction;
};

template <typename IndividualType>
FitnessCalculator<IndividualType>::FitnessCalculator(const std::function<float(const IndividualType &)> &&fitnessFunc)
    : fitnessFunction(std::move(fitnessFunc)) {}

template <typename IndividualType>
void FitnessCalculator<IndividualType>::updateFitness(std::vector<IndividualType> &population) const
{
    for (auto &individual : population)
        individual.fitness = fitnessFunction(individual);
    normalize(population);
}

template <typename IndividualType>
void FitnessCalculator<IndividualType>::normalize(std::vector<IndividualType> &population) const
{
    auto minFitness = findMinFitness(population);
    if (minFitness < 0.0)
        for (auto &i : population)
            i.fitness -= minFitness;
}

template <typename IndividualType>
float FitnessCalculator<IndividualType>::findMinFitness(std::vector<IndividualType> &population) const
{
    float minFitness = std::numeric_limits<float>::infinity();
    for (auto &i : population)
        if (i.fitness < minFitness)
            minFitness = i.fitness;
    return minFitness;
}