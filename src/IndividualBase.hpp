#pragma once

#include "mutation/IMutationStrategy.hpp"

class IndividualBase
{
public:
    IndividualBase() = default;
    IndividualBase(IndividualBase &&rhs);

    virtual ~IndividualBase() = default;

    virtual void mutate(IMutationStrategy &mutation) = 0;
    virtual void mate(IndividualBase &lhs, const unsigned &crossingSpot) = 0;
    virtual unsigned allelesSize() const = 0;

    float fitness;

protected:
    void crossAlleles(std::shared_ptr<IAlleles> &alleles,
                      std::shared_ptr<IAlleles> &lhsAlleles,
                      const unsigned &crossingSpot);
    template <typename IteratorType>
    void moveBeginIteratorToCrossingPoint(IteratorType &beginIterator,
                                          unsigned crossingPoint);
};