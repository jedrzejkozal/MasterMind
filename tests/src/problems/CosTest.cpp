#include <math.h>
#include "gtest/gtest.h"
#include "../../../src/individual/IndividualTwoAlleles.hpp"
#include "../../../src/GeneticAlgorithm.hpp"
#include "../../utils/DecodeFromBinary.hpp"
#include "../../utils/PrintAlleles.hpp"

TEST(CosTest, globalMaxIsFound)
{
    auto cosFitness = [](const IndividualTwoAlleles &individual) {
        auto x = decodeFromBinary(individual.alleles_x.get());
        auto y = decodeFromBinary(individual.alleles_y.get());
        return 100.0 * cos(x) * cos(y) / exp(x) / exp(y);
    };

    auto stopping = [](const float &fitness) { return fitness > 100 - 1 ? true : false; };
    auto genetic = GeneticAlgorithm<IndividualTwoAlleles>(100, 5, 0.9, 0.01, cosFitness, stopping);
    genetic.findSolution(100);
    auto best = genetic.bestIndividual();

    // printAlleles(*best.alleles.get());
    float bestFitnessValue = cosFitness(best);

    ASSERT_NEAR(100, bestFitnessValue, 0.0001);
}