#include "ICrossoverStrategy.hpp"
#include "Probabilistic.hpp"

class DefaultCrossover : public ICrossoverStrategy
{
public:
    DefaultCrossover(const float &crossoverProb)
        : ICrossoverStrategy(crossoverProb) {}

    virtual void cross(std::vector<Individual> &matingPool) override;

private:
    using IteratorType = std::vector<Individual>::iterator;
    std::pair<unsigned, unsigned> selectPair(std::vector<Individual> &matingPool);
    void crossPair(Individual &first, Individual &second);
    bool crossingTakesPlace();
    Probabilistic probabilistic;
};