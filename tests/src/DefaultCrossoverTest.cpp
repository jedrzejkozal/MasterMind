#include "gtest/gtest.h"
#include "../../src/DefaultCrossover.hpp"
#include "../testables/DefaultAllelesTestable.hpp"

class DefaultCrossoverTest : public testing::Test
{
public:
    auto individualWithAlleleZeros() const noexcept;
    auto individualWithAlleleOnes() const noexcept;
};

auto DefaultCrossoverTest::individualWithAlleleZeros() const noexcept
{
    auto allelesZeros = std::make_shared<DefaultAllelesTestable>(
        std::initializer_list<unsigned>({0, 0, 0}));
    return Individual(allelesZeros);
}

auto DefaultCrossoverTest::individualWithAlleleOnes() const noexcept
{
    auto allelesOnes = std::make_shared<DefaultAllelesTestable>(
        std::initializer_list<unsigned>({1, 1, 1}));
    return Individual(allelesOnes);
}

TEST_F(DefaultCrossoverTest, afterCrossoverPopulationHaveTheSameSize)
{
    std::vector<Individual> population{individualWithAlleleZeros(),
                                       individualWithAlleleOnes()};
    auto old_size = population.size();

    DefaultCrossover sut(0.5);
    sut.cross(population);

    ASSERT_EQ(old_size, population.size());
}

TEST_F(DefaultCrossoverTest, individualsAreCrossed)
{
    std::vector<Individual> population{individualWithAlleleZeros(),
                                       individualWithAlleleOnes()};

    DefaultCrossover sut(0.5);
    sut.cross(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    ASSERT_NE(firstIndividualOnes, 3);
    ASSERT_NE(secondIndividualOnes, 3);
}