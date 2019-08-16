#include <vector>

#include "../Individual.hpp"

class ICrossoverStrategy
{
public:
    ICrossoverStrategy(const float &crossoverProb)
        : crossoverProbability(crossoverProb) {}

    virtual void cross(std::vector<Individual> &matingPool) = 0;

protected:
    const float crossoverProbability;
};
