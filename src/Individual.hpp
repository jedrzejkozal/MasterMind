#pragma once

#include <memory>

#include "IAlleles.hpp"
#include "IMutationStrategy.hpp"

class Individual
{
public:
    Individual(unsigned allelesSize);
    Individual(std::shared_ptr<IAlleles> allelesArg);

    void mutate(IMutationStrategy &mutation);

private:
    unsigned alleleSize;
    std::shared_ptr<IAlleles> alleles;
};

Individual::Individual(unsigned allelesSize)
    : alleleSize(allelesSize)
{
    alleles = std::make_shared<DefaultAlleles>(DefaultAlleles(allelesSize, 0, 1));
}

Individual::Individual(std::shared_ptr<IAlleles> allelesArg)
    : alleles(allelesArg)
{
}

void Individual::mutate(IMutationStrategy &mutation)
{
    mutation.mutate(*alleles.get());
}