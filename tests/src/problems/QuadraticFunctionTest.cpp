#include "gtest/gtest.h"
#include "../../../src/GeneticAlgorithm.hpp"

void printAlleles(const IAlleles &alleles)
{
    auto iterators = alleles.constIterators();
    auto begin = std::get<0>(iterators);
    auto end = std::get<1>(iterators);

    for (auto it = begin; it != end; it++)
        std::cout << *it;
    std::cout << std::endl
              << std::endl
              << std::endl;
}

unsigned decodeFromBinary(const Individual &individual)
{
    unsigned decoded = 0;
    unsigned exponent = 0;
    auto reverseIterators = individual.alleles->reverseIterators();
    auto begin = std::get<0>(reverseIterators);
    auto end = std::get<1>(reverseIterators);
    for (auto bit = begin; bit != end; bit++)
    {
        decoded += *bit * std::pow(2, exponent);
        exponent++;
    }
    return decoded;
};

TEST(QuadraticFunctionTest, simpleCaseSolutionIsFoundAfter40IterationsOrLess)
{
    auto quadraticFitness = [](const Individual &individual) {
        auto x = decodeFromBinary(individual);
        return x * x;
    };

    auto stopping = [](const float &fitness) { return fitness > 960 ? true : false; };
    auto genetic = GeneticAlgorithm<Individual>(40, 5, 0.9, 0.01, quadraticFitness, stopping);
    genetic.findSolution(40);
    auto best = genetic.bestIndividual();

    // printAlleles(*best.alleles.get());
    auto bestFitnessValue = quadraticFitness(best);

    ASSERT_NEAR(961, bestFitnessValue, 0.0001);
}

TEST(QuadraticFunctionTest, maxInMidlleOfSearchSapceSolutionIsFoundAfter40IterationsOrLess)
{
    auto quadraticFitness = [](const Individual &individual) {
        auto x = decodeFromBinary(individual);
        return -x * x + 20 * x + 1000;
    };

    auto stopping = [](const float &fitness) { return fitness > 1100 - 1 ? true : false; };
    auto genetic = GeneticAlgorithm<Individual>(40, 5, 0.9, 0.01, quadraticFitness, stopping);
    genetic.findSolution(40);
    auto best = genetic.bestIndividual();

    // printAlleles(*best.alleles.get());
    auto bestFitnessValue = quadraticFitness(best);

    ASSERT_NEAR(1100, bestFitnessValue, 0.0001);
}