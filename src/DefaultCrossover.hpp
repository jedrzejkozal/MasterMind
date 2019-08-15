#include "ICrossoverStrategy.hpp"
#include "Probabilistic.hpp"

class DefaultCrossover : public ICrossoverStrategy
{
public:
    DefaultCrossover(const float &crossoverProb)
        : ICrossoverStrategy(crossoverProb) {}

    virtual void cross(std::vector<Individual> &matingPool) override;

private:
    void crossPair(Individual &first, Individual &second);
    Probabilistic probabilistic;
};