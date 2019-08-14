#pragma once

#include <random>

class Probabilistic
{
public:
    Probabilistic()
        : generator(rd()) {}
    virtual ~Probabilistic() = default;

    virtual bool bernoulli(float prob) const;
    virtual int uniform(int min, int max) const;

private:
    mutable std::random_device rd;
    mutable std::default_random_engine generator;
};