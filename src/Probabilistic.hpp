#pragma once

#include <random>

class Probabilistic
{
public:
    Probabilistic()
        : generator(rd()) {}
    virtual ~Probabilistic() = default;

    virtual bool bernoulli(float prob);
    virtual int uniform(int min, int max);

private:
    std::random_device rd;
    std::default_random_engine generator;
};