#include "Individual.hpp"
#include "alleles/DefaultAlleles.hpp"
#include "exceptions/AllelesSizeToSmallException.hpp"

Individual::Individual(const unsigned &allelesSize)
{
    alleles = std::make_shared<DefaultAlleles>(allelesSize, 0, 1);
}

Individual::Individual(std::shared_ptr<IAlleles> allelesArg)
    : alleles(allelesArg) {}

Individual::Individual(const Individual &lhs)
{
    alleles = lhs.alleles->copy();
}

Individual::Individual(Individual &&rhs)
    : IndividualBase(std::move(rhs)),
      alleles(std::move(rhs.alleles)) {}

Individual &Individual::operator=(const Individual &lhs)
{
    alleles = lhs.alleles;
    fitness = lhs.fitness;
    return *this;
}

Individual &Individual::operator=(Individual &&rhs)
{
    alleles = rhs.alleles;
    fitness = rhs.fitness;
    return *this;
}

void Individual::mutate(IMutationStrategy &mutation)
{
    mutation.mutate(*alleles.get());
}

void Individual::mate(IndividualBase &lhs, const unsigned &crossingSpot)
{
    if (alleles->size() < 2 or dynamic_cast<Individual *>(&lhs)->alleles->size() < 2)
        throw AllelesSizeToSmallException();
    crossAlleles(alleles, dynamic_cast<Individual *>(&lhs)->alleles, crossingSpot);
}

unsigned Individual::allelesSize() const
{
    return alleles->size();
}