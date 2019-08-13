#include <random>
#include <iostream>

#include "Probabilistic.hpp"

bool Probabilistic::bernoulli(float prob) const
{
    std::cout << "bernoulli call" << std::endl;
    std::default_random_engine generator;
    std::bernoulli_distribution distribution(prob);

    return distribution(generator);
}