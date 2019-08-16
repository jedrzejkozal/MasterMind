#include <iostream>

#include "Probabilistic.hpp"

bool Probabilistic::bernoulli(float prob) const
{
    std::bernoulli_distribution distribution(prob);
    return distribution(generator);
}

int Probabilistic::uniform_int(int min, int max) const noexcept
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

float Probabilistic::uniform_float(float min, float max) const noexcept
{
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}