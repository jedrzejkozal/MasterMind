#include "gtest/gtest.h"
#include "../../../src/selection/DefaultSelection.hpp"
#include "../../testables/DefaultAllelesTestable.hpp"
#include "../../utils/FitnessFunctions.hpp"
#include "../../utils/Individuals.hpp"

class SelectionTest : public testing::Test
{
public:
    void applyFitnessFunction(const std::function<float(const Individual &fitnessFunction)>,
                              std::vector<Individual> &population);
};

void SelectionTest::applyFitnessFunction(const std::function<float(const Individual &)> fitnessFunction,
                                         std::vector<Individual> &population)
{
    for (auto &individual : population)
        individual.fitness = fitnessFunction(individual);
}

TEST_F(SelectionTest, populationAfterSelectionHaveTheSameSize)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(),
                                       individualWithAlleleOne()};
    applyFitnessFunction(fitnessFunction, population);

    auto initialPopSize = population.size();

    DefaultSelection<> sut;
    sut.select(population);

    ASSERT_EQ(initialPopSize, population.size());
}

TEST_F(SelectionTest, individualsWithZeroFitnessAreNotSelected)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(),
                                       individualWithAlleleOne()};
    applyFitnessFunction(fitnessFunction, population);

    DefaultSelection<> sut;
    sut.select(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    ASSERT_EQ(firstIndividualOnes, 2);
    ASSERT_EQ(secondIndividualOnes, 2);
}

TEST_F(SelectionTest, individualsWithZeroFitnessAreNotSelectedEvenIfThereAreMoreOfThem)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(),
                                       individualWithAlleleZero(),
                                       individualWithAlleleZero(),
                                       individualWithAlleleOne()};
    applyFitnessFunction(fitnessFunction, population);

    DefaultSelection<> sut;
    sut.select(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    auto thirdIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[2].alleles.get())->countOnes();
    auto fourthIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[3].alleles.get())->countOnes();

    ASSERT_EQ(firstIndividualOnes, 2);
    ASSERT_EQ(secondIndividualOnes, 2);
    ASSERT_EQ(thirdIndividualOnes, 2);
    ASSERT_EQ(fourthIndividualOnes, 2);
}
