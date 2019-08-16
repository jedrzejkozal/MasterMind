#include "gtest/gtest.h"
#include "../../src/GeneticAlgorithm.hpp"

TEST(GeneticAlgorithmTest, allelesHaveSpecifiedSize)
{
    auto allelesSize = 5;
    GeneticAlgorithm sut(5, allelesSize, 0.5, 0.5, [](const auto &i) { return 1; });
    ASSERT_EQ(sut.bestIndividual().alleles->size(), allelesSize);
}