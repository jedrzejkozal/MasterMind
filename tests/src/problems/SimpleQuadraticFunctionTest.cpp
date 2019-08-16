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

auto getFitnessFunction()
{
    auto decodeFromBinary = [](auto &individual) {
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
    return [decodeFromBinary](const Individual &i) {
        auto x = decodeFromBinary(i);
        return x * x;
    };
}

TEST(SimpleQuadraticFunctionTest, solutionIsFoundAfter20IterationsOrLess)
{
    auto quadraticFitness = getFitnessFunction();
    auto stopping = [](const float &fitness) { return fitness > 960 ? true : false; };
    auto genetic = GeneticAlgorithm(20, 5, 0.9, 0.01, quadraticFitness, stopping);
    genetic.findSolution(20);
    auto best = genetic.bestIndividual();

    std::cout << "alleles = ";
    printAlleles(*best.alleles.get());
    auto bestFitnessValue = quadraticFitness(best);
    std::cout << "best fitness value = " << bestFitnessValue << std::endl;

    ASSERT_NEAR(961, bestFitnessValue, 0.0001);
}