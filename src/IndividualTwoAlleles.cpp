#include "IndividualTwoAlleles.hpp"
#include "alleles/DefaultAlleles.hpp"
#include "exceptions/AllelesSizeToSmallException.hpp"

IndividualTwoAlleles::IndividualTwoAlleles(const unsigned &allelesSize)
{
    alleles_x = std::make_shared<DefaultAlleles>(allelesSize, 0, 1);
}

IndividualTwoAlleles::IndividualTwoAlleles(const IndividualTwoAlleles &lhs)
{
    alleles_x = lhs.alleles_x->copy();
    alleles_y = lhs.alleles_y->copy();
}

void IndividualTwoAlleles::mutate(IMutationStrategy &mutation)
{
    mutation.mutate(*alleles_x.get());
    mutation.mutate(*alleles_y.get());
}

void IndividualTwoAlleles::mate(IndividualTwoAlleles &lhs, const unsigned &crossingSpot)
{
    if (alleles_x->size() < 2 or lhs.alleles_x->size() < 2 or alleles_y->size() < 2 or lhs.alleles_y->size() < 2)
        throw AllelesSizeToSmallException();
    crossAlleles(alleles_x, lhs.alleles_x, crossingSpot);
    crossAlleles(alleles_y, lhs.alleles_y, crossingSpot);
}

void IndividualTwoAlleles::crossAlleles(std::shared_ptr<IAlleles> &alleles,
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

unsigned IndividualTwoAlleles::allelesSize() const
{
    return alleles_x->size();
}