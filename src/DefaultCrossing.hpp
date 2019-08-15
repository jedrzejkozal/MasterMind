#pragma once

#include "ICrossingStrategy.hpp"
#include "Probabilistic.hpp"

class DefaultCrossing : public ICrossingStrategy
{
public:
    DefaultCrossing(const float &crossingProb, const std::function<float(const Individual &)> fitFunc)
        : ICrossingStrategy(fitFunc),
          crossingProbability(crossingProb)
    {
    }

    DefaultCrossing(DefaultCrossing &&rhs)
        : ICrossingStrategy(std::move(rhs)),
          crossingProbability(rhs.crossingProbability),
          prob(std::move(rhs.prob))
    {
    }

    virtual void cross(std::vector<Individual> &population) override;

private:
    std::vector<float> calcCumulativeProb(const std::vector<Individual> &population);
    std::vector<Individual> drawNewPopulation(const std::vector<Individual> &population,
                                              const std::vector<float> &cumulativeProb);

    std::vector<float> calcIndividualFitness(const std::vector<Individual> &population);
    float calcVectorSum(const std::vector<float> &v);
    std::vector<float> calcCrossingProb(std::vector<float> &fitness, const float &sum);
    std::vector<float> toCumulative(std::vector<float> &crossingProb);

    Individual selectIndividual(const std::vector<Individual> &population,
                                const std::vector<float> &cumulativeProb);
    void crossPair(Individual &first, Individual &second);

    const float crossingProbability;
    Probabilistic prob;
};
