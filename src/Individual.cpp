#include "Individual.hpp"
#include "alleles/DefaultAlleles.hpp"

Individual::Individual(unsigned allelesSize)
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