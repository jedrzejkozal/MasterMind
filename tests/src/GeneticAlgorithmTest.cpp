#include "gtest/gtest.h"
#include "../../src/GeneticAlgorithm.hpp"

TEST(GeneticAlgorithmTest, allelesHaveSpecifiedSize)
{
    auto allelesSize = 5;
    GeneticAlgorithm sut(5, allelesSize, 0.5, 0.5, [](const auto &i) { return 1; });
    ASSERT_EQ(sut.bestIndividual().alleles->size(), allelesSize);
}

// TEST_F(SelectionTest, afterUpdateFitnessIndividualsHaveProperFitnessValue)
// {
//     const auto fitnessFunction = getSimpleFitnessFunc();
//     std::vector<Individual> population{individualWithAlleleZero(),
//                                        individualWithAlleleOne()};

//     DefaultSelection sut(fitnessFunction);
//     sut.updateFitness(population);

//     ASSERT_EQ(population[0].fitness, 0);
//     ASSERT_EQ(population[1].fitness, 1);
// }