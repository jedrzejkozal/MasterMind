#pragma once

#include <vector>

#include "Individual.hpp"

class FitnessCalculator
{
public:
    FitnessCalculator(const std::function<float(const Individual &)> &&fitnessFunc)
        : fitnessFunction(std::move(fitnessFunc)) {}

    void updateFitness(std::vector<Individual> &population) const;

private:
    void normalize(std::vector<Individual> &population) const;
    float findMinFitness(std::vector<Individual> &population) const;

    const std::function<float(const Individual &)> fitnessFunction;
};