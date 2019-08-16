#include "Individual.hpp"
#include "alleles/DefaultAlleles.hpp"
#include "exceptions/AllelesSizeToSmallException.hpp"

Individual::Individual(const unsigned &allelesSize)
{
    alleles = std::make_shared<DefaultAlleles>(allelesSize, 0, 1);
}

Individual::Individual(std::shared_ptr<IAlleles> allelesArg)
    : alleles(allelesArg)
{
}

Individual::Individual(const Individual &lhs)
{
    alleles = lhs.alleles->copy();
}

void Individual::mutate(IMutationStrategy &mutation)
{
    mutation.mutate(*alleles.get());
}

void Individual::mate(Individual &lhs, const unsigned &crossingSpot)
{
    if (alleles->size() < 2 or lhs.alleles->size() < 2)
        throw AllelesSizeToSmallException();
    auto firstIterators = alleles->iterators();
    auto secondIterators = lhs.alleles->iterators();
    auto firstBegin = std::get<0>(firstIterators);
    auto firstEnd = std::get<1>(firstIterators);
    auto secondBegin = std::get<0>(secondIterators);

    moveBeginIteratorToCrossingPoint(firstBegin, crossingSpot);
    moveBeginIteratorToCrossingPoint(secondBegin, crossingSpot);

    for (; firstBegin != firstEnd; firstBegin++, secondBegin++)
        std::swap(*firstBegin, *secondBegin);
}