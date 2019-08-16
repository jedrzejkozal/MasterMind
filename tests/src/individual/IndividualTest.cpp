#include "gtest/gtest.h"
#include "../../../src/individual/Individual.hpp"
#include "../../../src/mutation/DefaultMutation.hpp"
#include "../../testables/DefaultAllelesTestable.hpp"
#include "../../../src/exceptions/AllelesSizeToSmallException.hpp"

TEST(IndividualTest, alllesAreModifiedDuringMutationTest)
{
    auto mutation = DefaultMutation(0.5);
    auto alleles = std::make_shared<DefaultAllelesTestable>(std::initializer_list<unsigned>({0, 0, 0, 0, 0, 0, 0}));
    Individual sut(alleles);

    sut.mutate(mutation);

    ASSERT_NE(alleles->countOnes(), 0);
}

TEST(IndividualTest, allAlllesAreModifiedTest)
{
    auto mutation = DefaultMutation(1.0);
    auto alleles = std::make_shared<DefaultAllelesTestable>(std::initializer_list<unsigned>({0, 0, 0, 0, 0, 0, 0}));
    Individual sut(alleles);

    sut.mutate(mutation);

    ASSERT_NE(alleles->countOnes(), 1);
}

TEST(IndividualTest, defaultMutationTest)
{
    auto mutation = DefaultMutation(0.5);
    auto allels = std::make_shared<DefaultAlleles>(5, 0, 1);
    Individual sut(std::move(allels));

    sut.mutate(mutation);
}

TEST(IndividualTest, allelesSizeLessThen2ExceptionRaised)
{
    auto allels = std::make_shared<DefaultAlleles>(1, 0, 1);
    Individual sut(std::move(allels));
    ASSERT_THROW(
        {
            sut.mate(sut, 1);
        },
        AllelesSizeToSmallException);
}