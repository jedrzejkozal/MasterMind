#pragma once

#include <memory>

#include "alleles/IAlleles.hpp"
#include "mutation/IMutationStrategy.hpp"

class Individual
{
public:
    Individual(const unsigned &allelesSize);
    Individual(std::shared_ptr<IAlleles> allelesArg);
    Individual(const Individual &lhs);
    Individual(Individual &&rhs)
        : alleles(std::move(rhs.alleles)),
          fitness(std::move(fitness)) {}
    ~Individual() = default;
    Individual &operator=(const Individual &lhs)
    {
        alleles = lhs.alleles;
        fitness = lhs.fitness;
        return *this;
    }
    Individual &operator=(Individual &&rhs)
    {
        alleles = rhs.alleles;
        fitness = rhs.fitness;
        return *this;
    }

    void mutate(IMutationStrategy &mutation);
    void mate(Individual &lhs, const unsigned &crossingSpot);

    std::shared_ptr<IAlleles> alleles;
    float fitness;

private:
    template <typename IteratorType>
    void moveBeginIteratorToCrossingPoint(IteratorType &beginIterator, unsigned crossingPoint);
};

template <typename IteratorType>
void Individual::moveBeginIteratorToCrossingPoint(IteratorType &beginIterator, unsigned crossingPoint)
{
    while (crossingPoint > 0)
    {
        beginIterator++;
        crossingPoint--;
    }
}
