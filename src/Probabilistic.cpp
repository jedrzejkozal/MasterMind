#include <iostream>

#include "Probabilistic.hpp"

bool Probabilistic::bernoulli(float prob) const
{
    std::bernoulli_distribution distribution(prob);
    return distribution(generator);
}

int Probabilistic::uniform(int min, int max) const
{
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}