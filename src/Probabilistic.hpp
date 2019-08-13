#pragma once

#include <iostream>

class Probabilistic
{
public:
    virtual bool bernoulli(float prob) const;
    virtual ~Probabilistic() = default;
};