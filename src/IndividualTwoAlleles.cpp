#include "IndividualTwoAlleles.hpp"
#include "alleles/DefaultAlleles.hpp"
#include "exceptions/AllelesSizeToSmallException.hpp"

IndividualTwoAlleles::IndividualTwoAlleles(const unsigned &allelesSize)
{
    alleles_x = std::make_shared<DefaultAlleles>(allelesSize, 0, 1);
    alleles_y = std::make_shared<DefaultAlleles>(allelesSize, 0, 1);
}

IndividualTwoAlleles::IndividualTwoAlleles(const IndividualTwoAlleles &lhs)
{
    alleles_x = lhs.alleles_x->copy();
    alleles_y = lhs.alleles_y->copy();
}

IndividualTwoAlleles::IndividualTwoAlleles(IndividualTwoAlleles &&rhs)
    : IndividualBase(std::move(rhs)),
      alleles_x(std::move(rhs.alleles_x)),
      alleles_y(std::move(rhs.alleles_y)) {}

IndividualTwoAlleles &IndividualTwoAlleles::operator=(const IndividualTwoAlleles &lhs)
{
    alleles_x = lhs.alleles_x;
    alleles_y = lhs.alleles_y;
    fitness = lhs.fitness;
    return *this;
}

IndividualTwoAlleles &IndividualTwoAlleles::operator=(IndividualTwoAlleles &&rhs)
{
    alleles_x = rhs.alleles_x;
    alleles_y = rhs.alleles_y;
    fitness = rhs.fitness;
    return *this;
}

void IndividualTwoAlleles::mutate(IMutationStrategy &mutation)
{
    mutation.mutate(*alleles_x.get());
    mutation.mutate(*alleles_y.get());
}

void IndividualTwoAlleles::mate(IndividualBase &lhs, const unsigned &crossingSpot)
{
    if (alleles_x->size() < 2 or
        dynamic_cast<IndividualTwoAlleles *>(&lhs)->alleles_x->size() < 2 or
        alleles_y->size() < 2 or
        dynamic_cast<IndividualTwoAlleles *>(&lhs)->alleles_y->size() < 2)
        throw AllelesSizeToSmallException();
    crossAlleles(alleles_x, dynamic_cast<IndividualTwoAlleles *>(&lhs)->alleles_x, crossingSpot);
    crossAlleles(alleles_y, dynamic_cast<IndividualTwoAlleles *>(&lhs)->alleles_y, crossingSpot);
}

unsigned IndividualTwoAlleles::allelesSize() const
{
    return alleles_x->size();
}