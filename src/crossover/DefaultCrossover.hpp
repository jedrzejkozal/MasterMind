#include "ICrossoverStrategy.hpp"
#include "../Probabilistic.hpp"

class DefaultCrossover : public ICrossoverStrategy
{
public:
    DefaultCrossover(const float &crossoverProb)
        : ICrossoverStrategy(crossoverProb) {}

    virtual void cross(std::vector<Individual> &matingPool) override;

private:
    void addPairToNewPopulation(std::vector<Individual> &newPopulation,
                                std::vector<Individual> &matingPool);
    std::pair<unsigned, unsigned> selectPair(std::vector<Individual> &matingPool);
    void crossPair(Individual &first, Individual &second);
    bool crossingTakesPlace();
    void removeUsed(std::vector<Individual> &matingPool,
                    std::pair<unsigned, unsigned> pair);

    Probabilistic probabilistic;
};