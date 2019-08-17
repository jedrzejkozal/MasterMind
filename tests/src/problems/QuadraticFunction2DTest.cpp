#include "gtest/gtest.h"
#include "../../../src/individual/IndividualTwoAlleles.hpp"
#include "../../../src/GeneticAlgorithm.hpp"
#include "../../utils/DecodeFromBinary.hpp"
#include "../../utils/PrintAlleles.hpp"

TEST(QuadraticFunction2DTest, simpleCaseSolutionIsFoundAfter40IterationsOrLess)
{
    auto quadraticFitness = [](const IndividualTwoAlleles &individual) {
        auto x = decodeFromBinary(individual.alleles_x.get());
        auto y = decodeFromBinary(individual.alleles_y.get());
        return -(x * x + y * y) + 10'000;
    };

    auto stopping = [](const float &fitness) { return fitness > 10'000 - 1 ? true : false; };
    auto genetic = GeneticAlgorithm<IndividualTwoAlleles>(100, 5, 0.9, 0.01, quadraticFitness, stopping);
    genetic.findSolution(60);
    auto best = genetic.bestIndividual();

    // printAlleles(*best.alleles.get());
    auto bestFitnessValue = quadraticFitness(best);

    ASSERT_NEAR(10'000, bestFitnessValue, 0.0001);
}