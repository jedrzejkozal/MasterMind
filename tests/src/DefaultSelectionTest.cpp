#include "gtest/gtest.h"
#include "../../src/DefaultSelection.hpp"
#include "../testables/DefaultAllelesTestable.hpp"

class SelectionTest : public testing::Test
{
public:
    auto getSimpleFitnessFunc() const noexcept;
    auto individualWithAlleleZero() const noexcept;
    auto individualWithAlleleOne() const noexcept;
};

auto SelectionTest::getSimpleFitnessFunc() const noexcept
{
    return [](const Individual &i) {
        auto alleles_iterators = dynamic_cast<DefaultAllelesTestable *>(i.alleles.get())->iterators();
        return float(*std::get<0>(alleles_iterators));
    };
}

auto SelectionTest::individualWithAlleleZero() const noexcept
{
    auto allelesZeros = std::make_shared<DefaultAllelesTestable>(
        std::initializer_list<unsigned>({0}));
    return Individual(allelesZeros);
}

auto SelectionTest::individualWithAlleleOne() const noexcept
{
    auto allelesOnes = std::make_shared<DefaultAllelesTestable>(
        std::initializer_list<unsigned>({1}));
    return Individual(allelesOnes);
}

TEST_F(SelectionTest, populationAfterSelectionHaveTheSameSize)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(),
                                       individualWithAlleleOne()};

    auto initialPopSize = population.size();

    DefaultSelection sut(fitnessFunction);
    sut.select(population);

    ASSERT_EQ(initialPopSize, population.size());
}

TEST_F(SelectionTest, individualsWithZeroFitnessAreNotSelected)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(),
                                       individualWithAlleleOne()};

    DefaultSelection sut(fitnessFunction);
    sut.select(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    ASSERT_EQ(firstIndividualOnes, 1);
    ASSERT_EQ(secondIndividualOnes, 1);
}

TEST_F(SelectionTest, individualsWithZeroFitnessAreNotSelectedEvenIfThereAreMoreOfThem)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(),
                                       individualWithAlleleZero(),
                                       individualWithAlleleZero(),
                                       individualWithAlleleOne()};

    DefaultSelection sut(fitnessFunction);
    sut.select(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    auto thirdIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[2].alleles.get())->countOnes();
    auto fourthIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[3].alleles.get())->countOnes();

    ASSERT_EQ(firstIndividualOnes, 1);
    ASSERT_EQ(secondIndividualOnes, 1);
    ASSERT_EQ(thirdIndividualOnes, 1);
    ASSERT_EQ(fourthIndividualOnes, 1);
}
