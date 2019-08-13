#include "gtest/gtest.h"
#include "../../src/Probabilistic.hpp"
#include "../mocks/ProbabilisticMock.hpp"

using testing::Return;

TEST(ProbabilisticTest, bernoulliPositive)
{
    ProbabilisticMock mock;
    EXPECT_CALL(mock, bernoulli(0.5))
        .WillOnce(Return(true));
    mock.bernoulli(0.5);
}