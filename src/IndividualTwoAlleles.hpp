#pragma once

#include <memory>

#include "alleles/IAlleles.hpp"
#include "mutation/IMutationStrategy.hpp"

class IndividualTwoAlleles
{
public:
    IndividualTwoAlleles(const unsigned &allelesSize);
    IndividualTwoAlleles(const IndividualTwoAlleles &lhs);
    IndividualTwoAlleles(IndividualTwoAlleles &&rhs)
        : alleles_x(std::move(rhs.alleles_x)),
          alleles_y(std::move(rhs.alleles_y)),
          fitness(std::move(fitness)) {}
    ~IndividualTwoAlleles() = default;
    IndividualTwoAlleles &operator=(const IndividualTwoAlleles &lhs)
    {
        alleles_x = lhs.alleles_x;
        alleles_y = lhs.alleles_y;
        fitness = lhs.fitness;
        return *this;
    }
    IndividualTwoAlleles &operator=(IndividualTwoAlleles &&rhs)
    {
        alleles_x = rhs.alleles_x;
        alleles_y = rhs.alleles_y;
        fitness = rhs.fitness;
        return *this;
    }

    void mutate(IMutationStrategy &mutation);
    void mate(IndividualTwoAlleles &lhs, const unsigned &crossingSpot);
    unsigned allelesSize() const;

    std::shared_ptr<IAlleles> alleles_x;
    std::shared_ptr<IAlleles> alleles_y;
    float fitness;

private:
    void crossAlleles(std::shared_ptr<IAlleles> &alleles,
                      std::shared_ptr<IAlleles> &lhsAlleles,
                      const unsigned &crossingSpot);
    template <typename IteratorType>
    void moveBeginIteratorToCrossingPoint(IteratorType &beginIterator, unsigned crossingPoint);
};

template <typename IteratorType>
void IndividualTwoAlleles::moveBeginIteratorToCrossingPoint(IteratorType &beginIterator, unsigned crossingPoint)
{
    while (crossingPoint > 0)
    {
        beginIterator++;
        crossingPoint--;
    }
}
