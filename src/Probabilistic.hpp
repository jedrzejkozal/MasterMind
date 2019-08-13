#pragma once

#include <iostream>

class Probabilistic
{
public:
    virtual ~Probabilistic() = default;

    virtual bool bernoulli(float prob) const;
    virtual int uniform(int min, int max) const;
};