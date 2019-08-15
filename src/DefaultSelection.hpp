#pragma once

#include "ISelectionStrategy.hpp"
#include "Probabilistic.hpp"

class DefaultSelection : public ISelectionStrategy
{
public:
    DefaultSelection(const std::function<float(const Individual &)> fitFunc)
        : ISelectionStrategy(fitFunc)
    {
    }

    DefaultSelection(DefaultSelection &&rhs)
        : ISelectionStrategy(std::move(rhs)),
          probabilistic(std::move(rhs.probabilistic))
    {
    }

    virtual void select(std::vector<Individual> &population) override;

private:
    std::vector<float> calcCumulativeProb(const std::vector<Individual> &population);
    std::vector<Individual> drawMatingPool(const std::vector<Individual> &population,
                                           const std::vector<float> &cumulativeProb);

    std::vector<float> calcIndividualFitness(const std::vector<Individual> &population);
    float calcVectorSum(const std::vector<float> &v);
    std::vector<float> calcSelectionProb(std::vector<float> &fitness, const float &sum);
    std::vector<float> toCumulative(std::vector<float> &SelectionProb);

    Individual selectIndividual(const std::vector<Individual> &population,
                                const std::vector<float> &cumulativeProb);
    void crossPair(Individual &first, Individual &second);

    Probabilistic probabilistic;
};
