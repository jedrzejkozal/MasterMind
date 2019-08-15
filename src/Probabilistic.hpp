#pragma once

#include <random>

class Probabilistic
{
public:
    Probabilistic()
        : generator(rd()) {}
    Probabilistic(Probabilistic &&rhs)
        : rd(),
          generator(std::move(rhs.generator)) {}
    virtual ~Probabilistic() = default;

    virtual bool bernoulli(float prob) const;
    int uniform_int(int min, int max) const;
    float uniform_float(float min, float max) const;

private:
    mutable std::random_device rd;
    mutable std::default_random_engine generator;
};