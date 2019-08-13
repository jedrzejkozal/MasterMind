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
        : DefaultMutation()
    {
        prob = p;
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