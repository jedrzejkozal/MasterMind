#include "gtest/gtest.h"
#include "../../src/FitnessCalculator.hpp"
#include "../utils/FitnessFunctions.hpp"
#include "../utils/Individuals.hpp"

TEST(FitnessCalculatorTest, afterUpdateFitnessCallIndividualsHaveProperFitnessValue)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(),
                                       individualWithAlleleOne()};

    FitnessCalculator<> sut(std::move(fitnessFunction));
    sut.updateFitness(population);

    ASSERT_EQ(population[0].fitness, 0);
    ASSERT_EQ(population[1].fitness, 1);
}

TEST(FitnessCalculatorTest, afterUpdateFitnessCallFitnessValueIsPositive)
{
    const auto fitnessFunction = [](const Individual &i) { return -10; };
    std::vector<Individual> population{individualWithAlleleZero(),
                                       individualWithAlleleOne()};

    FitnessCalculator<> sut(std::move(fitnessFunction));
    sut.updateFitness(population);

    for (auto &indv : population)
        ASSERT_GE(indv.fitness, 0.0);
}

TEST(FitnessCalculatorTest, afterUpdateFitnessCallSizeIsTheSame)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(),
                                       individualWithAlleleOne()};
    auto populationSize = population.size();

    FitnessCalculator<> sut(std::move(fitnessFunction));
    sut.updateFitness(population);

    ASSERT_EQ(populationSize, population.size());
}