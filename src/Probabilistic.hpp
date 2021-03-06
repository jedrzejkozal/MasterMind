#pragma once

#include <random>

class Probabilistic
{
public:
    Probabilistic();
    Probabilistic(Probabilistic &&rhs);
    virtual ~Probabilistic() = default;

    virtual bool bernoulli(float prob) const;
    int uniform_int(int min, int max) const noexcept;
    float uniform_float(float min, float max) const noexcept;

private:
    mutable std::random_device rd;
    mutable std::default_random_engine generator;
};