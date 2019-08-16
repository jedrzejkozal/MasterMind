#include "gtest/gtest.h"
#include "../../src/GeneticAlgorithm.hpp"
#include "../../src/exceptions/PopulationSizeNotEvenException.hpp"
#include "../../src/exceptions/PopulationSizeToSmallException.hpp"

#include "../../src/IndividualTwoAlleles.hpp"

TEST(GeneticAlgorithmTest, allelesHaveSpecifiedSize)
{
    auto allelesSize = 5;
    GeneticAlgorithm<Individual> sut(6, allelesSize, 0.5, 0.5, [](const auto &i) { return 1; });
    ASSERT_EQ(sut.bestIndividual().alleles->size(), allelesSize);
}

TEST(GeneticAlgorithmTest, whenPopulationSizeNotEvenExceptionRaised)
{
    GeneticAlgorithm<Individual> sut(5, 1, 0.5, 0.5, [](const auto &i) { return 1; });

    ASSERT_THROW({ sut.findSolution(1); }, PopulationSizeNotEvenException);
}

TEST(GeneticAlgorithmTest, whenPopulationSizeIsOneExceptionRaised)
{
    GeneticAlgorithm<Individual> sut(1, 1, 0.5, 0.5, [](const auto &i) { return 1; });

    ASSERT_THROW({ sut.findSolution(1); }, PopulationSizeToSmallException);
}

TEST(GeneticAlgorithmTest, customIndividualType)
{
    GeneticAlgorithm<IndividualTwoAlleles> sut(1, 1, 0.5, 0.5, [](const auto &i) { return 1; });

    ASSERT_THROW({ sut.findSolution(1); }, PopulationSizeToSmallException);
}