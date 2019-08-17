#include "gtest/gtest.h"
#include "../../../src/GeneticAlgorithm.hpp"
#include "../../utils/DecodeFromBinary.hpp"
#include "../../utils/PrintAlleles.hpp"

TEST(LocalMinimaTest, globalMaxIsFound)
{
    auto quadraticFitness = [](const Individual &individual) {
        auto x = decodeFromBinary(individual.alleles.get());
        if (x < 15)
            return -x * x + 20 * x;
        return -x * x + 40 * x;
    };

    auto stopping = [](const float &fitness) { return fitness > 400 - 1 ? true : false; };
    auto genetic = GeneticAlgorithm<Individual>(40, 5, 0.9, 0.01, quadraticFitness, stopping);
    genetic.findSolution(40);
    auto best = genetic.bestIndividual();

    // printAlleles(*best.alleles.get());
    auto bestFitnessValue = quadraticFitness(best);

    ASSERT_NEAR(400, bestFitnessValue, 0.0001);
}