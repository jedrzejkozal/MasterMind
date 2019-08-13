#include <memory>
#include "gtest/gtest.h"
#include "../mocks/ProbabilisticMock.hpp"
#include "../../src/DefaultMutation.hpp"

using testing::Return;

using namespace testing;

class DefaultMutationTestable : public DefaultMutation
{
public:
    DefaultMutationTestable(std::shared_ptr<Probabilistic> p)
        : DefaultMutation(0.1)
    {
        prob = p;
    }
};

class DefaultAllelesTestable : public DefaultAlleles
{
public:
    DefaultAllelesTestable(std::initializer_list<unsigned> allelesArg)
        : DefaultAlleles(1, 0, 1)
    {
        alleles = allelesArg;
    }

    DefaultAllelesTestable(std::vector<unsigned> allelesArg)
        : DefaultAlleles(1, 0, 1)
    {
        alleles = allelesArg;
    }

    bool allelesEqual(std::initializer_list<unsigned> expected)
    {
        auto expected_vec = std::vector<unsigned>(expected);
        return std::equal(alleles.begin(), alleles.end(), expected_vec.begin());
    }

    unsigned countOnes()
    {
        return std::count_if(alleles.begin(), alleles.end(), [](const unsigned &lhs) { return lhs == 1; });
    }
};

TEST(DefaultMutationTest, allAllelesAreSwitched)
{
    auto alleles = DefaultAllelesTestable({0, 0, 1});

    std::shared_ptr<ProbabilisticMock> mock = std::make_shared<ProbabilisticMock>();
    EXPECT_CALL(*mock, bernoulli(_))
        .Times(3)
        .WillRepeatedly(Return(true));

    DefaultMutationTestable sut(mock);
    sut.mutate(alleles);

    ASSERT_TRUE(alleles.allelesEqual({1, 1, 0}));
}

TEST(DefaultMutationTest, lastAlleleIsSwitched)
{
    auto alleles = DefaultAllelesTestable({0, 0, 1});

    std::shared_ptr<ProbabilisticMock> mock = std::make_shared<ProbabilisticMock>();
    EXPECT_CALL(*mock, bernoulli(_))
        .WillOnce(Return(false))
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    DefaultMutationTestable sut(mock);
    sut.mutate(alleles);

    ASSERT_TRUE(alleles.allelesEqual({0, 0, 0}));
}

TEST(DefaultMutationTest, normalProbabilisticImplWithProbHalfNearlyHalfOfAllelesAreSwitched)
{
    unsigned alleleSize = 1000;
    auto alleles = DefaultAllelesTestable(std::vector<unsigned>(alleleSize, 0));

    DefaultMutation sut(0.5);
    sut.mutate(alleles);

    auto howManyOnes = alleles.countOnes() / float(alleleSize);
    ASSERT_NEAR(howManyOnes, 0.5, 0.05);
}