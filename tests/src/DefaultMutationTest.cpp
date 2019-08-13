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

    bool allelesEqual(std::initializer_list<unsigned> expected)
    {
        auto expected_vec = std::vector<unsigned>(expected);
        return std::equal(alleles.begin(), alleles.end(), expected_vec.begin());
    }
};

class DefaultMutationTest : public ::testing::Test
{
};

TEST_F(DefaultMutationTest, baseTest)
{
    std::shared_ptr<ProbabilisticMock> mock = std::make_shared<ProbabilisticMock>();
    EXPECT_CALL(*mock, bernoulli(_))
        .WillOnce(Return(true));

    DefaultMutationTestable sut(mock);
    ASSERT_TRUE(sut.probTest());
}

TEST_F(DefaultMutationTest, mutationTestAllAllelesAreSwitched)
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