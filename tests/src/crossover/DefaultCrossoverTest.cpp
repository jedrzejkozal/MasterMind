#include "gtest/gtest.h"
#include "../../../src/crossover/DefaultCrossover.hpp"
#include "../../testables/DefaultAllelesTestable.hpp"
#include "../../utils/Individuals.hpp"

TEST(DefaultCrossoverTest, afterCrossoverPopulationHaveTheSameSize)
{
    std::vector<Individual> population{individualWithAlleleZeros(),
                                       individualWithAlleleOnes()};
    auto old_size = population.size();

    DefaultCrossover<> sut(0.5);
    sut.cross(population);

    ASSERT_EQ(old_size, population.size());
}

TEST(DefaultCrossoverTest, individualsAreCrossed)
{
    std::vector<Individual> population{individualWithAlleleZeros(),
                                       individualWithAlleleOnes()};

    DefaultCrossover<> sut(1.0);
    sut.cross(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    ASSERT_TRUE(firstIndividualOnes != 3);
    ASSERT_TRUE(secondIndividualOnes != 3);
}

TEST(DefaultCrossoverTest, individualsAreDeletedInRightOrder)
{
    std::vector<Individual> population{individualWithAlleleOnes(),
                                       individualWithAlleleZeros()};

    DefaultCrossover<> sut(1.0);
    sut.cross(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    ASSERT_TRUE(firstIndividualOnes != 3 or secondIndividualOnes != 3);
}

TEST(DefaultCrossoverTest, individualsAreCrossedForLargerPopulation)
{
    std::vector<Individual> population{individualWithAlleleOnes(),
                                       individualWithAlleleZeros(),
                                       individualWithAlleleZeros(),
                                       individualWithAlleleZeros()};

    DefaultCrossover<> sut(1.0);
    sut.cross(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    ASSERT_TRUE(firstIndividualOnes != 3 or secondIndividualOnes != 3);
}

TEST(DefaultCrossoverTest, ifCrossoverProbabilityIsZeroIndividualsAreNotChanged)
{
    std::vector<Individual> population{individualWithAlleleOnes(),
                                       individualWithAlleleZeros()};

    DefaultCrossover<> sut(0.0);
    sut.cross(population);

    auto firstIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[0].alleles.get())->countOnes();
    auto secondIndividualOnes = dynamic_cast<DefaultAllelesTestable *>(population[1].alleles.get())->countOnes();
    ASSERT_TRUE((firstIndividualOnes == 3 and secondIndividualOnes == 0) or
                (firstIndividualOnes == 0 and secondIndividualOnes == 3));
}