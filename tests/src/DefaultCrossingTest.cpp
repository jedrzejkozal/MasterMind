#include "gtest/gtest.h"
#include "../../src/DefaultCrossing.hpp"
#include "../testables/DefaultAllelesTestable.hpp"

class CrossingTest : public testing::Test
{
public:
    auto getSimpleFitnessFunc() const noexcept;
    auto individualWithAlleleZero() const noexcept;
    auto individualWithAlleleOne() const noexcept;
    auto individualWithAlleleZeros() const noexcept;
    auto individualWithAlleleOnes() const noexcept;
};

auto CrossingTest::getSimpleFitnessFunc() const noexcept
{
    return [](const Individual &i) {
        auto alleles_iterators = dynamic_cast<DefaultAllelesTestable *>(i.alleles.get())->iterators();
        return float(*std::get<0>(alleles_iterators));
    };
}

auto CrossingTest::individualWithAlleleZero() const noexcept
{
    auto allelesZeros = std::make_shared<DefaultAllelesTestable>(
        std::initializer_list<unsigned>({0}));
    return Individual(allelesZeros);
}

auto CrossingTest::individualWithAlleleOne() const noexcept
{
    auto allelesOnes = std::make_shared<DefaultAllelesTestable>(
        std::initializer_list<unsigned>({1}));
    return Individual(allelesOnes);
}

auto CrossingTest::individualWithAlleleZeros() const noexcept
{
    auto allelesZeros = std::make_shared<DefaultAllelesTestable>(
        std::initializer_list<unsigned>({0, 0, 0}));
    return Individual(allelesZeros);
}

auto CrossingTest::individualWithAlleleOnes() const noexcept
{
    auto allelesOnes = std::make_shared<DefaultAllelesTestable>(
        std::initializer_list<unsigned>({1, 1, 1}));
    return Individual(allelesOnes);
}

TEST_F(CrossingTest, populationAfterCrossingHaveTheSameSize)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(), individualWithAlleleOne()};

    auto initialPopSize = population.size();

    DefaultCrossing sut(0.5, fitnessFunction);
    sut.cross(population);

    ASSERT_EQ(initialPopSize, population.size());
}

TEST_F(CrossingTest, individualsWithZeroFitnessDoNotCross)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(), individualWithAlleleOne()};

    DefaultCrossing sut(0.5, fitnessFunction);
    sut.cross(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    ASSERT_EQ(firstIndividualOnes, 1);
    ASSERT_EQ(secondIndividualOnes, 1);
}

TEST_F(CrossingTest, individualsWithZeroFitnessDoNotCrossEvenIfThereAreMoreOfThem)
{
    const auto fitnessFunction = getSimpleFitnessFunc();
    std::vector<Individual> population{individualWithAlleleZero(),
                                       individualWithAlleleZero(),
                                       individualWithAlleleZero(),
                                       individualWithAlleleOne()};

    DefaultCrossing sut(0.5, fitnessFunction);
    sut.cross(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    auto thirdIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[2].alleles.get())->countOnes();
    auto fourthIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[3].alleles.get())->countOnes();

    ASSERT_EQ(firstIndividualOnes, 1);
    ASSERT_EQ(secondIndividualOnes, 1);
    ASSERT_EQ(thirdIndividualOnes, 1);
    ASSERT_EQ(fourthIndividualOnes, 1);
}

TEST_F(CrossingTest, individualsAreCrossed)
{
    const auto fitnessFunction = [](const Individual &i) { return 1.0; };
    std::vector<Individual> population{individualWithAlleleZeros(),
                                       individualWithAlleleOnes()};

    DefaultCrossing sut(0.5, fitnessFunction);
    sut.cross(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    ASSERT_NE(firstIndividualOnes, 3);
    ASSERT_NE(secondIndividualOnes, 3);
}