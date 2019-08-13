#pragma once

#include "gmock/gmock.h"
#include "../../src/Probabilistic.hpp"

class ProbabilisticMock : public Probabilistic
{
public:
    virtual ~ProbabilisticMock() = default;
    MOCK_METHOD1(bernoulli, bool(float));
};