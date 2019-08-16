#include "gtest/gtest.h"
#include "../../../src/GeneticAlgorithm.hpp"
#include "../../utils/DecodeFromBinary.hpp"
#include "../../utils/PrintAlleles.hpp"

TEST(QuadraticFunction1DTest, simpleCaseSolutionIsFoundAfter40IterationsOrLess)
{
    auto quadraticFitness = [](const Individual &individual) {
        auto x = decodeFromBinary(individual.alleles.get());
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

TEST(QuadraticFunction1DTest, maxInMidlleOfSearchSapceSolutionIsFoundAfter40IterationsOrLess)
{
    auto quadraticFitness = [](const Individual &individual) {
        auto x = decodeFromBinary(individual.alleles.get());
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