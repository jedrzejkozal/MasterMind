#include "IndividualBase.hpp"

IndividualBase::IndividualBase(IndividualBase &&rhs)
    : fitness(rhs.fitness) {}

void IndividualBase::crossAlleles(std::shared_ptr<IAlleles> &alleles,
                                  std::shared_ptr<IAlleles> &lhsAlleles,
                                  const unsigned &crossingSpot)
{
    auto firstIterators = alleles->iterators();
    auto secondIterators = lhsAlleles->iterators();
    auto firstBegin = std::get<0>(firstIterators);
    auto firstEnd = std::get<1>(firstIterators);
    auto secondBegin = std::get<0>(secondIterators);

    moveBeginIteratorToCrossingPoint(firstBegin, crossingSpot);
    moveBeginIteratorToCrossingPoint(secondBegin, crossingSpot);

    for (; firstBegin != firstEnd; firstBegin++, secondBegin++)
        std::swap(*firstBegin, *secondBegin);
}

template <typename IteratorType>
void IndividualBase::moveBeginIteratorToCrossingPoint(IteratorType &beginIterator,
                                                      unsigned crossingPoint)
{
    while (crossingPoint > 0)
    {
        beginIterator++;
        crossingPoint--;
    }
}