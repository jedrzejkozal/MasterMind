#include "gtest/gtest.h"
#include "../../../src/GeneticAlgorithm.hpp"
#include "../../utils/DecodeFromBinary.hpp"
#include "../../utils/PrintAlleles.hpp"

TEST(TwoEqualMaxTest, oneOfTheMaxIsFound)
{
    auto quadraticFitness = [](const Individual &individual) {
        auto x = decodeFromBinary(individual.alleles.get());
        return -x * x * x * x + 80 * x * x * x - 2200 * x * x + 24000 * x;
    };

    auto stopping = [](const float &fitness) { return fitness > 90'000 - 1 ? true : false; };
    auto genetic = GeneticAlgorithm<Individual>(40, 5, 0.9, 0.01, quadraticFitness, stopping);
    genetic.findSolution(40);
    auto best = genetic.bestIndividual();

    // printAlleles(*best.alleles.get());
    auto bestFitnessValue = quadraticFitness(best);

    ASSERT_NEAR(90'000, bestFitnessValue, 0.0001);
}