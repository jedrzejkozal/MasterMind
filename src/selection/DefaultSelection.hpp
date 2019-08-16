#pragma once

#include "ISelectionStrategy.hpp"
#include "../Probabilistic.hpp"

class DefaultSelection : public ISelectionStrategy
{
public:
    DefaultSelection() = default;
    DefaultSelection(DefaultSelection &&rhs)
        : probabilistic(const_cast<Probabilistic &&>(std::move(rhs.probabilistic))) {}

    virtual void select(std::vector<Individual> &population) override;

private:
    std::vector<float> calcCumulativeProb(const std::vector<Individual> &population) const;
    std::vector<Individual> drawMatingPool(const std::vector<Individual> &population,
                                           const std::vector<float> &cumulativeProb) const;

    std::vector<float> getIndividualsFitness(const std::vector<Individual> &population) const;
    float calcVectorSum(const std::vector<float> &v) const noexcept;
    std::vector<float> calcSelectionProb(std::vector<float> &fitness, float &sum) const noexcept;
    std::vector<float> toCumulative(std::vector<float> &SelectionProb) const noexcept;

    Individual selectIndividual(const std::vector<Individual> &population,
                                const std::vector<float> &cumulativeProb) const noexcept;
    unsigned indexFromIterator(const std::vector<float>::const_iterator &it,
                               const std::vector<float> &container) const noexcept;
    void crossPair(Individual &first, Individual &second);

    const Probabilistic probabilistic;
};
